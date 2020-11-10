cmake_minimum_required(VERSION 3.10)
project(minio VERSION 0.1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# 如果用户安装到非 /usr/local 目录下，需要将下一行取消注释
# set(AWSSDK_ROOT_DIR "安装 aws-sdk-cpp 的目录")
find_package(AWSSDK REQUIRED COMPONENTS s3)
aux_source_directory(. MINIO_CPP_LIST)
add_library(minio SHARED ${MINIO_CPP_LIST})
target_link_libraries(minio ${AWSSDK_LIBRARIES})

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")
install(TARGETS minio LIBRARY DESTINATION lib)
install(FILES minio.h DESTINATION include)
