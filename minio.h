#pragma once
#include <string>

/**
 * Minio bascit auth configuration
 * 
 * access_key: your minio access_key
 * secret_key: your minio secret_key
 * address: your minio server address
 */
struct AuthStruct {
    std::string access_key;
    std::string secret_key;
    std::string address;
};

/**
 * Minio download object information
 * 
 * from_bucket: your download bucket name
 * object_key: normally file name
 * file_path: local file path
 */
struct ObjectStruct {
    std::string from_bucket;
    std::string object_key;
    std::string file_path;
};

/**
 * Download object from your minio server
 * 
 * Params:
 * - auth: Minio basic auth configuration
 * - object: Minio download object information
 * - region: your minio region
 * 
 * Return:
 * if true you have downloaded object successfully else not
 */
bool getObject(const AuthStruct& auth, const ObjectStruct& object);

/**
 * Upload object to your minio server
 * 
 * Params:
 * - auth: Minio basic auth configuration
 * - objcet: Minio upload object information
 */
bool putObject(const AuthStruct& auth, const ObjectStruct& object);

/**
 * Create a bucket
 * 
 * Params:
 * - auth: Minio basic auth configuration
 * - buckName: create bucket name
 */
bool makeBucket(const AuthStruct& auth, const std::string bucketName);