#include <iostream>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/s3/model/CreateBucketRequest.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <sys/stat.h>
#include <fstream>

#include "minio.h"

struct AwsStruct
{
    Aws::String address;    // minio server address
    Aws::String accessKey;  // access key
    Aws::String secretKey;  // secrect key
    Aws::String objectKey;  // object name
    Aws::String filePath;   // local file path
    Aws::String fromBucket; // bucket name
};

bool doGetObject(const AwsStruct &customConfig);

bool doPutObject(const AwsStruct &customConfig);

bool doMakeBucket(const AuthStruct &auth, const Aws::String &bucketName);

bool getObject(const AuthStruct &auth, const ObjectStruct &object)
{
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    bool res = false;
    {
        AwsStruct customConfig = {
            auth.address, auth.access_key, auth.secret_key,
            object.object_key, object.file_path, object.from_bucket};
        res = doGetObject(customConfig);
    }
    Aws::ShutdownAPI(options);
    return res;
}

bool putObject(const AuthStruct &auth, const ObjectStruct &object)
{
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    bool res = false;
    {
        AwsStruct customConfig = {
            auth.address, auth.access_key, auth.secret_key,
            object.object_key, object.file_path, object.from_bucket};
        res = doPutObject(customConfig);
    }
    Aws::ShutdownAPI(options);
    return res;
}

bool makeBucket(const AuthStruct &auth, const std::string bucketName)
{
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    bool res = false;
    {
        const Aws::String bucket_name = bucketName;
        res = doMakeBucket(auth, bucket_name);
    }
    Aws::ShutdownAPI(options);
    return res;
}

bool doGetObject(const AwsStruct &customConfig)
{
    Aws::Client::ClientConfiguration config;

    config.endpointOverride = customConfig.address;
    config.scheme = Aws::Http::Scheme::HTTP;
    config.verifySSL = false;

    Aws::S3::S3Client s3_client(Aws::Auth::AWSCredentials(customConfig.accessKey, customConfig.secretKey), config,
                                Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Never, false);

    Aws::S3::Model::GetObjectRequest object_request;
    object_request.SetBucket(customConfig.fromBucket);
    object_request.SetKey(customConfig.objectKey);

    Aws::S3::Model::GetObjectOutcome get_object_outcome = s3_client.GetObject(object_request);

    if (get_object_outcome.IsSuccess())
    {
        Aws::OFStream local_file;
        local_file.open(customConfig.filePath, std::ios::out | std::ios::binary);
        local_file << get_object_outcome.GetResultWithOwnership().GetBody().rdbuf();
        return true;
    }
    else
    {
        auto err = get_object_outcome.GetError();
        std::cerr << "Error: GetObject: " << err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
        return false;
    }
}

bool doPutObject(const AwsStruct &customConfig)
{
    struct stat buffer;

    if (stat(customConfig.filePath.c_str(), &buffer) == -1)
    {
        std::cerr << "Error: PutObject: File '" << customConfig.filePath << "' does not exist." << std::endl;
        return false;
    }

    Aws::Client::ClientConfiguration config;
    config.endpointOverride = customConfig.address;
    config.scheme = Aws::Http::Scheme::HTTP;
    config.verifySSL = false;

    Aws::S3::S3Client s3_client(Aws::Auth::AWSCredentials(customConfig.accessKey, customConfig.secretKey), config,
                                Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Never, false);

    Aws::S3::Model::PutObjectRequest request;
    request.SetBucket(customConfig.fromBucket);
    request.SetKey(customConfig.objectKey);

    std::shared_ptr<Aws::IOStream> input_data =
        Aws::MakeShared<Aws::FStream>("SmapleAllocationTag", customConfig.filePath.c_str(), std::ios_base::in | std::ios_base::binary);
    request.SetBody(input_data);

    Aws::S3::Model::PutObjectOutcome outcome = s3_client.PutObject(request);

    if (outcome.IsSuccess())
    {
        std::cout << "Add object '" << customConfig.objectKey << "' to bucket '" << customConfig.fromBucket << "'." << std::endl;
        return true;
    }
    else
    {
        std::cerr << "Error: PutObject: " << outcome.GetError().GetMessage() << std::endl;
        return false;
    }
}

