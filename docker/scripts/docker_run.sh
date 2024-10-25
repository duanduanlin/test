#/bin/bash

function print_color {
    tput setaf $1
    echo "$2"
    tput sgr0
}

function print_error {
    print_color 1 "$1"
}

function print_warning {
    print_color 3 "$1"
}

function print_info {
    print_color 2 "$1"
}

DOCKER_USER="root"
CONTAINER_NAME="humble"
IMAGE_NAME="ros:humble"
WORK_DIR="/home/work"

if [ "$(docker ps -a --quiet --filter status=exited --filter name=^/$CONTAINER_NAME$)" ]; then
	print_info "Start container: $CONTAINER_NAME"
	docker start $CONTAINER_NAME
fi

if [ "$(docker ps -a --quiet --filter status=running --filter name=^/$CONTAINER_NAME$)" ]; then
    print_info "Attaching to running container: $CONTAINER_NAME"
    docker exec -i -t -u $DOCKER_USER --workdir $WORK_DIR $CONTAINER_NAME /bin/bash $@
    exit 0
fi

print_info "running container: $CONTAINER_NAME"
docker run \
--privileged \
--network host \
--name=$CONTAINER_NAME \
-v /dev:/dev \
-v ~/work:/home/work \
--workdir $WORK_DIR \
-it $IMAGE_NAME

