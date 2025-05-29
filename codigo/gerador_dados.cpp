#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

void createRandomTeste(){
    string path = "dados/teste.bin"; 

    fstream file;
    file.open(path, ios::binary | ios::out);
    if(!file) return;

    for (int i = 0; i < 100; i++)
    {
        int random = rand() % 100;
        file.write(reinterpret_cast<char*>(&random), sizeof(int));
    }
    file.close();

}

void createOrderedIntDataFile(int len){
    string path = "dados/sorted_"+to_string(len)+".bin"; 

    fstream file;
    file.open(path, ios::binary | ios::out);
    if(!file) return;

    for (int i = 0; i < len; i++)
    {
        file.write(reinterpret_cast<char*>(&i), sizeof(int));
    }
    file.close();
}

void createRandomIntDataFile(int len){
    string nome = "";
    if(len < 100000){
        nome = "pequeno";
    }
    string path = "dados/"+nome+".bin"; 

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
    int len = pow(10, 4)*1.7;
    time_point<system_clock> t1 = high_resolution_clock::now();
    createRandomIntDataFile(len);
    time_point<system_clock> t2 = high_resolution_clock::now();

    duration<double, std::milli> tempo = (t2 - t1)/1000;

    cout<<len<<" números aleatórios criados em "<<tempo.count()<<"s\n";

    // createRandomTeste();



    return 0;
}