#pragma once
#include <string>

extern std::string EXTERN_TEST;

/**
 * Minio bascit auth configuration
 * 
 * access_key: your minio access_key
 * secret_key: your minio secret_key
 * address: your minio server address
 */
struct AuthStruct
{
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
struct ObjectStruct
{
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
bool getObject(const AuthStruct &auth, const ObjectStruct &object);

/**
 * Upload object to your minio server
 * 
 * Params:
 * - auth: Minio basic auth configuration
 * - objcet: Minio upload object information
 */
bool putObject(const AuthStruct &auth, const ObjectStruct &object);

/**
 * Create a bucket
 * 
 * Params:
 * - auth: Minio basic auth configuration
 * - buckName: create bucket name
 */
bool makeBucket(const AuthStruct &auth, const std::string bucketName);

namespace Minio
{
    using namespace std;
    using ClientConfiguration = void *;
    using SDKOptions = void *;
    using S3Client = void *;

    class Minio
    {
    public:
        /**
         * @brief Minio 构造函数
         * @param  address          Minio 服务所在地址，可以使用 IP:Port 的形式
         * @param  access_key       Minio 登录使用的 access_key
         * @param  secret_key       Minio 登录使用的 secret_key
         */
        Minio(string address, string access_key, string secret_key, bool secure = false);
        ~Minio();

        /**
         * @brief 从 Minio 中下载文件
         * @param  from_bucket      文件所在的桶名
         * @param  object_key       文件的路径
         * @param  file_path        文件保存的路径
         * @return 如何下载成功返回 true 否则会打印失败信息并返回 false
         */
        bool getObject(string from_bucket, string object_key, string file_path);

        /**
         * @brief upload data from a file to an object
         * @param bucket_name       name of bucket
         * @param file_path         absolute path of file
         * @param file_name         name of file
         * @return if file upload is success returned true, if file upload is error returned false
         */
        bool putObject(string bucket_name, string file_path,string file_name);




    private:
        const string _address;
        const string _access_key;
        const string _secret_key;
        const bool _secure;

        SDKOptions _options;
        ClientConfiguration _config;
        S3Client _s3_client;
    };
} // namespace Minio