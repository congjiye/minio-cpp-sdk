# FindMinio
# ---------
#
# Find the minio-cpp-sdk libraries
# 
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# The following variables will be defined:
#
# ``Minio_CPP_FOUND`` True if Minio_CPP found on the local system
#
# ``Minio_CPP_INCLUDE_DIRS`` Location of Minio_CPP header files
#
# ``Minio_CPP_LIBRARY_DIRS`` Location of Minio_CPP libraries
#
# ``Minio_CPP_LIBRARIES`` List of the Minio_CPP libraries found

find_path(Minio_CPP_INCLUDE_DIRS minio.h /usr/local/include/minio-cpp-sdk ${Minio_CPP_ROOT_DIR}/include)

find_library(Minio_CPP_LIBRARIES libminio.so /usr/local/lib ${Minio_CPP_ROOT_DIR}/lib)

message(STATUS ${Minio_CPP_INCLUDE_DIRS} ${Minio_CPP_LIBRARIES})
if(Minio_CPP_INCLUDE_DIRS AND Minio_CPP_LIBRARIES)
    set(Minio_CPP_FOUND true)
endif(Minio_CPP_INCLUDE_DIRS AND Minio_CPP_LIBRARIES)

if(Minio_CPP_FOUND)
    if(NOT Minio_FIND_QUIETLY)
        message(STATUS "Found Minio_CPP: ${Minio_CPP_LIBRARIES}")
    endif(NOT Minio_FIND_QUIETLY)
else(Minio_CPP_FOUND)
    if(Minio_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find minio library")
    endif(Minio_FIND_REQUIRED)
endif(Minio_CPP_FOUND)