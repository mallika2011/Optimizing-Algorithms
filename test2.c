#include <stdio.h> 

// Inline function in C 
inline int foo() 
{ 
	return 2; 
} 

// Driver code 
int main() 
{ 

	int ret; 

	// inline function call 
	ret = foo(); 

	printf("Output is: %d\n", ret); 
	return 0; 
} 
