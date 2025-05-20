#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <fstream>

using namespace std;

void createOrderedDataFile(int len){
    string path = "../dados/raw_"+to_string(len); 

    fstream file;
    file.open(path, ios::binary | ios::out);
    if(!file) return;

    for (float i = 0; i < len; i++)
    {
        file.write(reinterpret_cast<char*>(&i), sizeof(float));
    }
    file.close();
}

void createRandomDataFile(int len){
    string path = "../dados/raw_"+to_string(len); 

    fstream file;
    file.open(path, ios::binary | ios::out);
    if(!file) return;

    for (int i = 0; i < len; i++)
    {
        float random = rand() % 1000;
        file.write(reinterpret_cast<char*>(&random), sizeof(float));
    }
    file.close();
}

int main(){
    createRandomDataFile(100);

    return 0;
}