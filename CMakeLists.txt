project(minio)

find_package(AWSSDK REQUIRED COMPONENTS s3)
aux_source_directory(. MINIO_CPP_LIST)
add_library(minio ${MINIO_CPP_LIST})
target_link_libraries(minio ${AWSSDK_LINK_LIBRARIES})