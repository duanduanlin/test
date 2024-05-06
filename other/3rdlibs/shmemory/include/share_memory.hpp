#ifndef __SHARE_MEMORY__H__
#define __SHARE_MEMORY__H__

#include <pthread.h>
#include <string>
#include <errno.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include "log.hpp"

namespace sharememory
{
template<class T>
class ShareMemory
{
private:
	struct TShareMemory
	{
		// 引用计数
		int ref_cnt;
		// 共享内存锁
		pthread_mutex_t mutex;
		// 共享内存数据
		T data;
	};

public:
	explicit ShareMemory(const std::string& key_name)
	{
		// 共享内存
		m_shm = reinterpret_cast<TShareMemory*>(-1);
		m_shm_id = -1;
		m_key_name = key_name;

		//
		m_inited = false;
	}

	~ShareMemory()
	{
		if (m_inited)
		{
			// 减少引用计数
			Lock();
			m_shm->ref_cnt--;

			// 若是最后一个进程引用，删除
			if (m_shm->ref_cnt <= 0)
			{
				pthread_mutex_destroy(&m_shm->mutex); //销毁mutex，就不需要再Unlock

				if (shmdt(m_shm) == -1)
				{
					loge("shmdt failed:%s\n", strerror(errno));
				}

				if (shmctl(m_shm_id, IPC_RMID, nullptr) == -1)
				{
					loge("shmctl(IPC_RMID) failed:%s\n", strerror(errno));
				}
			}
			else
			{
				UnLock();
				// 解除与进程关联
				if (shmdt(m_shm) == -1)
				{
					loge("shmdt failed:%s\n", strerror(errno));
				}
			}
		}
	}

	bool Init(int countOfT = 1)
	{
        const int ciMode0666=(S_IRUSR|S_IWUSR) | (S_IRGRP|S_IWGRP) | (S_IROTH|S_IWOTH);
		if (m_inited)
		{
			return true;
		}

		key_t key = ftok(m_key_name.c_str(), 66);
		if (key < 0)
		{
			loge("get key error:%s\n", strerror(errno));
			return false;
		}

		if (countOfT < 1)
		{
			loge("Init: countOfT[%d] error\n", countOfT);
			return false;
		}

		m_shm_id = shmget(key, sizeof(TShareMemory) + sizeof(T) * (countOfT - 1), IPC_CREAT | ciMode0666 | IPC_EXCL);
		if (-1 != m_shm_id ) // 共享内存创建成功，第一次创建
		{
			//
			m_shm = reinterpret_cast<TShareMemory*>(shmat(m_shm_id, nullptr, 0));
			if (ShareMemoryIsInvalid())
			{
				loge("Init: shmat error:%s\n", strerror(errno));
				/**
				 * 到此m_shm->mutex并未初始化成功，shmctl确保下次调用Init shmget 能成功
				 * 进而再次运行第一次创建的逻辑
				 */
				shmctl(m_shm_id, IPC_RMID, nullptr);
				return false;
			}

			pthread_mutexattr_t attr;
			pthread_mutexattr_init(&attr);
			pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
			pthread_mutexattr_setrobust(&attr, PTHREAD_MUTEX_ROBUST);
			int ret = pthread_mutex_init(&(m_shm->mutex), &attr);
			if (0 != ret)
			{
				logi("Init: mute init error, ret:%d\n", ret);
				if (shmdt(m_shm) == -1)
				{
					loge("shmdt failed:%s\n",strerror(errno));
				}

				if (shmctl(m_shm_id, IPC_RMID, nullptr) == -1)
				{
					loge("shmctl(IPC_RMID) failed:%s\n",strerror(errno));
				}
				return false;
			}

			Lock();
			memset(&(m_shm->data), 0, sizeof(T));
			m_shm->ref_cnt = 1;
			UnLock();
		}
		else
		{
			if (EEXIST == errno)  //共享内存已创建
			{
				//
				m_shm_id = shmget(key, sizeof(TShareMemory), 0);
				if (-1 == m_shm_id)
				{
					return false;
				}

				//
				m_shm = reinterpret_cast<TShareMemory*>(shmat(m_shm_id, nullptr, 0));
				if (ShareMemoryIsInvalid())
				{
					loge("shmat failed:%s\n", strerror(errno));
					return false;
				}

				// 
				AddRef();
			}
			else
			{
				loge("Init: shmget error:%s\n", strerror(errno));
				return false;
			}
		}
		
		m_inited = true;
		return true;
	}

	void Lock(void)
	{
		if (ShareMemoryIsInvalid())
		{
			if (EOWNERDEAD == pthread_mutex_lock(&(m_shm->mutex)))
			{
				 pthread_mutex_consistent(&(m_shm->mutex));
			}
		}
	}

	void UnLock(void)
	{
		if (ShareMemoryIsInvalid())
		{
			pthread_mutex_unlock(&(m_shm->mutex));
		}
	}

	T* GetMemory(void)
	{
		if (ShareMemoryIsInvalid())
		{
			return nullptr;
		}

		return &(m_shm->data);
	}
	
private:
    bool ShareMemoryIsInvalid()
    {
        return (m_shm==reinterpret_cast<TShareMemory*>(-1));
    }
	inline void AddRef()
	{
		if (ShareMemoryIsInvalid())
		{
			Lock();
			m_shm->ref_cnt ++;
			UnLock();
		}
	}

private:
	// 共享内存句柄
	TShareMemory* m_shm;
	int m_shm_id;
	std::string m_key_name;
	//
	bool m_inited;
};

}
using namespace sharememory;

#endif //__SHARE_MEMORY__H__