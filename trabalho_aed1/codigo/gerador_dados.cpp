#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

void createOrderedDataFile(int len){
    string path = "../dados/raw_ordered"+to_string(len); 

    fstream file;
    file.open(path, ios::binary | ios::out);
    if(!file) return;

    for (int i = 0; i < len; i++)
    {
        file.write(reinterpret_cast<char*>(&i), sizeof(int));
    }
    file.close();
}

void createRandomDataFile(int len){
    string path = "trabalho_aed1/dados/raw_"+to_string(len); 

    fstream file;
    file.open(path, ios::binary | ios::out);
    if(!file) return;

    for (int i = 0; i < len; i++)
    {
        int random = rand() % len;
        file.write(reinterpret_cast<char*>(&random), sizeof(int));
    }
    file.close();
}

int main(){
    int len = pow(10, 3);
    time_point<system_clock> t1 = high_resolution_clock::now();
    createRandomDataFile(len);
    time_point<system_clock> t2 = high_resolution_clock::now();

    duration<double, std::milli> tempo = (t2 - t1)/1000;

    cout<<len<<" números aleatórios criados em "<<tempo.count()<<"s\n";



    return 0;
}