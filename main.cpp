/*
Declare your functions here and put code for functions' definitions below main() function
*/
//function that creates a random vector called rVec of size "asize"
#include<iostream>
#include<vector>
#include<string>
using namespace std;

void randomVector(vector<int> &rVec, int asize){
	rVec.resize(asize, 0);
	for(int i = 0; i < asize; i++){
		rVec[i] = rand() % (1000000);
	}
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


int main(){
	srand(time(0));
	int TOTAL = 5;
	int sizesOfVectors[TOTAL] = {1000, 10000, 50000, 100000, 200000};
	for(int i = 0; i < TOTAL; i++){
		int curSize = sizesOfVectors[i];
		vector<int> origVector;
		randomVector(origVector, curSize);
		//origVector contains random integers
		//for each algorithm, make a separate copy of the original vector
		
		//bubble sort
		vector<int> bubbleVec = origVector;
		//run bubble sort and measure time of bubble sort:
		clock_t t1 = clock();
		//call bubble sort in the line below:
		Bubble(bubbleVec);
		clock_t t2 = clock();
		double elapsed = double(t2 - t1)/CLOCKS_PER_SEC;
		cout << "Bubble sort (size and run time in sec): " << curSize << " " << elapsed << endl;


		//insertion sort
		vector<int> insertionVec = origVector;
		//run insertion sort and measure the run time:
		t1 = clock();
		//call insertion sort in the line below:
		Insert(insertionVec);
//insertionVec vector
		t2 = clock();
		elapsed = double(t2 - t1)/CLOCKS_PER_SEC;
		cout << "Insertion sort (size and run time in sec): " << curSize << " " << elapsed << endl;


		//selection sort
		vector<int> selectionVec = origVector;
		//run selection sort and measure the run time:
		t1 = clock();
		//call selection sort in the line below:
		Selection(selectionVec);
// selectionVec vector
		t2 = clock();
		elapsed = double(t2 - t1)/CLOCKS_PER_SEC;
		cout << "Selection sort (size and run time in sec): " << curSize << " " << elapsed << endl;


		//quickSort sort
		vector<int> quickSortVec = origVector;
		//run quickSort sort and measure the run time:
		t1 = clock();
		//call quickSort sort in the line below:
		Quick(quickSortVec);
//quickSortVec vector
		t2 = clock();
		elapsed = double(t2 - t1)/CLOCKS_PER_SEC;
		cout << "QuickSort sort (size and run time in sec): " << curSize << " " << elapsed << endl;
	}//for loop
    return 0;
}
