# minio-cpp-sdk

该项目提供 Minio C++ 版本的 SDK。使用方式和 Minio 官方提供的版本类似, 使用方便，使用时无外部依赖。用户可以查看 [Minio 官网](http://docs.minio.org.cn/docs/master/python-client-api-reference) 查看所有 API 用法。

![](https://img.shields.io/badge/platform-linux-orange.svg)
![](https://img.shields.io/badge/language-c%2B%2B-blue.svg)

## 安装 SDK

你可以使用源码进行编译，也可以使用我们预编译好的包使用。[预编译包地址](https://github.com/JyCAydon/minio-cpp-sdk/releases/tag/V0.1.0)

### 源码编译

Minio C++ SDK 是基于 AWS S3 的 SDK 二次开发的，因此在源码编译 SDK 前我们需要安装 aws-sdk-cpp。

#### 下载 aws-sdk-cpp

```bash
https://github.com/JyCAydon/minio-cpp-sdk.gitcd minio-cpp
cd minio-cpp
git submodule init && git submodule update
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
-DCMAKE_INSTALL_PREFIX  | 编译后安装目录        | 安装目录，默认为 /usr/local

```bash
cd aws-sdk-cpp

# Release 版本
mkdir cmake-build-release
cd cmake-build-release
cmake -DBUILD_ONLY="s3" -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DCMAKE_INSTALL_PREFIX=<you-install-path> ..
make
make install

# Debug 版本
mkdir cmake-build-debug
cd cmake-build-debug
cmake -DBUILD_ONLY="s3" -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=OFF -DCMAKE_INSTALL_PREFIX=<you-install-path> ..
make
make install
```

#### 编译 minio-cpp-sdk

用户可以通过修改 `-DCMAKE_PREFIX_INSTALL` 来设置安装目录，默认目录为当前源码文件下的 `install` 文件夹。

```bash
cd minio-cpp
mkdir build && cd build
cmake ..
make && make install
```

## 如何使用

所有接口方法都有相应的注释，用户可以自行查看 minio.h 文件查看相应的接口使用方法。

### CMAKE 使用

```text
include_directories("your-install-path/minio/include")
link_directories("your-install-path/minio/lib)
target_link_libraries(project PRIVATE minio)
```

### 下载文件

```c++
#include "minio.h"

int main()
{
    Minio::Minio minio("play.min.io",
                       "Q3AM3UQ867SPQQA43P2F",
                       "zuf+tfteSlswRu7BJ86wekitnifILbZam1KYY3TG");
    try
    {
        minio.GetObject("lib", "word.txt", "word.txt");
    }
    catch (const Minio::MinioException &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
```

## 测试

目前接口使用 `valgrind` 进行测试。下载文件接口已通过测试，可以放心使用。

## TODO

- [ ] 完善所有接口实现
- [ ] 并行接口测试
