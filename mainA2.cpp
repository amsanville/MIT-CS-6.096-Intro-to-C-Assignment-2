#include<iostream>
using namespace std;

/*
4.1: Functions for calculating the sum of two integers and two doubles
*/
int sum(int a, int b) { return a + b; }
double sum(double a, double b) { return a + b; }
/*
4.2
*/

/*
4.3: Functions for summing 3 and 4 things
*/
int sum(int a, int b, int c) { return a + b + c; }
//int sum(int a, int b, int c, int d) { return a + b + c + d; }
//^ commented out as it conflicts directly with part 4.4

/*
4.4: Function for summing with default arguments 
*/
int sum(int a, int b, int c = 0, int d = 0) { return a + b + c + d; }

/*
4.5: Function for summing arbitrarily large set of integers

int sum(int arr[], int arrSize) {
	int total = 0;
	for (int i = 0; i < arrSize; i++) {
		total += arr[i];
	}
	return total;
}
^ Commented out so recursive version can be tested.
*/

/*
4.6: Recursive version of summing an arbitrary number of integers
*/
int sum(int arr[], int arrSize) {
	if (arrSize > 0) {
		return arr[0] + sum(arr + 1, arrSize - 1);
	}
	else {
		return 0;
	}
}

/*
5: Monte Carlo Calculation of Pi

For this problem, we use Monte Carlo simulation methods to calculate pi. The
way this is accomplished is by randomly throwing darts at a square with a
circle inscribed within it. The idea is that the ratio of the area of the
circle to the square is (pi r^2)/(4 r^2) = pi/4, which we can estimate from
the random experiment.

Centering the circle at origin and recognizing the symmetry of the random
experiment, we see that we only have to select random numbers in the first
quadrant. We then uniformly select random numbers for x and y from 0 to 1
and calculate: a = x^2 + y^2. We see that if a <=1 the point fell within the
circle. Finally, we estimate the ratio as the number of points in the circle
over the total number of points. This should be approximate pi/4.

The spec for this function is as follows (all randomness will use rand):
@param n the number of points for the MC calculation
@return the estimate of pi
*/
double estimateOfPi(int n) {
	// Randomly generate the points on [0, 1] and check if they are in the
	// circle
	int count = 0;
	for (int i = 0; i < n; i++) {
		double x = ((double)rand()) / ((double)RAND_MAX);
		double y = ((double)rand()) / ((double)RAND_MAX);
		if (pow(x, 2.) + pow(y, 2.) <= 1) {
			count++;
		}
	}

	// Estimate the value of pi
	return 4 * ((double)count) / ((double)n);
}

/*
6.1 Print contents of array delimited by ", "
*/
void printArray(int arr[], int arrSize) {
	for (int i = 0; i < arrSize - 1; i++) {
		cout << arr[i] << ", ";
	}
	// Special last case
	cout << arr[arrSize - 1] << endl;
}

/*
6.2 Reverse an array in place

Note: since arrays are actually just pointers
*/
void reverse(int arr[], int arrSize) {
	for (int i = 0; i < arrSize / 2; i++) {
		int temp = arr[i];
		arr[i] = arr[arrSize - 1 - i];
		arr[arrSize - 1 - i] = temp;
	}
}

/*
6.3 Transpose array

Transpose the input array and store it in the output array.
*/
const int LENGTH = 4;
const int WIDTH = 3;
void transpose(const int input[][LENGTH], int output[][WIDTH]) {
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			output[j][i] = input[i][j];
		}
	}
}

/*
6.4 Declaring the output in the function

You can't formally return an array from a function in C++. The best you can do
is return a pointer (or in this case a pointer to a pointer). Here, I've
implemented the transpose to create an output in the function. One major
difference between this and the above is the introduction of heap memory. The
output array is declared on the heap and can thus cause memory leaks if we are
not careful.
*/

int** transpose2(const int input[][LENGTH]) {
	// Entirely on the heap
	int** output = new int*[LENGTH];
	for (int j = 0; j < LENGTH; j++) {
		output[j] = new int[WIDTH];
	}

	// Transpose
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < LENGTH; j++) {
			output[j][i] = input[i][j];
		}
	}

	// Return
	return output;
}


