pushd $FW_TARGETDIR > /dev/null
###
 # @Author: hanson
 # @Date: 2024-09-18 15:45:48
 # @LastEditors: hanson
 # @LastEditTime: 2024-11-21 10:56:23
 # @Description:
 # @FilePath: \src\autocity_uros_setup\config\zephyr\generic\make_run.sh
###

ZEPHYR_BUILD_DIR="$FW_TARGETDIR/build/zephyr"
WORK_SPACE_DIR="$FW_TARGETDIR/.."

unset UROS_APP

UROS_APP=$(head -n1 $FW_TARGETDIR/APP | tail -n1)

if [ -v UROS_CUSTOM_APP_FOLDER ]; then
    export UROS_APP_FOLDER="$UROS_CUSTOM_APP_FOLDER/$UROS_APP"
else
    export UROS_APP_FOLDER="$FW_TARGETDIR/autocity_uros_apps/apps/$UROS_APP"
fi

if [ -d "$UROS_APP_FOLDER" ]; then
    echo "Selected app: $UROS_APP"
else
    echo "App not found: $UROS_APP"
    exit 1
fi

# Host platform (=native_posix) is special, as flashing is actually just executing the binary
if [ "$PLATFORM" = "host" ]; then

    if [ ! -f "$ZEPHYR_BUILD_DIR/zephyr.exe" ]; then
        echo "Error: $ZEPHYR_BUILD_DIR/zephyr.exe not found. Please compile before make run."
        exit 1
    fi

    module=$UROS_APP                         #模块名

    common_list=(
        "$WORK_SPACE_DIR/install/micro_ros_agent"
        "$WORK_SPACE_DIR/install/micro_ros_msgs"
        "$WORK_SPACE_DIR/install/setup.bash
        "$WORK_SPACE_DIR/install/local_setup.bash
        "$WORK_SPACE_DIR/install/_local_setup_util_ps1.py
        "$WORK_SPACE_DIR/install/_local_setup_util_sh.py
        )

    if [ "$UROS_APP" = "ucanbus" ]; then
        pack_list=(
            "$WORK_SPACE_DIR/install/uchassis_msgs"
            "$WORK_SPACE_DIR/install/ucontrol_msgs"
            )
        file_list=(
            "$ZEPHYR_BUILD_DIR/zephyr.elf"
            "${UROS_APP_FOLDER}/config"
            "${UROS_APP_FOLDER}/scripts"
        )
    elif [ "$UROS_APP" = "udepot" ]; then
        pack_list=(
            "$WORK_SPACE_DIR/install/udepot_cmd_msgs"
            "$WORK_SPACE_DIR/install/udepot_status_msgs"
            )
        file_list=(
            "$ZEPHYR_BUILD_DIR/zephyr.elf"
            "${UROS_APP_FOLDER}/config"
            "${UROS_APP_FOLDER}/scripts"
        )
    else
        echo "Error: unknown app $UROS_APP"
        exit 1
    fi


    PACKAGE_NAME=${module}
    echo "package for ${PACKAGE_NAME}"

    echo "driname: $(dirname $0)"
    runScript=$(dirname $0)/run.sh
    echo "runScript=$runScript"

    rm -rf output
    mkdir -p output/${module}

    for common in ${common_list[*]}
    do
        cp -r $common output/
    done

    for file in ${file_list[*]}
    do
        cp -r $file output/${module}/
    done

    for pack in ${pack_list[*]}
    do
        cp -r $pack output/
    done

    tar -zcf $module.tar.gz output

    cat $runScript $module.tar.gz > ${PACKAGE_NAME}.run
    rm $module.tar.gz
    chmod +x ${PACKAGE_NAME}.run
    rm -rf output
    # $ZEPHYR_BUILD_DIR/zephyr.exe

else

    if [ ! -f "$ZEPHYR_BUILD_DIR/zephyr.bin" ]; then
        echo "Error: $ZEPHYR_BUILD_DIR/zephyr.bin not found. Please compile before make run."
        exit 1
    fi
fi
popd > /dev/null
