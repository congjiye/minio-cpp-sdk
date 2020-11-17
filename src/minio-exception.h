/**
 * @file minio-exception.h
 * @brief minio 异常类
 * @author aydon (congtheking@outlook.com)
 * @version 1.0
 * @date 2020-11-13
 *
 * @copyright Copyright (c) 2020 aydon
 */
#pragma once

#include <stdexcept>
#include <string>

namespace Minio
{
    class MinioException : public std::logic_error
    {
    public:
        explicit MinioException(const std::string &s)
            : logic_error(s) {}
        virtual ~MinioException() {}
    };

    class S3ErrorException : public MinioException
    {
    public:
        explicit S3ErrorException(const std::string &s)
            : MinioException(s) {}
        S3ErrorException(const std::string &name, const std::string &msg)
            : MinioException(name + " : " + msg) {}
        virtual ~S3ErrorException() {}
    };

    class PathException : public std::logic_error
    {
    public:
        explicit PathException(const std::string &s)
            : logic_error(s) {}
        virtual ~PathException() {}
    };
} // namespace Minio