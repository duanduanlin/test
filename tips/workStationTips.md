1.制作linux启动盘
2.设置bios启动选项
1.开机狂按F12进入bios。
2.修改存储类型
3.选择U盘启动
3.在ubuntu启动选项中以图像化界面进入
4.安装并覆盖原系统
5.重启，并按住shift+F8进入grub
6.选择高级模式，打开命令行
7.屏蔽掉风扇检测
sudo vim /etc/modprobe.d/blacklist.conf

#在文本最下端添加两行
blacklist nouveau
options nouveau modeset=0

8.配置硬盘
sudo fdisk -l

sudo fdisk /dev/sda

sudo fdisk /dev/nvme1n1
#格式化
sudo mkfs -t ext4 /dev/sda
sudo mkfs -t ext4 /dev/nvme1n1
#挂载
sudo mkdir /mnt/data

sudo chmod g+w /mnt/data/

sudo chgrp mpu /mnt/data


sudo vi /etc/fstab
/dev/sda /home ext4 errors=remount-ro 0 1
/dev/nvme1n1 /mnt/data ext4 defaults 0 0

sudo mkdir /mnt/tmp
sudo mount /dev/sda /mnt/tmp
sudo rsync -avx /home /mnt/tmp



cd /mnt/tmp

sudo rm -rf lost+found

sudo mv home/* .

sudo rm -rf home/



sudo passwd

su root
rm -rf /home/*

reboot



9. 创建用户，并添加到mpu组
sudo addgroup --gid 1002 mpu


sudo adduser username
sudo adduser username mpu

# 链接硬盘
ln -s /mnt/data/ /home/username/data

10.挂载share


sudo mkdir /mnt/share
sudo apt-get install cifs-utils
sudo mount -t cifs //10.18.67.49/share /mnt/share -o username=xzd,password=xzd



sudo cp /mnt/share/repo /usr/bin/

sudo chmod 777 /usr/bin/repo

11.安装软件
sudo apt-get update

sudo apt-get upgrade -y

#配置smb

sudo apt-get install samba -y
sudo apt-get install smbclient
sudo vim /etc/samba/smb.conf
[dding3]
path = /home/dding3
browseable = yes
available = yes
public = yes
writable = yes
force user = dding3
force group = dding3
create mask = 0755
directory mask = 0755

sudo smbpasswd -a dding3



安装配置vim

sudo apt-get install vim -y

sudo vim ~/.vimrc
colorscheme ron
:syntax on
filetype on
filetype plugin on
filetype indent on
set sts=4
set shiftwidth=4
set backspace=2
set tabstop=4
set showmode
set nu
set nohlsearch



安装工具

sudo apt-get install net-tools -y

sudo apt-get install wget -y

sudo apt-get install openssh-server -y

sudo apt-get install git -y

sudo apt-get install python -y

sudo apt-get install python3-pip -y

sudo apt-get install openjdk-8-jre -y



sudo pip3 install lxml

sudo pip3 install bsdiff4

sudo apt-get install tree -y

# ssh认证问题

sudo vim /etc/ssh/sshd_config


KexAlgorithms curve25519-sha256@libssh.org,ecdh-sha2-nistp256,ecdh-sha2-nistp384,ecdh-sha2-nistp521,diffie-hellman-group-exchange-sha256,diffie-hellman-group14-sha1,diffie-hellman-group-exchange-sha1,diffie-hellman-group1-sha1

sudo /etc/init.d/ssh restart

//给你自己的账号创建 ssh key
$ ssh-keygen
把 public key 设置到 git 服务器
cat ~/.ssh/id_rsa.pub

// 配置 git config
git config --global user.name dding3
git config --global user.email dding3@jmc.com.cn

ssh -p 29418 dding3@172.30.1.13



jbox02

sudo mkdir jbox02

cd jbox02

repo init -u ssh://dding3@172.30.1.13:29418/JMC/JBOX02/manifest -m jbox02_manifest.xml && repo sync



vbox01

sudo mkdir vbox01

cd vbox01

repo init -u ssh://$USER@172.30.1.13:29418/JMC/JBOX02/manifest -m vbox01_manifest.xml && repo sync



./platforms/ql_ag570/tools/toolchain/install.sh



sudo apt-get install m4 -y

# 替换openssl工具
1. sudo apt-get install make (Install compiling library Make)

2. wget https://www.openssl.org/source/openssl-1.0.2g.tar.gz (Download the latest OpenSSL 1.0.2g 源代码)

3. tar -xzvf openssl-1.0.2g.tar.gz (Extract the tar ball to the local directory)

4. cd openssl-1.0.2l (Enter extracted OpenSSL directory)

5. sudo ./config (Configure binaries for compiling)

6. sudo make install (install configured binaries)

7. sudo ln -sf /usr/local/ssl/bin/openssl `which openssl` (This will create a sym link to the new binaries), 这一步可能失败，替换 ‘which openssl’ 为 /usr/local/bin/openssl 再试一次

8. openssl version -v (Used to check the version of the Current OpenSSL binaries)



# 安装python2包
wget https://bootstrap.pypa.io/pip/2.7/get-pip.py
sudo python2 get-pip.py
sudo apt-get install python-dev
#python2 -m pip install python-lzo



远程桌面
sudo apt-get install gnome-session-flashback

sudo apt-get install tigervnc-standalone-server

执行vpcpasswd，设置连接密码
先执行一次vncserver命令，会初始化~/.vnc文件夹，然后用(vncserver -kill )杀死所有vnc进程
vim ~/.vnc/xstartup，填入下面的代码
#!/bin/sh

unset SESSION_MANAGER

unset DBUS_SESSION_BUS_ADDRESS

export XKL_XMODMAP_DISABLE=1

export XDG_CURRENT_DESKTOP="GNOME-Flashback:GNOME"

export XDG_MENU_PREFIX="gnome-flashback-"

[ -x /etc/vnc/xstartup ] && exec /etc/vnc/xstartup

[ -r $HOME/.Xresources ] && xrdb $HOME/.Xresources

xsetroot -solid grey #设置背景色

vncconfig -iconic & #

gnome-terminal & #连接后会直接打开一个terminal窗口

nautilus & #连接后会直接打开一个文件窗口

gnome-session --session=gnome-flashback-metacity --disable-acceleration-check &









#输入以下命令，目的是放开防火墙，端口可能是5901，也可能是5902，可以使用 ps -aux | grep vnc来确定，查找以下字段：-rfbport 5902

sudo ufw allow 5901

sudo ufw allow 5902 



#启动vncserver，以下命令表示接受2个用户连接，而且可以从外部连接进来。

vncserver :2 -localhost no



客户端连接
官网提供的安装包下载地址：https://sourceforge.net/projects/tigervnc/files/stable/1.13.0/
win安装包：https://github.com/lehaifeng000/tools/releases/download/1.0/vncviewer64-1.13.0.exe （已放置于：\\10.18.67.49\share\MPU\杨晓强\TMP）
mac安装包：https://github.com/lehaifeng000/tools/releases/download/1.0/TigerVNC-1.13.0.dmg
ubuntu20安装包：https://github.com/lehaifeng000/tools/releases/download/1.0/xtigervncviewer_1.13.0-1ubuntu1_amd64.deb
打开安装的tigervnc客户端，输入 服务器ip:端口号，如192.168.1.100:5901，端口号根据自己设置的进行调整
点击连接，输入密码，即可连接上服务器桌面