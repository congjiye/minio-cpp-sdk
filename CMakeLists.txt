cmake_minimum_required(VERSION 3.10)
project(minio)

# 如果用户安装到非 /usr/local 目录下，需要将下一行取消注释
# set(AWSSDK_ROOT_DIR "安装 aws-sdk-cpp 的目录")
find_package(AWSSDK REQUIRED COMPONENTS s3)
aux_source_directory(. MINIO_CPP_LIST)
add_library(minio ${MINIO_CPP_LIST} main.cpp)
target_link_libraries(minio ${AWSSDK_LINK_LIBRARIES})

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")
install(TARGETS minio LIBRARY DESTINATION lib)
install(FILES minio.h DESTINATION include)

add_executable(main main.cpp)
target_link_libraries(main minio)