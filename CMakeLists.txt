cmake_minimum_required(VERSION 3.10)
project(minio VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

option(MINIO_BUILD_EXAMPLE "option for build example" ON)

# AWSSDK_ROOT_DIR 设置无效，改用 CMAKE_PREFIX_PATH 代替，具体可以查看 README
# set(AWSSDK_ROOT_DIR "/usr/local" CACHE PATH "AWSSDK Installed dir.")

# 编译 minio 核心模组
add_subdirectory(src)

message(STATUS "Minio-CPP-SDK Version: ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

if (MINIO_BUILD_EXAMPLE)
    add_subdirectory(examples)
endif()

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")
install(TARGETS minio LIBRARY DESTINATION lib)
install(FILES ${CMAKE_SOURCE_DIR}/src/minio.h ${CMAKE_SOURCE_DIR}/src/minio-exception.h DESTINATION include)
