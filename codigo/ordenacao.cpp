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

vector<int> selectionSort(vector<int> data, int* comps, int* switches){
    vector<int> sortedData = data;
    int iMin = 0;
    int i = 0;
    int aux = 0;

    for (int i = i; i < sortedData.size(); i++)
    {
        iMin = i;
        for (int j = i; j < sortedData.size(); j++)
        {
            if(sortedData[j] < sortedData[iMin]){
                iMin = j;
                *comps += 1;
            } 
        }
        swap(sortedData[i], sortedData[iMin]);
        *switches += 1;
    }

    return sortedData;
}

vector<int> bubbleSort(vector<int> data, int* comps, int* switches){
    vector<int> sortedData = data;
    bool switched;

    for(int i = 0; i < data.size()-1; i++){
        switched = false;

        for (int j = i; j < sortedData.size()-i-1; j++)
        {   
            if(sortedData[j] > sortedData[j+1]){
                switch(data[j], data[j+1]);
                *comps += 1;
                *switches += 1;
                switched = true;
            } 
        }

        if(!switched) break;
    }

    return sortedData;
}

int main(){
    cout<<"---- QUANTIDADE PEQUENA DE DADOS (10.000 números) -----\n";
    vector<int> data = vectorizeData("dados/pequeno.bin");
    int comps = 0;
    int switches = 0;
    time_point<system_clock> t1 = high_resolution_clock::now();
    vector<int> selectionSorted = selectionSort(data,&comps,&switches);
    time_point<system_clock> t2 = high_resolution_clock::now();

    std::chrono::duration<double> tempo = (t2 - t1);

    cout<<selectionSorted.size()<<" números ordenados com Selection Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";
    
    t1 = high_resolution_clock::now();
    vector<int> bubbleSorted = bubbleSort(data,&comps,&switches);
    t2 = high_resolution_clock::now();

    std::chrono::duration<double> tempo = (t2 - t1);
    
    cout<<bubbleSorted.size()<<" números ordenados com Bubble Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";


    comps = 0;
    switches = 0;

    return 0;
}