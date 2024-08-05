#include <iostream>

void foo(int *ptr) {
	std::cout << "foo(int* ptr) called" << std::endl;
	std::cout << ptr << std::endl;
}

void foo(int n) {
	std::cout << "foo(int n) called" << std::endl;
	(void)n;
}

int main() {
	int *const	ptr = nullptr;
	int			&ref = *ptr;

	// foo(ref); // funnily enough, it doesn't crash until ref is getting read
	foo(nullptr);	// Calls foo(int* ptr)
	// foo(NULL);		// ambiguous call
	foo(1);			// works
	// foo((void *)0);	// also ambiguous, eventhough should be interpret as address
	foo((int *)0); // works

	// int n1 = NULL; // does the implicit conversion and just generate compile warning
	// int n1 = (void *)0; // error
	// int n2 = nullptr; // gl reading c++ error
}