/*
6.5 Reverse an array in place using array pointer math
*/
void reverse2(int arr[], int arrSize) {
	for (int i = 0; i < arrSize / 2; i++) {
		int temp = *(arr + i);
		*(arr + i) = *(arr + arrSize - 1 - i);
		*(arr + arrSize - 1 - i) = temp;
	}
}

/*
7.1 Find the length of a string (i.e. a character array) excluding the final 
NULL chracter using only arithmetic and dereference operators.
*/
int stringLength(char* str) {
	int i = 0;
	while (*(str + i) != '\0') {
		i++;
	}
	return i;
}

/*
7.2 Swap two integers using call-by-reference
*/
void swap1(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

/*
7.3 Swap two integers using pointers, swap by dereferencing
*/
void swap2(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}


/*
7.4 Swap two integers using pointers, swap by swapping pointer location
*/
void swap3(int** a, int** b) {
	int* temp = *a;
	*a = *b;
	*b = temp;
}

/*
7.5 Follow the steps from the PDF
*/
void doTasks() {
	// Declare the memory
	char oddOrEven[] = "Never odd or even";
	// Create a pointer to point to the 6th character of oddOrEven
	char* nthCharPtr = &oddOrEven[5];
	// Using pointer arithmetic, update to point to the 4th character
	nthCharPtr -= 2;
	// Print the value currently pointed to
	cout  << *nthCharPtr  << endl; // e
	// Create a new pointer that points to nthCharPtr
	char** pointerPtr = &nthCharPtr;
	// Print the value stored in pointerPtr
	cout << pointerPtr << endl; // Memory address
	// Print the value pointed to by nthCharPtr using this new pointer
	cout << *(*pointerPtr) << endl; // e
	// Update nthCharPtr to point to the next character
	nthCharPtr++;
	// Using pointer arithmetic, print out how far away from the character
	// currently being pointed to by nthCharPtr is from the start
	cout << nthCharPtr - oddOrEven << endl; // 4

}

int main() {
	// 4: Test sum
	int test0[] = { 0, 1, 2, 3, 4, 5, 6 };
	cout << sum(test0, 7) << endl; // 21

	// 5: Estimate of pi
	srand(0);
	cout << estimateOfPi(5000000) << endl; // Approximately pi = 3.14159

	// 6: Test array functions
	int test1[] = { 1, 2, 3 };
	int test2[] = { 4, 5, 6, 7 };
	int test3[][LENGTH] = { {1, 2, 3, 0}, {4, 5, 6, 0}, {7, 8, 9, 0} };
	int test4[][WIDTH] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
	// 6.1 - test printing
	printArray(test1, 3); // 1 2 3

	// 6.2 - test reverseal
	reverse(test1, 3); 
	printArray(test1, 3); // 3 2 1
	reverse(test2, 4);
	printArray(test2, 4); // 7 6 5 4
	
	// 6.3 - test first method for transposition
	cout << "Transpose attempt 1:" << endl;
	transpose(test3, test4);
 	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < WIDTH - 1; j++) {
			cout << test4[i][j] << ", ";
		}
		cout << test4[i][WIDTH - 1] << endl;
	}
	cout << endl;

	// 6.4 - test other two methods for transposition
	cout << "Transpose attempt 2:" << endl;
	int** test5 = transpose2(test3);
	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < WIDTH - 1; j++) {
			cout << test5[i][j] << ", ";
		}
		cout << test5[i][WIDTH - 1] << endl;
	}
	cout << endl;

	// 6.5 - test second method of reversal
	reverse2(test1, 3); // 1 2 3
	printArray(test1, 3);
	reverse2(test2, 4); // 4 5 6 7
	printArray(test2, 4);

	// 7: Tests
	// 7.1
	char str[] = "Hello!";
	cout << "Lenght of str: " << stringLength(str) << endl; // 6
	// 7.2
	int a = 0;
	int b = 1;
	cout << "Initial a: " << a << " b: "<< b << endl; // 0 1
	swap1(a, b);
	cout << "First Swap a: " << a << " b: " << b << endl; // 1 0
	// 7.3
	swap2(&a, &b);
	cout << "Second Swap a: " << a << " b: " << b << endl; // 0 1
	// 7.4
	int x = 5, y = 6;
	int* ptr1 = &x, *ptr2 = &y;
	swap3(&ptr1, &ptr2);
	cout << *ptr1 << ' ' << *ptr2 << endl; // 6 5
	// 7.5
	doTasks();

	return 0;
}