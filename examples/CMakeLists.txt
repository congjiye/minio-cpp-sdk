cmake_minimum_required(VERSION 3.17)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(list_buckets list_buckets.cc)
target_link_libraries(list_buckets minio)

add_executable(bucket_exists bucket_exists.cc)
target_link_libraries(bucket_exists minio)

add_executable(make_bucket make_bucket.cc)
target_link_libraries(make_bucket minio)

add_executable(remove_bucket remove_bucket.cc)
target_link_libraries(remove_bucket minio)

add_executable(get_object get_object.cc)
target_link_libraries(get_object minio)

add_executable(remove_objcet remove_objcet.cc)
target_link_libraries(remove_objcet minio)

add_executable(copy_objcet copy_objcet.cc)
target_link_libraries(copy_objcet minio)