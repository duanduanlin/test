#ifndef __RING_BUFFER__H__
#define __RING_BUFFER__H__

#include <mutex>
#include <string.h>
#include <condition_variable>


namespace ringbuf
{
template <class T>
class CRingBuffer
{
public:
	enum emRingbufferGetMode
	{
		RINGBUFFER_GET_READ, //get data and move the index
		RINGBUFFER_GET_COPY, //just get data,do'nt move the index
	};

	enum SelectStatus
	{
		WAIT_ERROR = -1,
		WAIT_OK = 0,
		WAIT_TIMEOUT = 1,
		WAIT_MAX
	};

	CRingBuffer()
	{
		m_pBuffer = nullptr;
		m_nSize = 0;
		m_nUnreadSize = 0;
		m_nWritePos = 0;
		m_nReadPos = 0;
	}

	~CRingBuffer()
	{
		deInit();
	}

	/* 去init */
	void deInit(void)
	{
		std::unique_lock<std::mutex> lock(m_mtx);
		if (m_pBuffer != nullptr)
		{
			delete[] m_pBuffer;
			m_pBuffer = nullptr;
			m_nSize = 0;
			m_nUnreadSize = 0;
			m_nWritePos = 0;
			m_nReadPos = 0;
		}
	}

	/*
	初始化缓冲区
	*/
	bool init(int nSize)
	{
		std::unique_lock<std::mutex> lock(m_mtx);
		// 参数校验
		if (nSize <= 0)
		{
			return false;
		}
		// 
		if (isInited())
		{
			return true; 
		}
		//
		try
		{
			m_pBuffer = new T[nSize];
		}
		catch (std::bad_alloc)
		{
			return false;
		}
		memset(m_pBuffer, 0x00, nSize * sizeof(T));
		m_nSize = nSize;
		m_nUnreadSize = 0;
		m_nWritePos = 0;
		m_nReadPos = 0;

		return true;
	}

	/*
	重置环形缓冲区大小，原有数据保留
	*/
	bool reSetBufferSize(int nSize)
	{
		std::unique_lock<std::mutex> lock(m_mtx);
		// 参数校验
		if(nSize <= 0)
		{
			return false;
		}

		// 如果原有剩余数据大于调整后的缓冲大小nSize，则调整后的nSize调整到未读取数据的大小
		if(m_nUnreadSize > nSize) 
		{
			nSize = m_nUnreadSize;
		}

		// 申请新缓冲
		T* pNewBuffer = nullptr;
		try
		{
			pNewBuffer = new T[nSize];
		}
		catch (std::bad_alloc)
		{
			return false;
		}
		memset(pNewBuffer, 0x00, nSize * sizeof(T));

		// 保存原有数据(若有)
		if(m_pBuffer != nullptr && m_nUnreadSize > 0)
		{
			if (m_nReadPos + m_nUnreadSize <= m_nSize)
			{
				memcpy(pNewBuffer, &m_pBuffer[m_nReadPos], m_nUnreadSize * sizeof(T));
			}
			else
			{
				memcpy(pNewBuffer, &m_pBuffer[m_nReadPos], (m_nSize - m_nReadPos) * sizeof(T));
				memcpy(&pNewBuffer[m_nSize - m_nReadPos], m_pBuffer, (m_nUnreadSize - (m_nSize - m_nReadPos)) * sizeof(T));
			}
		}

		// 释放老的缓冲
		if (m_pBuffer != nullptr)
		{
			delete[] m_pBuffer;
			m_pBuffer = nullptr;
		}

		// 移动读写指针
		m_pBuffer = pNewBuffer;
		m_nSize = nSize;
		m_nReadPos = 0;
		m_nWritePos = m_nUnreadSize;

		return true;
	}
	
	/*
	清空环形缓冲区
	*/
	void clear()
	{
		std::unique_lock<std::mutex> lock(m_mtx);
		m_nUnreadSize = 0;
		m_nWritePos = 0;
		m_nReadPos = 0;
	}

	/*
	写入数据到环形缓冲区
	返回值：-1	表示错误：参数错误/未初始化
			0	未写入任何数据（缓冲区满）
		   >0 	实际写入的T的个数		
	*/
	int writeData(const T* pT, int nSize = 1)
	{
		//
		if (nullptr == pT || nSize <= 0 || !isInited())
		{
			return -1;
		}
		
		//
		std::unique_lock<std::mutex> lock(m_mtx);
		if (nSize > m_nSize - m_nUnreadSize) //缓冲区大小不足时，仅写入最前面的数据
		{
			nSize = m_nSize - m_nUnreadSize;
		}
			
		if (nSize > 0)
		{
			if (m_nWritePos + nSize <= m_nSize)
			{
				memcpy(&m_pBuffer[m_nWritePos], pT, nSize * sizeof(T));
			}
			else
			{
				memcpy(&m_pBuffer[m_nWritePos], pT, (m_nSize - m_nWritePos) * sizeof(T));
				memcpy(m_pBuffer, &pT[m_nSize - m_nWritePos], (nSize - (m_nSize - m_nWritePos)) * sizeof(T));
			}

			m_nUnreadSize += nSize;
			m_nWritePos += nSize;
			if (m_nWritePos >= m_nSize)
			{
				m_nWritePos %= m_nSize;
			}	
		}

		if (nSize > 0)
		{
			cv.notify_all();
		}
		return nSize;
	}
	
