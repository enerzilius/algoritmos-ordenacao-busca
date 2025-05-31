#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

int linear(vector<int> data, int target, unsigned long *comps){
    for(int i = 0; i < data.size(); i++){
        if(data[i] == target){
            return i;
        }
    }
    return -1;
}

int binary(vector<int> data, int target, unsigned long *comps){
    int more = data.size();
    int less = 1;

    while(less <= more){
        int mid = (int)((less + more) / 2);

        if(data[mid] = target) return mid;

        if(data[mid] < target) more = mid + 1;
        else less = mid - 1;
    }

    return -1;
}

void analyzeSearch(){
    
}

int main(){
    unsigned long comps = 0;

    



    return 0;
}