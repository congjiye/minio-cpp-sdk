cmake_minimum_required(VERSION 3.10)
project(minio VERSION 0.1.0)

# 设置 c++ 标准
set(CMAKE_CXX_STANDARD 11)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++11 -fPIC")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++11 -fPIC")
endif()

option(MINIO_BUILD_EXAMPLE "If enabled, all examples will be build as independent binary objects" ON)
option(MINIO_BUILD_SHARED "If enables, the minio sdk library will be built as shared objects; otherwise all libraries will be built as static objects" OFF)

# 如果 AWSSDK 安装目录不为默认路径需要设置 AWSSDK_DOOR_DIR 为安装的根目录
set(AWSSDK_ROOT_DIR "${PROJECT_SOURCE_DIR}/aws-sdk-cpp/build/install" CACHE STRING "You root directory of your installed path")

# 编译 minio 核心模组
add_subdirectory(src)

message(STATUS "Minio-CPP-SDK Version: ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

if (MINIO_BUILD_EXAMPLE)
    add_subdirectory(examples)
endif()

# 设置安装路径
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")
install(TARGETS minio EXPORT Minio LIBRARY DESTINATION lib)
install(FILES ${CMAKE_SOURCE_DIR}/src/minio.h ${CMAKE_SOURCE_DIR}/src/minio-exception.h DESTINATION include)
install(FILES ${CMAKE_SOURCE_DIR}/cmake/FindMinio.cmake DESTINATION lib/cmake)

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPAKC_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")

include(CPack)