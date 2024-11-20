# 安装docker
sudo apt-get install docker.io
sudo usermod -aG docker $USER && newgrp docker

# 安装qemu
sudo apt-get update

sudo apt-get install qemu qemu-user-static

docker run --rm --privileged multiarch/qemu-user-static --reset -p yes

# 运行
docker run --name=humble-aarch64 --platform linux/arm64 -it <image-id> /bin/bash
