/*
 * @Author: dding3
 * @Date: 2023-12-05 18:57:32
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-05 19:18:43
 * @Description:
 * @FilePath: /test/commonapi/test/rpc/project/shm/src/shm_test.cpp
 */
#include <iostream>
#include <sys/shm.h>
#include <cstring>

int main() {
    key_t key = ftok("/tmp", 'S');
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *data = (char*)shmat(shmid, nullptr, 0);

    std::string message = "Hello, IPC using shared memory!";
    std::memcpy(data, message.c_str(), message.size());

    shmdt(data);
    shmctl(shmid, IPC_RMID, nullptr);
    return 0;
}
