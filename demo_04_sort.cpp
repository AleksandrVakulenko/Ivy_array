#include "ivy_array/inc/ivy.h"
#include "ivy_array/inc/utils.h"

#include <iostream>
#include <vector>
#include <algorithm>


void slow_sort(ivy& arr){
	for (int i = 0; i < arr.size()-1; i++){
		int min = 100;
		int min_ind = -1;
		for (int j = i; j < arr.size(); j++){
			if (arr[j] < min){
				min = arr[j];
				min_ind = j;
			}
		}
		int tmp = arr[i];
		arr[i] = arr[min_ind];
		arr[min_ind] = tmp;
	}
}

void slow_sort2(ivy& arr){
	bool is_sorted = false;
	int k = arr.size();
	while(!is_sorted){
		is_sorted = true;
		k--;
		for (int i = 0; i < k; i++){
			if(arr[i] > arr[i+1]) {
				std::swap(arr[i], arr[i+1]);
				is_sorted = false;
			}
		}
	}
}

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

void heapify(ivy& arr, int n, int i) {
    int largest = i;      // Инициализируем корень как наибольший элемент
    int left = 2 * i + 1; // Левый потомок
    int right = 2 * i + 2; // Правый потомок

    // Если левый потомок больше корня
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Если правый потомок больше текущего наибольшего
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // Если наибольший элемент не корень, меняем их местами и рекурсивно восстанавливаем кучу
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(ivy& arr) {
    int n = arr.size();

    // Построение max-кучи (heap)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Один за другим извлекаем элементы из кучи
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]); // Перемещаем текущий корень в конец массива
        heapify(arr, i, 0); // Восстанавливаем кучу на уменьшенном массиве
    }
}

void combSort(ivy& arr) {
    int n = arr.size();
    int gap = n; // Начальный разрыв (gap)
    const double shrinkFactor = 1.3; // Коэффициент уменьшения разрыва
    bool swapped = true; // Флаг, чтобы выполнять проверку на перестановку

    while (gap > 1 || swapped) {
        // Уменьшаем разрыв
        gap = std::max(1, static_cast<int>(gap / shrinkFactor));
        swapped = false;

        // Проходим по массиву и меняем местами элементы, если нужно
        for (int i = 0; i + gap < n; ++i) {
            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}


void TEST_SORT(int N){
	double time_1, time_2;
	
	std::cout << "\n    TEST SORT FOR N = " << N << ": " << '\n';
	
	{
	ivy arr(N, -1);
	std::cout << "slow_sort: ";
	time_1 = glfwGetTime();
		slow_sort2(arr);
	time_2 = glfwGetTime();
	std::cout << time_2 - time_1 << " s \n";
	}
	
	
	
	{
	pause(1);
	ivy arr(N, -1);
	std::cout << "combSort: ";
	time_1 = glfwGetTime();
		combSort(arr);
	time_2 = glfwGetTime();
	std::cout << time_2 - time_1 << " s \n";
	}
	
	
	
	{
	pause(1);
	ivy arr(N, -1);
	std::cout << "heapSort: ";
	time_1 = glfwGetTime();
		heapSort(arr);
	time_2 = glfwGetTime();
	std::cout << time_2 - time_1 << " s \n";
	}
	
	
	
	{
	pause(1);
	ivy arr(N, -1);
	std::cout << "Merge sort: ";
	time_1 = glfwGetTime();
		mergeSort(arr, 0, arr.size()-1);
	time_2 = glfwGetTime();
	std::cout << time_2 - time_1 << " s \n";
	}
	

	{
	pause(1);
	ivy arr(N, -1);
	std::cout << "std::sort: ";
	time_1 = glfwGetTime();
		std::sort(arr.begin(), arr.end());
	time_2 = glfwGetTime();
	std::cout << time_2 - time_1 << " s \n";
	}	

}

void user_thread(){

	TEST_SORT(25);
	TEST_SORT(50);
	TEST_SORT(100);
	TEST_SORT(200);
	TEST_SORT(400);

}







