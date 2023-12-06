<!--
 * @Author: dding3
 * @Date: 2023-12-05 18:08:32
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-05 19:14:41
 * @Description:
 * @FilePath: /test/commonapi/test/rt_test/README.MD
-->
# 下载
git clone git://git.kernel.org/pub/scm/utils/rt-tests/rt-tests.git
or
wget https://mirrors.edge.kernel.org/pub/linux/utils/rt-tests/rt-tests-1.10.tar.gz
# 修改工具链
# 安装依赖库
apt-get install apt-file
apt-file search numa.h
apt-get install libnuma-dev
# 编译
make