	/*
	readData:从环形缓冲区读取数据
	参数：  pT   	缓存
		   nSize 	nSize个sizeof(T)大小
		   mode		RINGBUFFER_GET_READ 读取数据，同时移动指针; RINGBUFFER_GET_COPY 只读取数据，不移动指针
	返回值：-1	表示错误：参数错误/未初始化
			0	未读取任何数据（缓冲区空）
		   >0 	实际读出的T的个数		
	*/
	int readData(T* pT, int nSize = 1, enum emRingbufferGetMode mode = RINGBUFFER_GET_READ)
	{
		//
		if (nullptr == pT || nSize <= 0 || !isInited())
		{
			return -1;
		}

		//
		std::unique_lock<std::mutex> lock(m_mtx);
		if (nSize > m_nUnreadSize)
		{
			nSize = m_nUnreadSize;
		}
			
		if (nSize > 0)
		{
			if (m_nReadPos + nSize <= m_nSize)
			{
				memcpy(pT, &m_pBuffer[m_nReadPos], nSize * sizeof(T));
			}
			else
			{
				memcpy(pT, &m_pBuffer[m_nReadPos], (m_nSize - m_nReadPos) * sizeof(T));
				memcpy(&pT[m_nSize - m_nReadPos], m_pBuffer, (nSize - (m_nSize - m_nReadPos)) * sizeof(T));
			}

			if(RINGBUFFER_GET_READ == mode) // RINGBUFFER_GET_COPY 时不移动指针
			{
				m_nUnreadSize -= nSize;
				m_nReadPos += nSize;
				if (m_nReadPos >= m_nSize)
				{
					m_nReadPos %= m_nSize;
				}	
			}
		}

		return nSize;
	}
	
	/*
	peekData:从环形缓冲区读取数据，不移动指针
	参数：  pT   	缓存
		   nSize 	nSize个sizeof(T)大小
		   offset	读取数据偏移量
	返回值：-1	表示错误：参数错误/未初始化
			0	未读取任何数据（缓冲区空）
		   >0 	实际读出的T的个数
	*/
	int peekData(T* pT, int nSize, int offset = 0)
	{
		if (nullptr == pT || nSize <= 0 || !isInited())
		{
			return -1;
		}

		std::unique_lock<std::mutex> lock(m_mtx);
		if ((offset + nSize) > m_nUnreadSize)
		{
			nSize = m_nUnreadSize - offset;
		}
		if (nSize < 0)
		{
			return -1;
		}

		int readPos = (m_nReadPos + offset) % m_nSize; 
		if (readPos + nSize <= m_nSize)
		{
			memcpy(pT, &m_pBuffer[readPos], nSize * sizeof(T));
		}
		else
		{
			memcpy(pT, &m_pBuffer[readPos], (m_nSize - readPos) * sizeof(T));
			memcpy(&pT[m_nSize - readPos], m_pBuffer, (nSize - (m_nSize - readPos)) * sizeof(T));
		}

		return nSize;
	}

	/*
	将循环缓冲区的部分数据丢弃（仅仅移动读指针）
	返回值：-1	表示错误：参数错误/未初始化 
			0	未丢弃任何数据（缓冲区空）
		   >0 	实际丢弃的T的个数		
	*/
	int discardData(int nSize)
	{
		//
		if (nSize <= 0 || !isInited())
		{
			return -1;
		}
		
		//
		std::unique_lock<std::mutex> lock(m_mtx);
		if (nSize > m_nUnreadSize)
		{
			nSize = m_nUnreadSize;
		}
			
		if (nSize > 0)
		{
			m_nUnreadSize -= nSize;
			m_nReadPos += nSize;
			if (m_nReadPos >= m_nSize)
			{
				m_nReadPos %= m_nSize;
			}
		}

		return nSize;
	}

	int getDataLength()
	{
		std::unique_lock<std::mutex> lock(m_mtx);
		return m_nUnreadSize;
	}

	int getSpaceLength()
	{
		std::unique_lock<std::mutex> lock(m_mtx);
		return (m_nSize - m_nUnreadSize);
	}

	SelectStatus selectWait(uint32_t milliseconds)
	{
		std::cv_status status;
		std::unique_lock<std::mutex> lock(m_mtx);
		if (m_nUnreadSize > 0)
		{
			return WAIT_OK;
		}

		if (milliseconds == 0)
		{
			//阻塞当前线程，直到条件变量被唤醒
			cv.wait(lock);
			return WAIT_OK;
		}
		else
		{
			//阻塞当前线程，直到条件变量被唤醒，或到指定时限时长后。milliseconds为时限，单位毫秒
			status = cv.wait_for(lock, std::chrono::milliseconds(milliseconds));
			if (status == std::cv_status::timeout)
			{
				return WAIT_TIMEOUT;
			}
			else if (status == std::cv_status::no_timeout)
			{
				return WAIT_OK;
			}
			else
			{
				return WAIT_ERROR;
			}
		}
	}

	/*
	退出数据等待接口：selectWait()
	返回值：None
	*/
	void cancelWait()
	{
		std::unique_lock<std::mutex> lock(m_mtx);
		cv.notify_all();
	}

private:
	inline bool isInited(void)
	{
		return (m_nSize > 0);
	}

private:
	T* m_pBuffer;		//缓冲区
	int m_nSize;		//缓冲区大小

	int m_nUnreadSize;	//未读取的数据大小

	int m_nWritePos;	//写入下标
	int m_nReadPos;		//读取下标

	std::condition_variable cv;
	std::mutex m_mtx;	//线程锁
};

}
using namespace ringbuf;
#endif //__RING_BUFFER__H__