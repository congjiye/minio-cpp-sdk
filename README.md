# minio-cpp

该项目提供 Minio C++ 版本的 SDK。使用方式和 Minio 官方提供的版本类似。用户可以查看 [Minio 官网](http://docs.minio.org.cn/docs/master/python-client-api-reference) 查看所有 API 用法。

![](https://img.shields.io/badge/platform-linux-orange.svg)
![](https://img.shields.io/badge/language-c%2B%2B-blue.svg)

## 安装 SDK

你可以使用源码进行编译，也可以使用我们预编译好的包使用。[预编译包地址](http://192.168.1.75:8880/congjiye/minio-cpp/-/releases)

### 源码编译

Minio C++ SDK 是基于 AWS S3 的 SDK 二次开发的，因此在源码编译 SDK 前我们需要安装 aws-sdk-cpp。

#### 下载 aws-sdk-cpp

```bash
git clone https://github.com/aws/aws-sdk-cpp.git
```

#### 安装依赖

```bash
sudo apt-get install libcurl4-openssl-dev libssl-dev uuid-dev zlib1g-dev libpulse-dev
```

#### 编译 aws-sdk-cpp

用户可以根据自行需要选择使用 release 或者 debug 版本。通过修改 `-DCMAKE_BUILD_TYPE` 选择编译版本。用户可以通过修改 `-DCMAKE_PREFIX_INSTALL` 来设置安装目录。

CMAKE 选项 | 说明 | 参数
--|--|--
-DCMAKE_BUILD_TYPE      | 编译版本             | Release / Debug
-DBUILD_SHARED_LIBS     | 编译动态或静态库      | OFF / ON
-DCMAKE_PREFIX_INSTALL  | 编译后安装目录        | 安装目录，默认为 /usr/local

```bash
# Release 版本
mkdir cmake-build-release
cd cmake-build-release
cmake -DBUILD_ONLY="s3" -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DCMAKE_PREFIX_INSTALL=<you-install-path> ..
make
make install

# Debug 版本
mkdir cmake-build-debug
cd cmake-build-debug
cmake -DBUILD_ONLY="s3" -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=OFF -DCMAKE_PREFIX_INSTALL=<you-install-path> ..
make
make install
```

#### 编译 minio-cpp

```bash
git clone http://192.168.1.75:8880/congjiye/minio-cpp.git
cd minio-cpp
mkdir build && cd build
cmake ..
make
```

## 如何使用

所有接口方法都有相应的注释，用户可以自行查看 minio.h 文件查看相应的接口使用方法。

### 下载文件

```c++
#include "minio.h"

int main()
{
    Minio::Minio minio("192.168.1.74:9001", "thunisoft", "6789@jkl");
    minio.getObject("lib", "demo.cpp", "/root/Projects/ASRProjects/aws-minio/demo.cpp");
}
```

## 测试

目前接口使用 `valgrind` 进行测试。下载文件接口已通过测试，可以放心使用。

## TODO

1. 完善所有接口实现
2. 并行接口测试