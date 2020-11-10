//
// Created by zjp on 2020/11/10.
//
#include <iostream>
#include "minio.h"

int main(){
    Minio::Minio minio("192.168.1.70:9001","thunisoft","6789@jkl");
    minio.putObject("voice-label/test_minio", "/home/zjp/workspace/cPlusPlus/minio-cpp-2/minio-cpp/minio.cpp","minio.cpp");


    std::cout<< "sdf" << std::endl;
}
