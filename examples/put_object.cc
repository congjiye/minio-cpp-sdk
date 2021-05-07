#include <iostream>
#include <vector>
#include "minio.h"

using namespace std;
int main(int argc, char **argv)
{
    Minio::Minio minio("play.min.io",
                       "Q3AM3UQ867SPQQA43P2F",
                       "zuf+tfteSlswRu7BJ86wekitnifILbZam1KYY3TG");

    try
    {
        minio.PutObject("testupload", "Makefilew", "Makefile");
    }
    catch(const Minio::MinioException& e)
    {
        std::cerr << e.what() << "\n";
    }
}