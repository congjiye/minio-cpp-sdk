#include <iostream>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/s3/model/CreateBucketRequest.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/s3/model/HeadBucketRequest.h>
#include <sys/stat.h>
#include <fstream>

#include "minio.h"

namespace Minio
{
    Minio::Minio(string address, string access_key, string secret_key, bool secure) : kAddress(address),
                                                                                      kAccessKey(access_key),
                                                                                      kSecretKey(secret_key),
                                                                                      kSecure(secure)
    {
        options_ = new Aws::SDKOptions;
        auto options = reinterpret_cast<Aws::SDKOptions *>(options_);
        Aws::InitAPI(*options);

        config_ = new Aws::Client::ClientConfiguration;
        auto config = reinterpret_cast<Aws::Client::ClientConfiguration *>(config_);
        config->endpointOverride = kAddress;

        if (kSecure)
        {
            config->scheme = Aws::Http::Scheme::HTTPS;
            config->verifySSL = true;
        }
        else
        {
            config->scheme = Aws::Http::Scheme::HTTP;
            config->verifySSL = false;
        }

        s3_client_ = new Aws::S3::S3Client(Aws::Auth::AWSCredentials(kAccessKey, kSecretKey), *config,
                                           Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Never, false);
    }

    Minio::~Minio()
    {
        auto options = reinterpret_cast<Aws::SDKOptions *>(options_);
        Aws::ShutdownAPI(*options);

        delete reinterpret_cast<Aws::SDKOptions *>(options_);
        delete reinterpret_cast<Aws::Client::ClientConfiguration *>(config_);
        delete reinterpret_cast<Aws::S3::S3Client *>(s3_client_);
    }

    bool Minio::GetObject(string from_bucket, string object_key, string file_path)
    {
        auto s3_client = reinterpret_cast<Aws::S3::S3Client *>(s3_client_);
        Aws::S3::Model::GetObjectRequest request;
        request.SetBucket(from_bucket);
        request.SetKey(object_key);

        auto outcome = s3_client->GetObject(request);

        if (outcome.IsSuccess())
        {
            Aws::OFStream local_file;
            local_file.open(file_path, std::ios::out | std::ios::binary);
            local_file << outcome.GetResultWithOwnership().GetBody().rdbuf();
            return true;
        }
        else
        {
            auto err = outcome.GetError();
            std::cerr << "Error: GetObject: " << err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
            return false;
        }
    }

    bool Minio::PutObject(string bucket_name, string file_path, string file_name)
    {
        struct stat buffer;

        if (stat(file_path.c_str(), &buffer) == -1)
        {
            std::cout << "Error PutObject: File " << file_name << " does not exist"
                      << "\n";
            return false;
        }
        auto s3_client = reinterpret_cast<Aws::S3::S3Client *>(s3_client_);
        Aws::S3::Model::PutObjectRequest request;
        request.SetBucket(bucket_name);
        request.SetKey(file_name);

        std::shared_ptr<Aws::IOStream> input_data = Aws::MakeShared<Aws::FStream>("sSampleAllocationtTag", file_path.c_str(), std::ios_base::in | std::ios_base::binary);
        request.SetBody(input_data);
        auto outcome = s3_client->PutObject(request);

        if (outcome.IsSuccess())
        {
            std::cout << "Added object " << file_name << " to bucket ";
            return true;
        }
        std::cout << "Error:putObjeact: " << outcome.GetError().GetMessage() << "\n";
        return false;
    }

    void Minio::MakeBucket(string bucket_name)
    {
        auto s3_client = reinterpret_cast<Aws::S3::S3Client *>(s3_client_);
        Aws::S3::Model::CreateBucketRequest request;
        request.SetBucket(bucket_name);

        auto outcome = s3_client->CreateBucket(request);

        if (!outcome.IsSuccess())
        {
            auto err = outcome.GetError();
            throw S3ErrorException(err.GetExceptionName().empty() ? "HttpException" : err.GetExceptionName(), err.GetMessage());
        }
    }

    bool Minio::ListBuckets(vector<string> &buckets)
    {
        auto s3_client = reinterpret_cast<Aws::S3::S3Client *>(s3_client_);
        auto outcome = s3_client->ListBuckets();
        vector<string>().swap(buckets);

        if (outcome.IsSuccess())
        {
            auto resp = outcome.GetResult().GetBuckets();

            for (auto &bucket : resp)
            {
                buckets.push_back(bucket.GetName());
            }
            return true;
        }
        else
        {
            std::cerr << "Error: ListBuckets: " << outcome.GetError().GetMessage() << std::endl;
            return false;
        }
    }

    bool Minio::BucketExists(string bucket_name)
    {
        auto s3_client = reinterpret_cast<Aws::S3::S3Client *>(s3_client_);
        Aws::S3::Model::HeadBucketRequest request;
        request.SetBucket(bucket_name);

        auto outcome = s3_client->HeadBucket(request);
        if (!outcome.IsSuccess())
        {
            auto err = outcome.GetError();
            std::cerr << "Error: BucketExists: "
                      << err.GetExceptionName() << "\n"
                      << err.GetMessage() << std::endl;
            return false;
        }
        return true;
    }
} // namespace Minio