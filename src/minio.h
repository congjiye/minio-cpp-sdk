#pragma once
#include <string>
#include <vector>

#include "minio-exception.h"
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
         */
        void GetObject(string from_bucket, string object_key, string file_path);

        /**
         * @brief upload data from a file to an object
         * @param bucket_name       name of bucket
         * @param file_path         absolute path of file
         * @param file_name         name of file
         * @return if file upload is success returned true, if file upload is error returned false
         */
        void PutObject(string bucket_name, string file_path, string file_name);

        /**
         * @brief 拷贝存储桶文件
         * @param  from_bucket      源存储桶名称
         * @param  from_file        源对象名称
         * @param  to_bucket        目标存储桶名称
         * @param  to_file          目标对象名称
         */
        void CopyObjcet(string from_bucket, string from_file, string to_bucket, string to_file = "");

        /**
         * @brief 删除一个对象
         * @param  bucket_name      存储桶名称
         * @param  objcet_key       存储桶里的对象名称
         */
        void RemoveObject(string bucket_name, string objcet_key);

        /**
         * @brief 创建一个存储桶
         * @param  bucket_name      存储桶名称
         */
        void MakeBucket(string bucket_name);

        /**
         * @brief 显示所有的存储桶
         * @param  buckets          返回的所有桶信息
         * @return true 
         */
        void ListBuckets(vector<string> &buckets);

        /**
         * @brief 判断存储桶是否存在
         * @param  bucket_name      存储桶名称
         * @return 如果存储桶存在则返回 true 否则返回 false
         */
        bool BucketExists(string bucket_name);

        /**
         * @brief 删除存储桶
         * @param  bucket_name      存储桶名
         */
        void RemoveBucket(string bucket_name);

    private:
        const string kAddress;
        const string kAccessKey;
        const string kSecretKey;
        const bool kSecure;

        SDKOptions options_;
        ClientConfiguration config_;
        S3Client s3_client_;
    };
} // namespace Minio