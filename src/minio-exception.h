/**
 * @file minio-exception.h
 * @brief minio 异常类
 * @author aydon (congtheking@outlook.com)
 * @version 1.0
 * @date 2020-11-13
 *
 * @copyright Copyright (c) 2020 aydon
 */
#ifndef MINIO_CPP_SDK_MINIO_EXCEPTION_H_
#define MINIO_CPP_SDK_MINIO_EXCEPTION_H_

#include <stdexcept>
#include <string>

namespace Minio {
class MinioException : public std::runtime_error {
public:
    explicit MinioException(const std::string &s) : runtime_error(s) {}
    virtual ~MinioException() {}
};

class InvalidEndpointException : public MinioException {
public:
    explicit InvalidEndpointException(const std::string &s) : MinioException(s) {}
    virtual ~InvalidEndpointException() {}
};

class InvalidAccessKeyException : public MinioException {
public:
    explicit InvalidAccessKeyException(const std::string &s) : MinioException(s) {}
    virtual ~InvalidAccessKeyException() {}
};

class InvalidSecretKeyException : public MinioException {
public:
    explicit InvalidSecretKeyException(const std::string &s) : MinioException(s) {}
    virtual ~InvalidSecretKeyException() {}
};

class InvalidBucketNameException : public MinioException {
public:
    explicit InvalidBucketNameException(const std::string &s) : MinioException(s) {}
    InvalidBucketNameException(const std::string &bucket_name, const std::string &msg)
        : MinioException(bucket_name + ": " + msg) {}
    virtual ~InvalidBucketNameException() {}
};

class InvalidObjectNameException : public MinioException {
public:
    explicit InvalidObjectNameException(const std::string &s) : MinioException(s) {}
    virtual ~InvalidObjectNameException() {}
};

class S3ErrorException : public MinioException {
public:
    explicit S3ErrorException(const std::string &s) : MinioException(s) {}
    S3ErrorException(const std::string &name, const std::string &msg) : MinioException(name + " : " + msg) {}
    virtual ~S3ErrorException() {}
};

class InvalidPathException : public MinioException {
public:
    explicit InvalidPathException(const std::string &s) : MinioException(s) {}
    virtual ~InvalidPathException() {}
};

class TimeoutException : public MinioException {
public:
    TimeoutException() : MinioException("Timeout was reached") {}
    virtual ~TimeoutException() {}
};
}  // namespace Minio

#endif  // MINIO_CPP_SDK_MINIO_EXCEPTION_H_