bool doMakeBucket(const AuthStruct &auth, const Aws::String &bucketName)
{
    Aws::Client::ClientConfiguration config;

    const Aws::String address = auth.address;
    const Aws::String accessKey = auth.access_key;
    const Aws::String secretKey = auth.secret_key;

    config.endpointOverride = address;
    config.scheme = Aws::Http::Scheme::HTTP;
    config.verifySSL = false;

    Aws::S3::S3Client s3_client(Aws::Auth::AWSCredentials(accessKey, secretKey), config,
                                Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Never, false);

    Aws::S3::Model::CreateBucketRequest request;
    request.SetBucket(bucketName);

    Aws::S3::Model::CreateBucketOutcome outcome = s3_client.CreateBucket(request);

    if (!outcome.IsSuccess())
    {
        auto err = outcome.GetError();
        std::cerr << "Error: CreateBucket: " << err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
        return false;
    }

    return true;
}

namespace Minio
{
    Minio::Minio(string address, string access_key, string secret_key, bool secure) : _address(address),
                                                                                      _access_key(access_key),
                                                                                      _secret_key(secret_key),
                                                                                      _secure(secure)
    {
        _options = new Aws::SDKOptions;
        Aws::SDKOptions *options = reinterpret_cast<Aws::SDKOptions *>(_options);
        Aws::InitAPI(*options);

        _config = new Aws::Client::ClientConfiguration;
        Aws::Client::ClientConfiguration *config = reinterpret_cast<Aws::Client::ClientConfiguration *>(_config);
        config->endpointOverride = _address;

        if (_secure)
        {
            config->scheme = Aws::Http::Scheme::HTTPS;
            config->verifySSL = true;
        }
        else
        {
            config->scheme = Aws::Http::Scheme::HTTP;
            config->verifySSL = false;
        }

        _s3_client = new Aws::S3::S3Client(Aws::Auth::AWSCredentials(_access_key, _secret_key), *config,
                                           Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Never, false);
    }

    Minio::~Minio()
    {
        Aws::SDKOptions *options = reinterpret_cast<Aws::SDKOptions *>(_options);
        Aws::ShutdownAPI(*options);

        delete reinterpret_cast<Aws::SDKOptions *>(_options);
        delete reinterpret_cast<Aws::Client::ClientConfiguration *>(_config);
        delete reinterpret_cast<Aws::S3::S3Client *>(_s3_client);
    }

    bool Minio::getObject(string from_bucket, string object_key, string file_path)
    {
        Aws::S3::S3Client *s3_client = reinterpret_cast<Aws::S3::S3Client *>(_s3_client);
        Aws::S3::Model::GetObjectRequest object_request;
        object_request.SetBucket(from_bucket);
        object_request.SetKey(object_key);

        Aws::S3::Model::GetObjectOutcome get_object_outcome = s3_client->GetObject(object_request);

        if (get_object_outcome.IsSuccess())
        {
            Aws::OFStream local_file;
            local_file.open(file_path, std::ios::out | std::ios::binary);
            local_file << get_object_outcome.GetResultWithOwnership().GetBody().rdbuf();
            return true;
        }
        else
        {
            auto err = get_object_outcome.GetError();
            std::cerr << "Error: GetObject: " << err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
            return false;
        }
    }

    bool Minio::putObject(string bucket_name,string file_path, string file_name){
        struct stat buffer;


        if(stat(file_path.c_str(),&buffer) == -1){
            std::cout<< "Error PutObject: File " << file_name << " does not exist" << "\n";
            return false;
        }
        Aws::S3::S3Client * s3_client = reinterpret_cast<Aws::S3::S3Client *>(_s3_client);
        Aws::S3::Model::PutObjectRequest object_request;
        object_request.SetBucket(bucket_name);
        object_request.SetKey(file_name);

        std::shared_ptr<Aws::IOStream> input_data = Aws::MakeShared<Aws::FStream>("sSampleAllocationtTag",file_path.c_str(),std::ios_base::in|std::ios_base::binary);
        object_request.SetBody(input_data);
        Aws::S3::Model::PutObjectOutcome putObjectOutcome = s3_client->PutObject(object_request);

        if(putObjectOutcome.IsSuccess()){
            std::cout << "Added object " << file_name << " to bucket ";
            return true;
        }
        std::cout << "Error:putObjeact: " << putObjectOutcome.GetError().GetMessage() << "\n" ;
        return false;
    }

} // namespace Minio