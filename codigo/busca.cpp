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
    int high = data.size()-1;
    int low = 1;

    *comps += 1;
    while(low <= high){
        int mid = (low+(high - low)/ 2);

        *comps += 1;
        if(data[mid] == target) return mid;
        *comps += 1;
        if(data[mid] < target) low = mid + 1;
        else high = mid - 1;
    }

    return -1;
}

void printSearchAnalysis(vector<int> data, int searchType, int size, int randomValue){
    string sizes[] = {"Pequeno", "Medio", "Grande"};
    string types[] = {"Linear Search", "Binary Search"};

    unsigned long comps = 0;

    int index = 0;

    time_point<system_clock> t1;
    time_point<system_clock> t2;

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
    cout<<"---- QUANTIDADE PEQUENA DE DADOS (14.000 números) -----\n";
    vector<int> data = vectorizeData("dados/resultPequeno.bin");
    int randomValue = rand() % data.size();
    printSearchAnalysis(data, 1, 1, randomValue);
    printSearchAnalysis(data, 2, 1, randomValue);
    cout<<endl;
    randomValue = rand() % data.size();
    printSearchAnalysis(data, 1, 1, randomValue);
    printSearchAnalysis(data, 2, 1, randomValue);
    cout<<endl;
    randomValue = rand() % data.size();
    printSearchAnalysis(data, 1, 1, randomValue);
    printSearchAnalysis(data, 2, 1, randomValue);

    cout<<"\n---- QUANTIDADE MÉDIA DE DADOS (80.000 números) -----\n";
    data = vectorizeData("dados/resultMedio.bin");
    randomValue = rand() % data.size();
    printSearchAnalysis(data, 1, 2, randomValue);
    printSearchAnalysis(data, 2, 2, randomValue);
    cout<<endl;
    randomValue = rand() % data.size();
    printSearchAnalysis(data, 1, 2, randomValue);
    printSearchAnalysis(data, 2, 2, randomValue);
    cout<<endl;
    randomValue = rand() % data.size();
    printSearchAnalysis(data, 1, 2, randomValue);
    printSearchAnalysis(data, 2, 2, randomValue);
    
    cout<<"\n---- QUANTIDADE GRANDE DE DADOS (180.000 números) -----\n";
    data = vectorizeData("dados/resultGrande.bin");
    randomValue = rand() % data.size();
    printSearchAnalysis(data, 1, 3, randomValue);
    printSearchAnalysis(data, 2, 3, randomValue);
    cout<<endl;
    data = vectorizeData("dados/resultGrande.bin");
    randomValue = rand() % data.size();
    printSearchAnalysis(data, 1, 3, randomValue);
    printSearchAnalysis(data, 2, 3, randomValue);
    cout<<endl;
    data = vectorizeData("dados/resultGrande.bin");
    randomValue = rand() % data.size();
    printSearchAnalysis(data, 1, 3, randomValue);
    printSearchAnalysis(data, 2, 3, randomValue);
    
    return 0;
}