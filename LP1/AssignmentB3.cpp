#include <iostream>
#include<bits/stdc++.h> 
using namespace std;
void firstfit(int blocks[],int m,int process[],int n){
    int allocated[n];
    memset(allocated, -1, sizeof(allocated));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(blocks[j]>=process[i]){
                allocated[i]=j;
                blocks[j]=blocks[j]-process[i];
                break;
            }
            

        }
    }
        cout << "\nProcess No.\tProcess Size\tBlock no.\n"; 
    for (int i = 0; i < n; i++) 
    { 
        cout << " " << i+1 << "\t\t" 
             << process[i] << "\t\t"; 
        if (allocated[i] != -1) 
            cout << allocated[i] + 1; 
        else
            cout << "Not Allocated"; 
        cout << endl; 
    }
    }

void bestfit(int blocks[], int m, int process[], int n) {
    int allocated[n];
    memset(allocated, -1, sizeof(allocated));
    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blocks[j] >= process[i]) {
                if (bestIdx == -1 || blocks[j] < blocks[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocated[i] = bestIdx;
            blocks[bestIdx] -= process[i];
        }
    }
    cout << "\nBest Fit Allocation:\n";
    cout << "Process No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++) {
        cout << " " << i + 1 << "\t\t" << process[i] << "\t\t";
        if (allocated[i] != -1)
            cout << allocated[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}
void worstfit(int blocks[],int m,int process[],int n){
     int allocated[n];
    memset(allocated, -1, sizeof(allocated));
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blocks[j] >= process[i]) {
                if (worstIdx == -1 || blocks[j] > blocks[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocated[i] = worstIdx;
            blocks[worstIdx] -= process[i];
        }
    }
    cout << "\nWorst Fit Allocation:\n";
    cout << "Process No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++) {
        cout << " " << i + 1 << "\t\t" << process[i] << "\t\t";
        if (allocated[i] != -1)
            cout << allocated[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;

}
}
void nextfit(int blocks[], int m, int process[], int n) {
    int allocated[n];
    memset(allocated, -1, sizeof(allocated));
    int lastAllocated = 0; // to keep track of the last allocated block index
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int index = (lastAllocated + j) % m; // circular indexing
            if (blocks[index] >= process[i]) {
                allocated[i] = index;
                blocks[index] -= process[i];
                lastAllocated = index; // update the last allocated index
                break;
            }
        }
    }
        cout << "\nNext Fit Allocation:\n";
    cout << "Process No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++) {
        cout << " " << i + 1 << "\t\t" << process[i] << "\t\t";
        if (allocated[i] != -1)
            cout << allocated[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;

}
}

 int main(){
    int blockSize[] = {100, 500, 200, 300, 600}; 
    int processSize[] = {212, 417, 112, 426};
    int m = sizeof(blockSize) / sizeof(blockSize[0]); 
    int n = sizeof(processSize) / sizeof(processSize[0]); 
    bestfit(blockSize, m, processSize, n); 
  //  firstfit(blockSize, m, processSize, n); 
   // worstfit(blockSize, m, processSize, n);
    //nextfit(blockSize, m, processSize, n);  
    return 0;
    

 }