#include <iostream>
#define TEST_ARRAY_SIZE 4

long int factorial(int num);

long int factorial(int num) {
	int limit = num;
	num = 1;
    for(int i = 1; i <= limit; i++) {
        num *= i;
    }
    
    return num;
}

int main() {
    int test[TEST_ARRAY_SIZE] = {1, 2, 5, 7};
    for (unsigned int i = 0; i < TEST_ARRAY_SIZE; i++) {
        std::cout << "Factorial of " << test[i] << " is " << factorial(test[i]) << std::endl;
    }
    
    return 0;
}