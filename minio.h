#pragma once
#include <string>
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
        bool GetObject(string from_bucket, string object_key, string file_path);

        /**
         * @brief upload data from a file to an object
         * @param bucket_name       name of bucket
         * @param file_path         absolute path of file
         * @param file_name         name of file
         * @return if file upload is success returned true, if file upload is error returned false
         */
        bool putObject(string bucket_name, string file_path,string file_name);

        /**
         * @brief 创建一个存储桶
         * @param  bucket_name      存储桶名称
         * @return 存储桶创建成功返回 true 否则打印识别信息并返回 false
         */
        bool makeBucket(string bucket_name);


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