
#include <iostream>
#include <vector>
//#include <stdlib.h>

#include "GLFW/glfw3.h"
#include "slow_array.h"
#include "utils.h"




void slow_sort(slow_array& arr){
	for (int i = 0; i < arr.size()-1; i++){
		int max = -1;
		int max_ind = -1;
		for (int j = i; j < arr.size(); j++){
			if (arr[j] > max){
				max = arr[j];
				max_ind = j;
			}
		}
		int tmp = arr[i];
		arr[i] = arr[max_ind];
		arr[max_ind] = tmp;
	}
}


// Merge two subarrays L and M into arr
void merge(slow_array &arr, int p, int q, int r) {
  
  // Create L ← A[p..q] and M ← A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;
  
  // Use std::vector to dynamically allocate arrays
  slow_array L(n1);
  slow_array M(n2);
  
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
void mergeSort(slow_array &arr, int l, int r) {
  if (l < r) {
    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;
    
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    // Merge the sorted subarrays
    merge(arr, l, m, r);
  }
}


slow_array foo(slow_array arr){
	slow_array tmp(arr.size());
	for (int i = 0; i < arr.size(); i++){
		tmp[i] = arr[i];
	}
	return tmp;
}


void user_thread(){
	
	/*
	slow_array arr(50);
	arr.make_rand();
	
	double time_1 = glfwGetTime();
	#ifdef ssort
	slow_sort(arr);
	#endif
	
	#ifdef msort
	mergeSort(arr, 0, arr.size()-1);
	#endif
	
	double time_2 = glfwGetTime();
	std::cout << time_2 - time_1 << " s \n";
	pause(2);
	
	*/
	
	//slow_array arr1(100,0);
	//slow_array arr2 = foo(arr1);
	
	//for(int i = 0; i<arr2.size(); i++){
	//	std::cout << arr2[i] << '\n';
	//}
	
	slow_array arr1(50,0);
	slow_array arr2(50,0);
	slow_array arr3(50,0);
	slow_array arr4(50,0);
	slow_array arr5(50,0);
	slow_array arr6(50,0);
	slow_array arr7(50,0);
	slow_array arr8(50,0);
	slow_array arr9(50,0);
	slow_array arr10(50,0);
	slow_array arr11(50,0);
	slow_array arr12(50,0);
	slow_array arr13(50,0);
	slow_array arr14(50,0);
	slow_array arr15(50,0);
	slow_array arr16(50,0);
	slow_array arr17(50,0);
	slow_array arr18(50,0);
	slow_array arr19(50,0);
	slow_array arr20(50,0);
	
}







