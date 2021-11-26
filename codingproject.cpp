/*
Timothy Seifert
Coding Project.cpp
Purpose: To race both bubblesort and heapsort against 
eachother to determine which is the fastest algorithm
Date: 11/26/21
*/

#include <iostream>
#include <stdio.h>
#include <thread>
#include <vector>
#include <chrono>
#include <ratio>
#include <cstdio>
#include <ctime>

using namespace std;
using namespace std::chrono;

/*
Purpose Heapify is the process of turning the array into a heap
Arguments: int array, n integer, and root integer
Failure condifitions: None
Return: void
*/
void heapify(int arr[], int n, int root)
{
	// make sure to try to catch bad input
	if (arr == NULL){
		cout << "NULL arguments" << endl;
		return;
	}
	// begin by setting the first node 0 as the root
	int largest = root; 
	// get the neighbors of the node
	int left = 2 * root + 1; 
	int right = 2 * root + 2; 

	// determine the largest node
	if (left < n && arr[left] > arr[largest]){
		largest = left;
	}
	if (right < n && arr[right] > arr[largest]){
		largest = right;
	}
	
	// if the original (root) is not the largest, proceed to swap
	if (largest != root) {
		swap(arr[root], arr[largest]);
		heapify(arr, n, largest);
	}
}

/*
Purpose: unit test greater looks at the entire array and 
return swhether it follows the incariant for a sorted
array.
Arguments: an array of ints
*/
bool unitTest_greater(int arr[]){
	int arr_size = sizeof(arr)/sizeof(arr[0]);
	int temp = -1;
	int curr = -1;
	for (int i = 0; i < arr_size; i++){
		temp = curr;
		arr[i] = curr;
		if (temp > curr){
			return false;
		}
	}
	return true;
}

/*
Purpose: Driving function behind heapsort, iterates through
the array in a way wich allows heapify to occur properly.
Arugments: an integer of arrays array, an integer n being the 
size of the array, a clock wich specifies the start of algorthm.
*/
void heapSort(int array[], int n, std::clock_t start)
{
	for (int i = (n / 2 - 1); i >= 0; i--){
		heapify(array, n, i);
	}

	for (int j = (n - 1); j > 0; j--) {
		swap(array[0], array[j]);
		heapify(array, j, 0);
	}
	cout << "		***********TIME ANALYSIS***********\n";
	cout << "		*Heap Sort finished" << endl;
	cout << "		*Ran on " << n << " numbers" << endl;
    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    cout << "		*Total Time in Seconds: "<< duration <<'\n';
	cout << "		***********************************\n";
}

/*
Purpose: Print array prints the values out of an array
Arguments: An array of integers and an int specifiying the array
size
Failure: a null array will be caught
*/
void printArray(int arr[], int array_size)
{
	if(arr == NULL){
		cout << "NULL argument" << endl;
		return;
	}
	for (int i = 0; i < array_size; ++i)
		cout << arr[i] << " ";
	cout << endl;
}

/*
Auxillary swapping function for sorting. Utilizing
pointers we can move variables around with ease.
*/
void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}


 
/*
Purpose: A naive sorting algorithm, wich bubbles up values.
Arugments: an integer of arrays array, an integer n being the 
size of the array, a clock wich specifies the start of algorthm.
Failure: NULL inputs are caught
*/
void bubbleSort(int arr[], int n, std::clock_t start)
{
	if (arr == NULL){
		cout << "NULL arguments" << endl;
		return;
	}

   for (int i = 0; i < n-1; i++)     
       for (int j = 0; j < n-i-1; j++)
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
	cout << "		***********TIME ANALYSIS***********\n";
	cout << "		*Bubble Sort finished" << endl;
	cout << "		*Ran on " << n << " numbers" << endl;
    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    cout << "		*Total Time in Seconds: "<< duration <<'\n';
	cout << "		***********************************\n";
} 

/*
Purpose: For modularity reasons this is a seperate function from main. 
Checks the quality of both sorting algorithms, printing out the sorted arrays
to terminal
Arguments:  a clock specifying the start of the algorithm.
Failure: N/A hard coded input, clocks have built in failure conditions.
*/
void functional_correctness_heapsort_bubblesort(std::clock_t start){
	int arr_small[30];
	for(int i=0;i<30;i++)
		arr_small[i]=rand()%100;
	
	int n_small = sizeof(arr_small) / sizeof(arr_small[0]);
	cout << "Heap Sort Functional Correctness" << endl;
	heapSort(arr_small, n_small, start);
	printArray(arr_small, n_small);
	cout << "Running Unit Test" << endl;
	if(unitTest_greater(arr_small)){
		cout << "passed test\n";
	}else{
		cout << "Test Failure\n";
	}

	for(int i=0;i<30;i++)
		arr_small[i]=rand()%100;

	cout << "Bubble Sort Functional Correctness" << endl;
	bubbleSort(arr_small, n_small, start);
	printArray(arr_small, n_small);
	cout << "Running Unit Test" << endl;
	if(unitTest_greater(arr_small)){
		cout << "passed test\n";
	}else{
		cout << "Test Failure\n";
	}
}

/*
Main: runs the above sorting algorithms, the driving code
behind the functions above.

*/
int main()
{

	cout << "Testing Functionality on Small Array" << endl;
	std::clock_t start;

	start = std::clock();
	functional_correctness_heapsort_bubblesort(start);
	cout <<"********************Running Threads********************\n";
	// we create threads and push them to the back of a vector so
	// we can run them all at once.
	std::vector<std::thread> threads;
	int arr[100000];
	for(int i=0;i<100000;i++)
		arr[i]=rand()%100;
	int n = sizeof(arr) / sizeof(arr[0]);

	threads.push_back(thread(heapSort, arr, n, start));

	int arr_two[100000];
	for(int i=0;i<100000;i++)
		arr_two[i]=rand()%100;
	int n_two = sizeof(arr_two)/sizeof(arr_two[0]);

	threads.push_back(thread(bubbleSort, arr_two, n_two, start));
	int arr_three[1000];
	for(int i=0;i<1000;i++)
		arr_three[i]=rand()%100;
	int n_three = sizeof(arr_three)/sizeof(arr_three[0]);
	threads.push_back(thread(bubbleSort, arr_three, n_three, start));
    for(auto& thread : threads){
        thread.join();
    }

	return 0;
}





