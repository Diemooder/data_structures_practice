#include <stdio.h>

int nums_length = 6;
int nums[nums_length] = {8,7,2,5,3,1};
int target = 10; 
int *valid_pairs = malloc(6 * sizeof(int));
int current_pair = 0;

for(int i = 0; i < nums_length; i++){
	for(int j = 0; j < nums_length; j++){
		i == j ? continue : Null;
		int result = nums[i] + nums[j];
		if(result == target){
			*(valid_pairs * current_pair + 0) = nums[j];
			*(valid_pairs * current_pair + 1) = nums[i];
		}
	}
}	

for(int i = 0; i <= current_pair; i += 2){
	printf("%d and %d is a valid pair for %d", *(valid_pairs + i), *(valid_pairs + i + 1), target);
}
