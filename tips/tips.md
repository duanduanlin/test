# 常用指令
## 修改selinux下文件type
chcon -t var_t /var/www/html/index.html
## 启动dbus-deamon
dbus-daemon --fork --session --address=unix:path=/tmp/dbus-o6ujiqBKsY
export DBUS_SESSION_BUS_ADDRESS=unix:path=/tmp/dbus-o6ujiqBKsY
## 设置链接库路径
export LD_LIBRARY_PATH=/oemdata/apps:/oemdata:/APP:/lib:/usr/lib
## MD5计算
md5sum xxx
## dos格式转换
dos2unix install.sh
## unzip 解压
unzip ohmyzsh-master.zip
## find指令
find . -name mcu_pipe
## 查看分区
df -h
du -sh
## 查看cpu占有率
top
## 查看内存信息
cat /proc/meminfo
## 查看系统信息
uname -a
## grep
grep -r "ql_log_print" ./
## 查看依赖关系
readelf -d xxx.so | grep NEEDED
## nm 查看符号信息
nm -D  external/ql_ec20/ql-ol-extsdk/lib/libql_peripheral.so | grep ql_log_print
## 生成patch和打patch
diff -u ori.c tar.c > update.patch
patch ori.c < update.patch
## git diff生成patch
git diff ./ > test.patch //生成patch
patch -p1 < test.patch //打patch
git apply test.patch //也可用这个命令打patch
## 清除内存缓存
echo 3 > /proc/sys/vm/drop_caches
## 文件切割
split -d -l 100000 -a 8 ConEmu-2023-06-21-p9656.log
## 软链接
ln -s libCommonAPI-DBus.so.3.1.12 libCommonAPI-DBus.so.3
## 查看库依赖
objdump -x test| grep NEED
