#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

void createBinaryFileFromVector(vector<int> sorted){
    string name = "";
    if(sorted.size() < 50000){
        name = "Pequeno";
    }else if(sorted.size() >= 50000 && sorted.size() < 150000){
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

void printAnalysis(vector<int> data, std::chrono::duration<double> tempo, unsigned long comps, unsigned long switches, int sorting, bool otimizado){
    string obs = otimizado?" (otimizado para o melhor caso)":"";
    string algs[] = {"Bubble Sort", "Selection Sort", "Insert Sort"};
    cout<<data.size()<<" números ordenados com "<<algs[sorting-1]<<obs<<" em "<<tempo.count()<<"s com "<<comps<<" comparações e "<<switches<<" trocas\n";
}

vector<int> createSortAnalysis(int sorting, int size, bool otimizado, vector<int> data){
    unsigned long comps = 0;
    unsigned long switches = 0;

    time_point<system_clock> t1;
    time_point<system_clock> t2;

    switch (sorting)
    {
    case 1:
        t1 = high_resolution_clock::now();
        if(otimizado) data = optimizedBubbleSort(data,&comps,&switches);
        else data = bubbleSort(data,&comps,&switches);
        t2 = high_resolution_clock::now();
        break;
    case 2:
        t1 = high_resolution_clock::now();
        if(otimizado) data = optimizedSelectionSort(data,&comps,&switches);
        else data = selectionSort(data,&comps,&switches);
        t2 = high_resolution_clock::now();
        break;
    case 3:
        t1 = high_resolution_clock::now();
        data = insertionSort(data,&comps,&switches);
        t2 = high_resolution_clock::now(); 
        break;
    default:
        break;
    }

    std::chrono::duration<double> tempo = t2 - t1;
    printAnalysis(data, tempo, comps, switches, sorting, otimizado);
    return data;
}




int main(){
    cout<<"---- QUANTIDADE PEQUENA DE DADOS (14.000 números) -----\n";
    cout<<"-- Casos Normais --\n";
    vector<int> data = vectorizeData("dados/pequeno.bin");
    vector<int> sorted;
    sorted = createSortAnalysis(1, 1, false, data);
    sorted = createSortAnalysis(1, 1, true, data);
    sorted = createSortAnalysis(2, 1, false, data);
    sorted = createSortAnalysis(2, 1, true, data);
    sorted = createSortAnalysis(3, 1, false, data);
    createBinaryFileFromVector(sorted);
    cout<<"-- Melhores casos --\n";
    sorted = createSortAnalysis(1, 1, false, sorted);
    sorted = createSortAnalysis(1, 1, true, sorted);
    sorted = createSortAnalysis(2, 1, false, sorted);
    sorted = createSortAnalysis(2, 1, true, sorted);
    sorted = createSortAnalysis(3, 1, false, sorted);
    
    cout<<"---- QUANTIDADE MÉDIA DE DADOS (80.000 números) -----\n";
    cout<<"-- Casos Normais --\n";
    data = vectorizeData("dados/medio.bin");
    sorted = createSortAnalysis(1, 2, false,  data);
    sorted = createSortAnalysis(1, 2, true,  data);
    sorted = createSortAnalysis(2, 2, false,  data);
    sorted = createSortAnalysis(2, 2, true,  data);
    sorted = createSortAnalysis(3, 2, false,  data);
    createBinaryFileFromVector(sorted);
    cout<<"-- Melhores casos --\n";
    sorted = createSortAnalysis(1, 2, false, sorted);
    sorted = createSortAnalysis(1, 2, true, sorted);
    sorted = createSortAnalysis(2, 2, false, sorted);
    sorted = createSortAnalysis(2, 2, true, sorted);
    sorted = createSortAnalysis(3, 2, false, sorted);
    
    cout<<"---- QUANTIDADE GRANDE DE DADOS (180.000 números) -----\n";
    data = vectorizeData("dados/grande.bin");
    cout<<"-- Casos Normais --\n";
    sorted = createSortAnalysis(1, 3, false, data);
    sorted = createSortAnalysis(1, 3, true, data);
    sorted = createSortAnalysis(2, 3, false, data);
    sorted = createSortAnalysis(2, 3, true, data);
    sorted = createSortAnalysis(3, 3, false, data);
    createBinaryFileFromVector(sorted);
    cout<<"-- Melhores casos --\n";
    sorted = createSortAnalysis(1, 3, false, sorted);
    sorted = createSortAnalysis(1, 3, true, sorted);
    sorted = createSortAnalysis(2, 3, false, sorted);
    sorted = createSortAnalysis(2, 3, true, sorted);
    sorted = createSortAnalysis(3, 3, false, sorted);
    
    return 0;
}