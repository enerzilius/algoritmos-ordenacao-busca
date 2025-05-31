#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

void createBinaryFileFromVector(vector<int> sorted){
    string name = "";
    if(sorted.size() < 5000){
        name = "Pequeno";
    }else if(sorted.size() >= 50000 && sorted.size() < 200000){
        name = "Medio";
    }else{
        name = "Grande";
    }

    string path = "dados/result"+name+".bin";

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

vector<int> selectionSort(vector<int> data, unsigned long* comps, unsigned long* switches){
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
vector<int> optimizedSelectionSort(vector<int> data, unsigned long* comps, unsigned long* switches){
    vector<int> sortedData = data;
    int iMin = 0;

    for (int i = 0; i < sortedData.size(); i++)
    {
        iMin = i;
        *comps += 1;
        if(sortedData[i] <= sortedData[i+1]) continue;
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

vector<int> bubbleSort(vector<int> data, unsigned long* comps, unsigned long* switches){
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
vector<int> optimizedBubbleSort(vector<int> data, unsigned long* comps, unsigned long* switches){
    vector<int> sortedData = data;
    bool switched;

    for(int i = 0; i < sortedData.size(); i++){
        switched = false;
        *comps += 1;
        if(sortedData[i] <= sortedData[i+1]) continue;
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

vector<int> insertionSort(vector<int> data, unsigned long* comps, unsigned long* switches){
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

void printSortAnalysis(int sorting, int size, bool bestCase){
    string sizes[] = {"pequeno", "medio", "grande"};
    string algs[] = {"Bubble Sort", "Selection Sort", "Insertion Sort"};

    unsigned long comps = 0;
    unsigned long switches = 0;

    vector<int> data = vectorizeData("dados/"+sizes[size-1]+".bin");
    vector<int> sorted;
    if(bestCase){
        sorted = insertionSort(data,&comps,&switches);
    }

    time_point<system_clock> t1;
    time_point<system_clock> t2;

    switch (sorting)
    {
    case 1:
        if(bestCase){
            t1 = high_resolution_clock::now();
            data = optimizedBubbleSort(sorted,&comps,&switches);
            t2 = high_resolution_clock::now();
        } else {
            t1 = high_resolution_clock::now();
            data = bubbleSort(data,&comps,&switches);
            t2 = high_resolution_clock::now();
        }
        break;
    case 2:
        if(bestCase){
            t1 = high_resolution_clock::now();
            data = optimizedSelectionSort(sorted,&comps,&switches);
            t2 = high_resolution_clock::now();
        } else {
            t1 = high_resolution_clock::now();
            data = selectionSort(data,&comps,&switches);
            t2 = high_resolution_clock::now();
        }
        break;
    case 3:
        if(bestCase){
            t1 = high_resolution_clock::now();
            data = insertionSort(sorted,&comps,&switches);
            t2 = high_resolution_clock::now();
        } else {
            t1 = high_resolution_clock::now();
            data = insertionSort(data,&comps,&switches);
            t2 = high_resolution_clock::now();
        }
        break;
    default:
        break;
    }

    std::chrono::duration<double> tempo = t2 - t1;

    cout<<data.size()<<" números ordenados com "+algs[sorting-1]+" em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";
}

int main(){
    cout<<"---- QUANTIDADE PEQUENA DE DADOS (15.000 números) -----\n";
    cout<<"-- Casos Normais --\n";
    printSortAnalysis(1, 1, false);
    printSortAnalysis(2, 1, false);
    printSortAnalysis(3, 1, false);
    cout<<"-- Melhores casos --\n";
    printSortAnalysis(1, 1, true);
    printSortAnalysis(2, 1, true);
    printSortAnalysis(3, 1, true);
    
    cout<<"---- QUANTIDADE MÉDIA DE DADOS (80.000 números) -----\n";
    cout<<"-- Casos Normais --\n";
    printSortAnalysis(1, 2, false);
    printSortAnalysis(2, 2, false);
    printSortAnalysis(3, 2, false);
    cout<<"-- Melhores casos --\n";
    printSortAnalysis(1, 2, true);
    printSortAnalysis(2, 2, true);
    printSortAnalysis(3, 2, true);
    
    cout<<"---- QUANTIDADE GRANDE DE DADOS (180.000 números) -----\n";
    cout<<"-- Casos Normais --\n";
    printSortAnalysis(1, 3, false);
    printSortAnalysis(2, 3, false);
    printSortAnalysis(3, 3, false);
    cout<<"-- Melhores casos --\n";
    printSortAnalysis(1, 3, true);
    printSortAnalysis(2, 3, true);
    printSortAnalysis(3, 3, true);
    
    return 0;
}