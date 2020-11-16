#include <string>
#include <iostream>

#include "minio.h"

using std::cerr;
using std::string;

int main(int argc, char **argv)
{
    Minio::Minio minio("play.min.io",
                       "Q3AM3UQ867SPQQA43P2F",
                       "zuf+tfteSlswRu7BJ86wekitnifILbZam1KYY3TG");

    try
    {
        minio.BucketExists("test5");
    }
    catch (const Minio::MinioException &e)
    {
        cerr << e.what() << "\n";
    }
    return 0;
}