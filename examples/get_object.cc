#include <iostream>
#include "minio.h"

int main(int argc, char **argv)
{
    Minio::Minio minio("play.min.io",
                       "Q3AM3UQ867SPQQA43P2F",
                       "zuf+tfteSlswRu7BJ86wekitnifILbZam1KYY3TG");

    try
    {
        minio.GetObject("lib", "word.txt", "word.txt");
    }
    catch (const Minio::MinioException &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}