#!/bin/bash

source_path=$(readlink -f $(dirname $0))
directory=$(echo ${source_path} | awk -F "/" '{print $NF}')
user=$(whoami)
current_path=$(pwd)

if [ ${directory} != "minio-cpp-sdk" ];then
    echo "You should run this script in minio-cpp-sdk directory"
    exit 1
fi

if [ ! -x $(command -v git) ];then
    echo "Error: git is not installed." >&2
    exit 1
fi

dependencies="libcurl4-openssl-dev libssl-dev uuid-dev zlib1g-dev libpulse-dev"
if [ ${user} == "root" ];then
    apt install -y ${dependencies}
else
    sudo apt install -y ${dependencies}
fi

cd ${source_path}
git submodule update --init --recursive

build_type=Release
if [[ $# -lt 1 ]];then
    echo "Build Type: Release"
elif [[ $1 != "Debug" && $1 != "Release" ]];then
    echo "Error Type: ${1}"
    echo "Legal parameters is Debug or Release"
else
    build_type=${1}
fi

cd aws-sdk-cpp
mkdir build && cd build
cmake -DBUILD_ONLY="s3" -DCMAKE_BUILD_TYPE=${build_type} -DBUILD_SHARED_LIBS=OFF -DCMAKE_INSTALL_PREFIX=$(pwd)/install ..
make && make install

cd ../..
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=${build_type} ..
make && make install

echo "All Done."