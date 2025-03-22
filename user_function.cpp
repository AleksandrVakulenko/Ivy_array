#include <iostream>
#include "utils.h"
#include "graphics.h"
#include "drawer.h"
#include "slow_array.h"

void user_func(){
	
	
	slow_array arr = {99, 1, 2, 3, 5, 6, 22, 33, 44, 55, 66, 77, 4, 5, 6, 7, 8, 9, 10, 33, 44, 99,
					33, 12,43,46,75,86,34,45,75,35,68,35,57,67,90};
	
	for (int i = 0; i < arr.size(); i+=1)
		arr[i];
	
	pause(0.5);
}







