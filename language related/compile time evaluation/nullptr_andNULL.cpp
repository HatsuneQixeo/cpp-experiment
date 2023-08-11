#include <iostream>
using namespace std;

void foo(int *ptr) {
	cout << "foo(int* ptr) called" << endl;
	cout << ptr << endl;
}

// void foo(int &ref) {
//     cout << "foo(int& ref) called" << endl;
//     cout << &ref << endl;
// }

void foo(int n) {
	cout << "foo(int n) called" << endl;
}

int main() {
	// int *ptr = nullptr;
	// int &ref = *ptr; // This line will cause a runtime error

	// foo(nullptr);	// Calls foo(int* ptr)
	// foo(*ptr);		// Did not crash for some reason
	// foo(NULL);		// May cause ambiguity error
	// foo(1);			// works
	// foo((void *)0);	// also ambiguous, eventhough should be interpret as address
	// foo((int *)0);	// not anymore

	// int n1 = NULL; // does the implicit conversio and just generate compile warning
	// int n1 = (void *)0; // error
	// int n2 = nullptr; // gl reading c++ error
}