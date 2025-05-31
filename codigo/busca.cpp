#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <chrono>
#include <vector>

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

int linear(vector<int> data, int target, unsigned long *comps){
    for(int i = 0; i < data.size(); i++){
        *comps += 1;
        if(data[i] == target){
            return i;
        }
    }
    return -1;
}

int binary(vector<int> data, int target, unsigned long *comps){
    int high = data.size();
    int low = 1;

    *comps += 1;
    while(low <= high){
        int mid = (int)((low + high) / 2);

        *comps += 1;
        if(data[mid] = target) return mid;
        *comps += 1;
        if(data[mid] < target) high = mid + 1;
        else low = mid - 1;
    }

    return -1;
}

void printSearchAnalysis(int searchType, int size){
    string sizes[] = {"Pequeno", "Medio", "Grande"};
    string types[] = {"Linear Search", "Binary Search"};

    unsigned long comps = 0;

    vector<int> data = vectorizeData("dados/result"+sizes[size-1]+".bin");
    cout<<data.size();
    cout<<"dados/result"+sizes[size-1]+".bin\n";
    int index = 0;

    time_point<system_clock> t1;
    time_point<system_clock> t2;

    int randomValue = rand() % data.size();

    switch(searchType){
        case 1:
            t1 = high_resolution_clock::now();
            index = linear(data, randomValue, &comps);
            t2 = high_resolution_clock::now();
            break;
        case 2:
            t1 = high_resolution_clock::now();
            index = binary(data, randomValue, &comps);
            t2 = high_resolution_clock::now();
            break;
    }
    std::chrono::duration<double> tempo = t2 - t1;

    cout<<types[searchType-1]<<" encontrou o número "<<randomValue<<" em "<<tempo.count()<<"s na posição "<<index<<" com "<<comps<<" comparações\n";
}

int main(){
    cout<<"---- QUANTIDADE PEQUENA DE DADOS (15.000 números) -----\n";
    cout<<"-- Casos Normais --\n";
    printSearchAnalysis(1, 1);
    printSearchAnalysis(2, 1);

    cout<<"---- QUANTIDADE MÉDIA DE DADOS (80.000 números) -----\n";
    cout<<"-- Casos Normais --\n";
    printSearchAnalysis(1, 2);
    printSearchAnalysis(2, 2);
    
    cout<<"---- QUANTIDADE GRANDE DE DADOS (180.000 números) -----\n";
    cout<<"-- Casos Normais --\n";
    printSearchAnalysis(1, 3);
    printSearchAnalysis(2, 3);
    
    return 0;
}