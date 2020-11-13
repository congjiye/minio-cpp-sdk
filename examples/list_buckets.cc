#include <iostream>

#include "minio.h"

using std::string;
using std::vector;

int main(int argc, char **argv)
{
    Minio::Minio minio("play.min.io",
                       "Q3AM3UQ867SPQQA43P2F",
                       "zuf+tfteSlswRu7BJ86wekitnifILbZam1KYY3TG");

    vector<string> buckets;
    minio.ListBuckets(buckets);
    for (auto &bucket : buckets)
    {
        std::cout << "Bucket Name: " << bucket << "\n";
    }
    return 0;
}