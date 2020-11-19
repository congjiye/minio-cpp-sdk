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
        vector<string> objects;
        minio.ListObjects("testupload", objects);
        for (auto &object : objects)
        {
            std::cout << "Object Name: " << object << "\n";
        }
    }
    catch (const Minio::MinioException &e)
    {
        std::cerr << e.what() << '\n';
    }
}