
#include <iostream>
#include <vector>
#include <algorithm>
//#include <stdlib.h>

#include "GLFW/glfw3.h"
#include "ivy_array/inc/ivy.h"
#include "ivy_array/inc/utils.h"



// Merge two subarrays L and M into arr
void merge(ivy &arr, int p, int q, int r) {
  
  // Create L ← A[p..q] and M ← A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;
  
  // Use std::vector to dynamically allocate arrays
  ivy L(n1);
  ivy M(n2);
  
  for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];
    
  for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];
    
  // Maintain current index of sub-arrays and main array
  int i = 0, j = 0, k = p;
  
  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = M[j];
      j++;
    }
    k++;
  }
  
  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }
  
  while (j < n2) {
    arr[k] = M[j];
    j++;
    k++;
  }
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(ivy &arr, int l, int r) {
  if (l < r) {
    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;
    
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    // Merge the sorted subarrays
    merge(arr, l, m, r);
  }
}





void user_thread(){

	std::vector<ivy*> array_of_ivy;
	int N = 15;
	
	for (int i = 0; i < N; i++)
		array_of_ivy.push_back(new ivy(rand()%80+20,50));

	for (int i = 0; i < array_of_ivy.size(); i+=2){
		delete array_of_ivy[i];
		array_of_ivy.erase(array_of_ivy.begin()+i);
	}
	
	for (int i = 0; i < N; i++)
		array_of_ivy.push_back(new ivy(rand()%80+20,-1));
	
	for (int i = 0; i < array_of_ivy.size(); i+=2){
		delete array_of_ivy[i];
		array_of_ivy.erase(array_of_ivy.begin()+i);
	}
	
	for (int i = 0; i < N; i++)
		array_of_ivy.push_back(new ivy(rand()%80+20,99));
	
	
	//for(int i = 0; i<N; i++)
	//	std::sort(array_of_ivy[i]->begin(), array_of_ivy[i]->end());
	pause(2);
	for(auto el:array_of_ivy)
		delete el;
}







