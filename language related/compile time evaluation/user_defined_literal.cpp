#include <iostream>
#include <string>

// Define a user-defined string literal for formatting
std::string operator""_f(const char* str, size_t size) {
	std::cout << "formatting " << str << " of size: " << size 	 << '\n';
	return std::string(str, size);
}

int main() {
	int value = 42;

	// Use the custom string literal for formatting
	std::string message = "The answer is "_f + std::to_string(value);

	std::cout << message << std::endl;

	return 0;
}
