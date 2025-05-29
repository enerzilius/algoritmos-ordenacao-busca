#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

void createBinaryFileFromVector(vector<int> sorted){
    fstream file;
    file.open("dados/resultado.bin", ios::binary | ios::out);
    if(!file) {
        cout<<"Falha na criação de arquivo com os resultados.\n";
        return;
    }

    // file.write(reinterpret_cast<char*>(sorted.size()), sizeof(sorted.size()));
    file.write(reinterpret_cast<char*>(sorted.data()), sorted.size()*sizeof(int));
    file.close();
}

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
            *comps += 1;
            if(sortedData[j] < sortedData[iMin]){
                iMin = j;
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

    for(int i = 0; i < sortedData.size(); i++){
        switched = false;

        for (int j = 0; j < sortedData.size()-i; j++)
        {   
            *comps += 1;
            if(sortedData[j] > sortedData[j+1]){
                swap(sortedData[j], sortedData[j+1]);
                *switches += 1;
                switched = true;
            } 
        }

        if(!switched) break;
    }

    return sortedData;
}

vector<int> insertionSort(vector<int> data, int* comps, int* switches){
    vector<int> sortedData = data;
    int index = 0;
    int j = 0;

    for (int i = 0; i < sortedData.size(); i++){
        index = i;
        int n = sortedData[i];
        j = i-1;
        while(j >= 0 && sortedData[j] > n){
            *comps += 1;
            *switches += 1;
            sortedData[j+1] = sortedData[j];
            index = j;
            j--;
        }
        sortedData[index] = n;
    }
    return sortedData;
}

int main(){
    cout<<"---- QUANTIDADE PEQUENA DE DADOS (10.000 números) -----\n";
    cout<<"-- Casos Normais --\n";
    vector<int> data = vectorizeData("dados/pequeno.bin");
    int comps = 0;
    int switches = 0;
    time_point<system_clock> t1 = high_resolution_clock::now();
    vector<int> selectionSorted = selectionSort(data,&comps,&switches);
    time_point<system_clock> t2 = high_resolution_clock::now();

    std::chrono::duration<double> tempo = t2 - t1;

    
    cout<<selectionSorted.size()<<" números ordenados com Selection Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";
    
    comps = 0;
    switches = 0;

    t1 = high_resolution_clock::now();
    vector<int> bubbleSorted = bubbleSort(data,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;

    
    cout<<bubbleSorted.size()<<" números ordenados com Bubble Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";

    comps = 0;
    switches = 0;

    t1 = high_resolution_clock::now();
    vector<int> insertionSorted = insertionSort(data,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;

    cout<<insertionSorted.size()<<" números ordenados com Insertion Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";

    cout<<"-- Melhores casos --\n";
    createBinaryFileFromVector(insertionSorted);
    vector<int> melhorCaso = vectorizeData("dados/resultado.bin");

    comps = 0;
    switches = 0;
    t1 = high_resolution_clock::now();
    vector<int> selectionSortedBC = selectionSort(melhorCaso,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;

    
    cout<<selectionSortedBC.size()<<" números ordenados com Selection Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";
    
    comps = 0;
    switches = 0;

    t1 = high_resolution_clock::now();
    vector<int> bubbleSortedBC = bubbleSort(melhorCaso,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;

    
    cout<<bubbleSortedBC.size()<<" números ordenados com Bubble Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";

    comps = 0;
    switches = 0;

    t1 = high_resolution_clock::now();
    vector<int> insertionSortedBC = insertionSort(melhorCaso,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;

    cout<<insertionSortedBC.size()<<" números ordenados com Insertion Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";





    return 0;
}