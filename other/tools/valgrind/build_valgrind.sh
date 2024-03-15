#!/bin/bash
set -e
set -x

SCRIPT=$0
if [ "${SCRIPT}" = "-bash" ] ; then
    SCRIPT=${BASH_SOURCE}
fi
MYDIR=$(cd "$(dirname "${SCRIPT}")"; pwd)

PKG_FILE=dbus-1.8.10.tar.gz
PKG_NAME=dbus-1.8.10

# need the patches from capicxx-dbus-runtime
CAPICXX_DBUS_PKG_FILE=capicxx-dbus-runtime-3.1.12.11.tar.gz
CAPICXX_DBUS_PKG_NAME=capicxx-dbus-runtime-3.1.12.11

mkdir -p ${BUILD_OBJS_PATH}
if [ -e ${MYDIR}/${PKG_FILE} ];then
    # prepare patches for dbus
    DBUS_RUNTIME_ROOT_DIR=${MYDIR}/../capicxx-dbus-runtime
    DBUS_RUNTIME_PKG_FILE=${DBUS_RUNTIME_ROOT_DIR}/${CAPICXX_DBUS_PKG_FILE}
    DBUS_RUNTIME_PKG_NAME=${CAPICXX_DBUS_PKG_NAME}
    rm -rf ${BUILD_OBJS_PATH}/${DBUS_RUNTIME_PKG_NAME}
    tar -zxf ${DBUS_RUNTIME_PKG_FILE} -C ${BUILD_OBJS_PATH}

    rm -rf ${BUILD_OBJS_PATH}/${PKG_NAME}
    tar -zxf ${MYDIR}/${PKG_FILE} -C ${BUILD_OBJS_PATH}
    if [ -e ${BUILD_OBJS_PATH}/${PKG_NAME} ];then
        cd ${BUILD_OBJS_PATH}/${PKG_NAME}
        # patching
        for i in ${BUILD_OBJS_PATH}/${DBUS_RUNTIME_PKG_NAME}/src/dbus-patches/*.patch; do patch -p1 < $i; done

        ./configure CC=${GEN_CC} --host=arm-oe-linux-gnueabi --prefix=${INSTALL_PREFIX} CFLAGS="${GEN_CFLAGS}"
        make -j4
        make install
        echo "success building ${PKG_NAME}."
    else
        echo "Error: extract package fail!!"
    fi
else
    echo "Error: missing package: ${MYDIR}/${PKG_FILE}!!"
fi

# SOURCE_DIR=${MYDIR}/dbus-1.8.10

# # PLATFORM_SDK_PATH=${MYDIR}/../../platforms/ql_ec20
# # PLATFORM_SDK_VERSION="a07"
# # INSTALL_PREFIX=${PLATFORM_SDK_PATH}/sdk/a07/prebuild

# # export PATH=$PATH:${MYDIR}/../../external/sdk/ql_ec20/${PLATFORM_SDK_VERSION}/ql-ol-crosstool/sysroots/x86_64-oesdk-linux/usr/bin/arm-oe-linux-gnueabi/


# # Need the common api patch
# DBUS_RUNTIME_ROOT_DIR=${MYDIR}/../capicxx-dbus-runtime
# if [ ! -d ${DBUS_RUNTIME_ROOT_DIR}/capicxx-dbus-runtime-3.1.5 ];then
#     tar -zxf ${DBUS_RUNTIME_ROOT_DIR}/capicxx-dbus-runtime-3.1.5.tar.gz -C ${DBUS_RUNTIME_ROOT_DIR}
# fi

# if [ ! -d ${SOURCE_DIR} ];then
#     tar -zxf ${MYDIR}/dbus-1.8.10.tar.gz -C ${MYDIR}
#     cd ${SOURCE_DIR}
#     for i in ${DBUS_RUNTIME_ROOT_DIR}/capicxx-dbus-runtime-3.1.5/src/dbus-patches/*.patch; do patch -p1 < $i; done
# fi

# cd ${SOURCE_DIR}

# ./configure CC=arm-oe-linux-gnueabi-gcc --host=arm-oe-linux-gnueabi --prefix=${INSTALL_PREFIX}
# make -j4
# make install
