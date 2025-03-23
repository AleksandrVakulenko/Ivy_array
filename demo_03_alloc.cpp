#include "ivy_array/inc/ivy.h"
#include "ivy_array/inc/utils.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>




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

	#ifndef LEAK
	for(auto el:array_of_ivy)
		delete el;
	#endif
}







