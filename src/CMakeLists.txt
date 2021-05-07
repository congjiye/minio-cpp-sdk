cmake_minimum_required(VERSION 3.17)

# 如果用户安装到非 /usr/local 目录下，需要将下一行取消注释
# set(AWSSDK_ROOT_DIR "安装 aws-sdk-cpp 的目录")

find_package(AWSSDK REQUIRED COMPONENTS s3)
aux_source_directory(. MINIO_CPP_LIST)

# list(APPEND MINIO_CPP_LIST minio-exception.h)

add_library(minio SHARED ${MINIO_CPP_LIST})
target_link_libraries(minio PRIVATE ${AWSSDK_LINK_LIBRARIES})