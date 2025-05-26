#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

vector<int> vectorizeData(string path){
    vector<int> empty;
    fstream file;
    file.open(path, ios::binary | ios::in);
    if(!file){
        cout<<"Falha ao abrir o arquivo no caminho indicado ["<<path<<"]\n";
        return empty;
    }

    file.seekg(0, ios::end);
    streamsize size = file.tellg();
    file.seekg(0, ios::beg);

    vector<int> data(size / sizeof(int));
        
    if (!file.read(reinterpret_cast<char*>(data.data()), size)) {
        std::cerr << "Erro lendo o arquivo" << std::endl;
        return empty;
    }
    
    file.close();
    return data;
}

void selectionSort(vector<int> data){
    for(float n : data){
        cout<<n<<"\n";
    }
}

int main(){
    vector<int> data = vectorizeData("trabalho_aed1/dados/raw_10");
    time_point<system_clock> t1 = high_resolution_clock::now();
    selectionSort(data);
    time_point<system_clock> t2 = high_resolution_clock::now();

    duration<double, std::milli> tempo = (t2 - t1)/1000;

    cout<<data.size()<<" números ordenados com Selection Sort em "<<tempo.count()<<"s\n";

    return 0;
}