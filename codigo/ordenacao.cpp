#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

void createBinaryFileFromVector(vector<int> sorted){
    string name = "";
    if(sorted.size() < 100000){
        name = "Pequeno";
    }else if(sorted.size() >= 100000 && sorted.size() < 300000){
        name = "Medio";
    }else{
        name = "Grande";
    }

    string path = "codigo/result"+name+"bin";

    fstream file;
    file.open(path, ios::binary | ios::out);
    if(!file) {
        cout<<"Falha na criação de arquivo com os resultados.\n";
        return;
    }

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

vector<int> selectionSort(vector<int> data, long long int* comps, long long int* switches){
    vector<int> sortedData = data;
    int iMin = 0;

    for (int i = 0; i < sortedData.size(); i++)
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

vector<int> bubbleSort(vector<int> data, long long int* comps, long long int* switches){
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

vector<int> insertionSort(vector<int> data, long long int* comps, long long int* switches){
    vector<int> sortedData = data;
    int index = 0;
    int j = 0;

    for (int i = 0; i < sortedData.size(); i++){
        index = i;
        int n = sortedData[i];
        j = i-1;
        *comps += 1;
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
    vector<int> dataP = vectorizeData("dados/pequeno.bin");
    long long int comps = 0;
    long long int switches = 0;
    time_point<system_clock> t1 = high_resolution_clock::now();
    vector<int> selectionSortedP = selectionSort(dataP,&comps,&switches);
    time_point<system_clock> t2 = high_resolution_clock::now();

    std::chrono::duration<double> tempo = t2 - t1;
    
    cout<<selectionSortedP.size()<<" números ordenados com Selection Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";
    
    comps = 0;
    switches = 0;

    t1 = high_resolution_clock::now();
    vector<int> bubbleSortedP = bubbleSort(dataP,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;

    
    cout<<bubbleSortedP.size()<<" números ordenados com Bubble Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";

    comps = 0;
    switches = 0;

    t1 = high_resolution_clock::now();
    vector<int> insertionSortedP = insertionSort(dataP,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;

    createBinaryFileFromVector(insertionSortedP);

    cout<<insertionSortedP.size()<<" números ordenados com Insertion Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";

    cout<<"-- Melhores casos --\n";
    vector<int> melhorCasoP = insertionSortedP;

    comps = 0;
    switches = 0;
    t1 = high_resolution_clock::now();
    vector<int> selectionSortedPBC = selectionSort(melhorCasoP,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;

    
    cout<<selectionSortedPBC.size()<<" números ordenados com Selection Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";
    
    comps = 0;
    switches = 0;

    t1 = high_resolution_clock::now();
    vector<int> bubbleSortedPBC = bubbleSort(melhorCasoP,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;

    
    cout<<bubbleSortedPBC.size()<<" números ordenados com Bubble Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";

    comps = 0;
    switches = 0;

    t1 = high_resolution_clock::now();
    vector<int> insertionSortedPBC = insertionSort(melhorCasoP,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;

    cout<<insertionSortedPBC.size()<<" números ordenados com Insertion Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";

    cout<<"---- QUANTIDADE MÉDIA DE DADOS (100.000 números) -----\n";
    cout<<"-- Casos Normais --\n";
    vector<int> dataM = vectorizeData("dados/medio.bin");
    comps = 0;
    switches = 0;
    t1 = high_resolution_clock::now();
    vector<int> selectionSortedM = selectionSort(dataM,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;
    
    cout<<selectionSortedM.size()<<" números ordenados com Selection Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";
    
    comps = 0;
    switches = 0;

    t1 = high_resolution_clock::now();
    vector<int> bubbleSortedM = bubbleSort(dataM,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;

    
    cout<<bubbleSortedM.size()<<" números ordenados com Bubble Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";

    comps = 0;
    switches = 0;

    t1 = high_resolution_clock::now();
    vector<int> insertionSortedM = insertionSort(dataM,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;

    cout<<insertionSortedM.size()<<" números ordenados com Insertion Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";

    createBinaryFileFromVector(insertionSortedM);

    cout<<"-- Melhores casos --\n";
    vector<int> melhorCasoM = insertionSortedM;

    comps = 0;
    switches = 0;
    t1 = high_resolution_clock::now();
    vector<int> selectionSortedMBC = selectionSort(melhorCasoM,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;

    
    cout<<selectionSortedMBC.size()<<" números ordenados com Selection Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";
    
    comps = 0;
    switches = 0;

    t1 = high_resolution_clock::now();
    vector<int> bubbleSortedMBC = bubbleSort(melhorCasoM,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;

    
    cout<<bubbleSortedMBC.size()<<" números ordenados com Bubble Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";

    comps = 0;
    switches = 0;

    t1 = high_resolution_clock::now();
    vector<int> insertionSortedMBC = insertionSort(melhorCasoM,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;

    cout<<insertionSortedMBC.size()<<" números ordenados com Insertion Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";

    cout<<"---- QUANTIDADE GRANDE DE DADOS (600.000 números) -----\n";
    cout<<"-- Casos Normais --\n";
    vector<int> dataG = vectorizeData("dados/grande.bin");
    comps = 0;
    switches = 0;
    t1 = high_resolution_clock::now();
    vector<int> selectionSortedG = selectionSort(dataG,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;
    
    cout<<selectionSortedG.size()<<" números ordenados com Selection Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";
    
    comps = 0;
    switches = 0;

    t1 = high_resolution_clock::now();
    vector<int> bubbleSortedG = bubbleSort(dataG,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;

    
    cout<<bubbleSortedG.size()<<" números ordenados com Bubble Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";

    comps = 0;
    switches = 0;

    t1 = high_resolution_clock::now();
    vector<int> insertionSortedG = insertionSort(dataG,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;

    cout<<insertionSortedG.size()<<" números ordenados com Insertion Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";

    createBinaryFileFromVector(insertionSortedM);

    cout<<"-- Melhores casos --\n";
    vector<int> melhorCasoG = insertionSortedG;

    comps = 0;
    switches = 0;
    t1 = high_resolution_clock::now();
    vector<int> selectionSortedGBC = selectionSort(melhorCasoG,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;

    
    cout<<selectionSortedGBC.size()<<" números ordenados com Selection Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";
    
    comps = 0;
    switches = 0;

    t1 = high_resolution_clock::now();
    vector<int> bubbleSortedGBC = bubbleSort(melhorCasoG,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;

    
    cout<<bubbleSortedGBC.size()<<" números ordenados com Bubble Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";

    comps = 0;
    switches = 0;

    t1 = high_resolution_clock::now();
    vector<int> insertionSortedGBC = insertionSort(melhorCasoG,&comps,&switches);
    t2 = high_resolution_clock::now();

    tempo = t2 - t1;

    cout<<insertionSortedGBC.size()<<" números ordenados com Insertion Sort em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";

    return 0;
}