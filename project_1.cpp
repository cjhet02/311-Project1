//Christopher Robles, Jack Mattern
#include<iostream>
#include<vector>
#include<fstream>
#include<time.h>
#include<math.h>
#include<chrono>
using namespace std;

//global variables that show if every sort call has been successful
bool BubbleSorted = true;
bool InsertSorted = true;
bool SelectSorted = true;
bool QuickSorted = true;

//provided function for generating a vector of random values
vector<int> randomVector(int size, int low, int high){
    vector<int> v(size, 0);
    for (int i = 0; i < size; i++)
        v[i] = rand() % (high - low + 1) + low;
    return v;
}
//a helper function that determines whether a vector has been sorted
bool isSorted(vector<int> v){
    int size = v.size();
    for(int i = 0; i < size - 1; i++){
        if(v[i] > v[i+1])
                return false;
    }
    return true;
}
//Bubble Sort implementation, returns a sorted vector
vector<int> Bubble(vector<int> v){
    bool sorted = false;
    while(!sorted){
        sorted = true;
        for(int i = 1; i < v.size(); i++){
            if(v[i-1] > v[i]){
                swap(v[i], v[i-1]);
                sorted = false;
            }
        }
    }
    return v;
}   
//Insertion Sort implementation, returns a sorted vector
vector<int> Insert(vector<int> v){
    int j, e;
    for(int i = 1; i < v.size(); i++){
        j = i - 1;
        e = v[i];
        while(j >= 0 && v[j] > e){
            v[j+1] = v[j];
            j--;
        }//while
        v[j+1] = e;
    }//for
    return v;
}
//Selection Sort implementation, returns a sorted vector
vector<int> Selection(vector<int> v){
    for(int i = 0; i < v.size()-1; i++){
        int uMin = i;
        for(int j = i+1; j < v.size(); j++){
            if(v[j] < v[uMin])
                    uMin = j;
        }
        swap(v[i], v[uMin]);
    }
    return v;
}
//Quicksort implementation, returns a sorted vector
vector<int> Quick(vector<int> &v){
    if(v.size() <= 1)
            return v;
    int pivot = v[0];
    vector<int> A;
    vector<int> B;
    for(int i = 1; i < (int)v.size(); i++){
        if(v[i] <= pivot)
                A.push_back(v[i]);
        else
                B.push_back(v[i]);
    }
    A = Quick(A);
    B = Quick(B);
    A.push_back(pivot);
    for (int i = 0; i < (int)B.size(); i++){
        A.push_back(B[i]);
    }

    return A;
}
//a helper function that calls sorting algorithms, times them, and checks if they were successful.
void callSorts(vector<int> v, vector<vector<double>> &timesVec){
    chrono::high_resolution_clock::time_point start; //time measurment variables
    chrono::high_resolution_clock::time_point end;

    start = chrono::high_resolution_clock::now(); //measures algorithm time
    vector<int> bubbleV = Bubble(v);
    end = chrono::high_resolution_clock::now();

    //adds elapsed time to a 2d vector for later calculations
    timesVec[0].push_back(chrono::duration_cast<chrono::duration<double>>(end - start).count()); 
    cout << " |bubble done|";
    if(!isSorted(bubbleV)) //check if vector is sorted, if not, change the global variable.
            BubbleSorted = false;

    start = chrono::high_resolution_clock::now(); //repeat for insert
    vector<int> insertV = Insert(v);
    end = chrono::high_resolution_clock::now();
    timesVec[1].push_back(chrono::duration_cast<chrono::duration<double>>(end - start).count());
    cout << " |insert done|";
    if(!isSorted(insertV))
        InsertSorted = false;
 

    start = chrono::high_resolution_clock::now(); //repeat for selection
    vector<int> selectV = Selection(v);
    end = chrono::high_resolution_clock::now();
    timesVec[2].push_back(chrono::duration_cast<chrono::duration<double>>(end - start).count());
    cout << " |selection done|";
    if(!isSorted(selectV))
        SelectSorted = false;

    start = chrono::high_resolution_clock::now(); //repeat for quicksort
    vector<int> quickV = Quick(v);
    end = chrono::high_resolution_clock::now();
    timesVec[3].push_back(chrono::duration_cast<chrono::duration<double>>(end - start).count());
    cout << " |quick done|";
    if(!isSorted(quickV))
        QuickSorted = false;
    cout << endl;
}
//this helper function calculates min, max, mean, and standard deviation of a list of times.
void timeCalc(vector<double> v){ //v is one of 4 inner vectors of measured times from my 2d vector
    double vMin = 101;
    double vMax = 0;
    double mean = 0;
    double sd = 0;

    for (int i =  0; i < (int)v.size(); i++){
        mean += v[i];
        if(v[i] < vMin)
                vMin = v[i];
        if(v[i] > vMax)
                vMax = v[i];
    }
    mean = mean / (int)v.size();
    for (int i = 0; i < (int)v.size(); i++)
            sd += (v[i]-mean)*(v[i]-mean);
    sd = sqrt(sd / ((int)v.size()-1));

    cout << "Minimum: " << vMin << "\nMaximum: " << vMax << endl;
    cout << "Mean: " << mean << "\nStandard Deviation: " << sd << endl;
}

int main(){
    srand(time(NULL));
    
    vector<vector<double>> timesVec(4); //this 2d vector holds 4 sub-vectors(one for each algorithm)
					//each sub-vector will hold the elapsed times of every called sort.
					//if I sort 10 vectors, each sub-vector will have 10 different times.

    for(int i = 1; i <= 10; i++){ //this for loop can be modified to change the amount of vectors that will be sorted
        vector<int> v = randomVector(100, 0, 99); //changing the values in this function call can change the length of the vectors.
        cout << "\nVector " << i << ": ";
        callSorts(v, timesVec); //this will send the current vector to the time measurment helper function.
    }

    //each block of code handles the output and timeCalc calls for each individual algorithm
    string divider = "-----------------------------------------------";
    //output for bubble sort 
    cout << divider << "\nBubble sort on 10 vectors: ";
    if(BubbleSorted)
            cout << "Successful" << endl;
    else
            cout << "Unsuccessful" << endl;
    timeCalc(timesVec[0]); //these function calls pass the algorithm's respective sub-vector of times into the calculation function
    
    //output for insertion sort
    cout << divider << "\nInsertion sort on 10 vectors: ";
    if(InsertSorted)
            cout << "Successful" << endl;
    else
            cout << "Unsuccessful" << endl;
    timeCalc(timesVec[1]);

    //output for selection sort
    cout << divider << "\nSelection sort on 10 vectors: ";
    if(SelectSorted)
            cout << "Successful" << endl;
    else
            cout << "Unsuccessful" << endl;
    timeCalc(timesVec[2]);
    
    //output for quicksort
    cout << divider << "\nQuicksort on 10 vectors: ";
    if(QuickSorted)
            cout << "Successful" << endl;
    else
            cout << "Unsuccessful" << endl;
    timeCalc(timesVec[3]);


    return 0;
}
