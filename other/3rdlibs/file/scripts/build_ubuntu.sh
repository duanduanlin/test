#!/bin/bash

g++ -std=c++11 \
../../shutil/src/shutil.cpp \
../src/crypto.cpp \
../src/file_manage.cpp \
../../../../apps/tests/os/file/src/file_test.cpp \
-I ../../shutil/include \
-I ../include \
-I ../test \
-lcrypto -lpthread -o file_test