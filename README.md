# MIT OCW 6.096 - Introduction to C++
## Assignment 2
Nominally, I would submit this file with the assignment. However, since this is all taken from MIT Open Course Ware, it will just be my version of the solutions posted there (https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-096-introduction-to-c-january-iap-2011/assignments/). I've answered the questions asked in the assignment here. I've constructed the solutions to the various parts of the assignment in Assignment2Main.cpp.

The main method tests the functions of interest with a few simple test cases. I've only done the bare minimum of testing and do not account for some of the boundary cases that may or may not be caught by the code.
### 2 A Simple Function
What would the following print out?
```
void f(const int a = 5){
	std::cout << a*2 << "\n";
}

int a = 123;
int main() {
	f(1);
	f(a);
	int b = 3;
	f(b);
	int a = 4;
	f(a);
	f();
}
```
It would print out:  
2  
246  
6  
8  
10
This is a question about scope. The function multiplies the input by 2 and the prints it. There are 3 values for `a` that can potentially be used: the external one, which gets used in the first call of `f(a)`, because it is the only value available; the internal value of `a`, which gets used in the second instance as the compiler prioritizes the local scope; and the default value of `a`, which gets used in the last instance as the function is not being called with an argument.
### 3 Fix the Function
#### 3.1
```
#include <iostream>

int main() {
	printNum(35) ;
	return 0;
}

void printNum(int number) { std::cout << number; } 
```
Error: something along the lines of unknown function `printNum`. The idea is that the compiler has no idea what the code means by `printNum` until it is defined. Fix one:
```
#include <iostream>
void printNum (int number) { std::cout << number; } 

int main() {
	printNum(35);
	return 0;
}
```
This puts the whole function definition before `main` allowing for `main` to find it. Fix two:
```
#include <iostream>

void printNum (int number);

int main() {
	printNum(35);
	return 0;
}

void printNum (int number) { std::cout << number; }
```
This is called forward-declaring the function. The function definition is given, so the compiler knows what to expect from the prototype. The complete implementation is given later. This is very important for object oriented programming as it allows for us to separate the inteface and implementation of the functions.
#### 3.2
```
#include <iostream>

void printNum(){std::cout << number;};

int main() {
	int number = 35;
	printNum(number);
	return 0;
}
```
The `printNum` function never actually defines what number is actually supposed to be. Fix one:
```
#include <iostream>
int number = 35;
void printNum(){std::cout << number;};

int main() {
	printNum();
	return 0;
}
```
This takes the approach of using file variables to solve the problem. Or fix two:
```
#include <iostream>

void printNum(int number){std::cout << number;};

int main() {
	int number = 35;
	printNum(number);
	return 0;
}
```
This simply gives `printNum` an input argument. The second fix is preferred. As a best practice, one should avoid using anything with a wider scope than is necessary. In this case, number does not seem particularly special and the function itself is useless without. In fact even with it, it always prints the value of `number`. Overall, that feels like a very useless function. The first fix works and shows how file variable could work, but, in this case, seems like an unnecessary use.
#### 3.3
```
#include <iostream>

void doubleNumber(int num) {num = num * 2;}

int main(){
	int num = 35;
	doubleNumber(num);
	std::cout << num;
	return 0;
}
```
The idea is that `doubleNumber` should double the input. However, what actually happens is the compiler makes a local copy of `num` that is then locally doubled and deleted as soon as the function ends. Instead, use pass-by-reference instead of pass-by-copy. Fix:
```
#include <iostream>

void doubleNumber(int& num) {num = num * 2;}

int main(){
	int num = 35;
	doubleNumber(num);
	std::cout << num;
	return 0;
}
```
#### 3.4
```
#include <iostream>
#include <cstdlib>

int difference(const int x, const int y){
	int diff = abs(x - y);
}

int main(){
	std::cout << difference(24, 1238);
	return 0;
}
```
The function doesn't actually return a value. Fix:
```
#include <iostream>
#include <cstdlib>

int difference(const int x, const int y){
	return abs(x - y);
}

int main(){
	std::cout << difference(24, 1238);
	return 0;
}
```
#### 3.5
```
#include <iostream>

int sum(const int x, const int y){
	return x + y;
}

int main() {
	std::cout << sum(1, 2, 3); // Should print 6
	return 0;
}
```
It doesn't print 6 because the function is being called with too many arguments. Fix:
```
#include <iostream>

int sum(const int x, const int y){
	return x + y;
}

int main() {
	std::cout << sum(sum(1, 2), 3);
	return 0;
}
```
#### 3.6
```
#include <iostream>
const int ARRAY_LEN = 10;

int main() {
	int arr[ARRAY_LEN] = {10};
	int *xPtr = arr, yPtr = arr + ARRAY_LEN - 1;
	std::cout << *xPtr << ' ' << *yPtr; // Should output 10 0
	return 0;
}
```
It doesn't work because `yPtr` is not actually a pointer. Curiously, `int *` only applies the asterisks on the `xPtr` and not the `yPtr`. Thus, the compiler things that `yPtr` is actually an `int` and there is a type mismatch. Fix:
```
#include <iostream>
const int ARRAY_LEN = 10;

int main() {
	int arr[ARRAY_LEN] = {10};
	int *xPtr = arr, *yPtr = arr + ARRAY_LEN - 1;
	std::cout << *xPtr << ' ' << *yPtr; // Should output 10 0
	return 0;
}
```
#### 4.2
The syntax error comes from the fact that the compiler does not know which cast you want it to do. It knows that doubles and integers are both numeric types and can cast between the two. The problem though, is that it cannot decide if it should cast the 1 to a double or the 10.0 to an integer.
#### 4.4
The syntax error is similar to 4.2 in that the compiler does not know whether it should use the three argument version or the four argument version with default output due to both functions having the same prototype (3 integer inputs).