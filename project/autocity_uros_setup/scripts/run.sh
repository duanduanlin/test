#!/bin/bash
lines=12
tail -n +$lines $0 > output.tar.gz
tar -zxf output.tar.gz
cp -rf output/* /autocity/sweeper/install
if [[ "$1" == "-s" || "$1" == "--save" ]];then
    echo "save output"
else
    rm -rf output.tar.gz output
fi
exit 0
