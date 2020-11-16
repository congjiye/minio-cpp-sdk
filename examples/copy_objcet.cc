#include <iostream>

#include "minio.h"

using std::string;
using std::cerr;

int main(int argc, char** argv)
{
    Minio::Minio minio("play.min.io",
                       "Q3AM3UQ867SPQQA43P2F",
                       "zuf+tfteSlswRu7BJ86wekitnifILbZam1KYY3TG");

    try
    {
        minio.CopyObjcet("lib", "word.txt", "test1");
    }
    catch(const Minio::MinioException& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}