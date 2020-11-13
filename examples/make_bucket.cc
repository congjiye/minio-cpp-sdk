#include <string>
#include <iostream>

#include "minio.h"
#include "minio-exception.h"

int main(int argc, char **argv)
{
    Minio::Minio minio("play.min.io",
                       "Q3AM3UQ867SPQQA43P2F",
                       "zuf+tfteSlswRu7BJ86wekitnifILbZam1KYY3TG");

    try
    {
        minio.MakeBucket("aa");
    }
    catch (const Minio::MinioException &e)
    {
        std::cerr << e.what() << '\n';
    }
}