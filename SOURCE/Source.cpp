#include <iostream>
#include <time.h>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>

#include "DataGenerator.h"

const int N_BUCKET = 1000;

using namespace std;
//->Support Func
void swap(int &a,int &b){
    int c = a;
    
    a = b;
    b = c;
}

void printArray(int *a,int n){
    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << endl;
}

void outputConsole(int size[],double result[][3]){
    cout << "\nResult:\n";
    cout << left << setw(15) << " "          <<right << setw(15) << size[0]      << setw(15) << size[1]      << setw(15) << size[2]      << endl;
    cout << left << setw(15) << "Bucket Sort"<<right << setw(15) << result[0][0] << setw(15) << result[1][0] << setw(15) << result[2][0] << endl;
    cout << left << setw(15) << "Intro Sort" <<right << setw(15) << result[0][1] << setw(15) << result[1][1] << setw(15) << result[2][1] << endl;
    cout << left << setw(15) << "Quick Sort" <<right << setw(15) << result[0][2] << setw(15) << result[1][2] << setw(15) << result[2][2] << endl;
}
//->Support Func

//->Bucket Sort
struct Node
{
    int data;
    Node* next;
};

Node* makeNode(int data)
{
    Node* p = new Node;
    p->data = data;
    p->next = NULL;
    return p;
}

void addNodeAndSorting(Node*& head, int value)
{
    Node* p = makeNode(value);
    if(p == NULL ){
        cout << "Ko du bo nho" << endl;
        return; 
    }
    if (head == NULL)
        head = p;
    else
    {
        Node* temp = head;
        if (temp->data > p->data)
        {
            p->next = head;
            head = p;
        }
        else
        {
            while (temp->next != NULL)
            {
                if (temp->next->data > p->data)
                    break;
                temp = temp->next;
            }
            p->next = temp->next;
            temp->next = p;
        }
    }
}

int findMax(int a[], int n){
    int max = a[0];

    for (int i = 1; i < n; i++)
        if (a[i]  > max)
            max = a[i];

    return max;
} 
void bucketSort(int a[], int n){
    int max = findMax(a, n);
    int nBucket = N_BUCKET;
    Node** bucket = new Node *[nBucket];

    for (int i = 0; i < nBucket; i++)
        bucket[i] = NULL;
    
    for (int i = 0; i < n; i++){
        int bi = (nBucket * a[i]) / (max + 1);

        addNodeAndSorting(bucket[bi], a[i]);
    }
    
    //Bring sorted elements in buckets back to array
    int index = 0;
    for (int i = 0; i < nBucket; i++){
        Node* p = bucket[i];
    
        while (p != NULL){
            a[index++] = p->data;
            p = p->next;
        }
    }
    
    //Release memory
    for (int i = 0; i < nBucket; i++){
        Node* p = bucket[i];
        while (p != NULL){
            Node* temp = p;
            p = p->next;
            delete temp;
        }
    }

    delete[] bucket;
}
//->Bucket Sort

//->Insertion Sort
void insertionSort(int arr[],int left,int right){
    for (int i = left; i < right; i++) {
        int x = arr[i];
        int j = i - 1;

        while ( j >= left && x < arr[j] ) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = x;
    }
}
//->Insertion Sort

//->HeapSort
void sift(int arr[],int index, int left, int right) {
    int i = index;
    int j = 2 * i + 1 - left;
    int x = arr[i];

    while (j < right) {
        if ( j < right - 1)
            if (arr[j] < arr[j + 1])
                j++;
        if (x >= arr[j])
            break;
        arr[i] = arr[j];
        i = j;
        j = 2 * i + 1 - left;
    }

    arr[i] = x;
}

void heapSort(int arr[], int left,int right) {
    for(int i = left + ((right - left)/2) - 1; i >= left;i--){
        sift(arr,i,left,right);
    }

    for(int i = right - 1; i >left; i--){
        swap(arr[left],arr[i]);
        sift(arr,left,left,i);
    }
        
}
//->HeapSort


//->QuickSort
int partition(int arr[], int left, int right){
    int pivotValue = arr[right];
    int pivotIndex = left - 1;

    for(int i = left; i < right;i++){
        if(arr[i] <= pivotValue){
            pivotIndex++;
            swap(arr[i], arr[pivotIndex]);
            
        }
    }

    swap(arr[pivotIndex + 1],arr[right]);
    return pivotIndex + 1;
}

int randomPartition(int arr[],int left,int right){
    srand(time(NULL));
    int index = rand() % (right - left + 1) + left;
    swap(arr[index],arr[right]);
    return partition(arr,left,right);
}

void quickSort(int arr[], int left, int right){
    if (left < right){
        int pivot = randomPartition(arr, left, right);

        quickSort(arr, left, pivot - 1);
        quickSort(arr, pivot + 1, right); 
    }
}
//->QuickSort

//->Intro Sort
void sort(int arr[],int left,int right,int depth){
    int size = right - left;

    if (size < 16){
        insertionSort(arr,left,right + 1);
    }
    else{
        if (depth == 0){
            heapSort(arr,left,right + 1);
        }
        else{
            int pivot = partition(arr,left,right);
            sort(arr,left,pivot - 1,depth - 1);
            sort(arr,pivot + 1,right,depth - 1);
        }
    }
}

void introSort(int arr[],int left,int right){
    int depth = 2 * log2(right - left);

    sort(arr,left,right,depth);
}

//->Intro Sort

int main(int argc, char* argv[]) {
    while (true){
        system("cls");
        int choice = -1;
        while(choice < 0 || choice > 3){
            cout << "Chose Data Order:\n";
            cout << "1.Randomized data\n";
            cout << "2.Sorted data\n";
            cout << "3.Reserved sorted Data\n";
            cout << "0.Exit\n";
            cout << "Your choice: ";
        
            cin >> choice;
        }

        if (choice == 0)
            return 0;
        
           
        int size[3] = {10000,100000,1000000};
        double result[3][3];

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                int n = size[i];
                int *arr = new int [n];

                GenerateData(arr,n,choice - 1);

                clock_t start,end;
                start = clock();
                
                switch (j){
                    case 0:
                        //Bucker Sort//
                        bucketSort(arr,n);
                        break;
                    case 1:
                        //IntroSort//
                        introSort(arr,0,n - 1);
                        break;
                    case 2:
                        //Quick Sort//
                        quickSort(arr,0,n - 1);
                        break;
                }

                end =  clock();
                double running_time = (double)(end - start);

                result[i][j] = running_time;
               
                delete[] arr; 
            } 
        } 
        output(size,result);
        system("pause");    
    }
    return 0;
}
