#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <unistd.h>

/**
 * @brief Union only work on primitive types, such as int, char, etc.
 * 
 * Classes need to utilise polymorphism to have one type representing dynamic types.
 * 
 * Following are experiments with IBody as the interface for different kinds of reading from different sources.
 */

// struct ClassA
// {
// 	std::string	_str;
// 	ClassA(void) : _str("ClassB") {
// 		std::cout << "ClassA(void)" << std::endl;
// 	}
// 	~ClassA(void) {
// 		std::cout << "~ClassA(void)" << std::endl;
// 	}
// };

// struct ClassB
// {
// 	std::string	_str;
// 	ClassB(void) : _str("ClassB") {
// 		std::cout << "ClassB(void)" << std::endl;
// 	}
// 	~ClassB(void) {
// 		std::cout << "~ClassB(void)" << std::endl;
// 	}
// };

// union Union
// {
// 	// ClassA	_classA;
// 	std::string	str;
// 	int			a;
// 	char		b;
// 	// ClassB	_classB;
// 	Union(void) {
// 		std::cout << "Union(void)" << std::endl;
// 	}
// 	~Union(void) {
// 		std::cout << "~Union(void)" << std::endl;
// 	}
// };


// union uu
// {
// 	std::string		body;
// 	std::ifstream	ifs;

// 	uu(void) {
// 		std::cout << "uu(void)" << std::endl;
// 	}
// 	~uu(void) {
// 		std::cout << "~uu(void)" << std::endl;
// 	}
// };

class IBody
{
	public:
		virtual ~IBody(void) {}
		virtual bool	isOpen(void) const = 0;
		virtual ssize_t	readBody(char *buffer, const size_t bytes) = 0;
};

class StringBody: public IBody
{
	private:
		std::string	_body;

	public:
		StringBody(const std::string &str):
			_body(str) {}
		~StringBody(void) {}

		bool	isOpen(void) const { return (true); }

		ssize_t	readBody(char *buffer, const size_t bytes) {
			const size_t	length = std::min(bytes, this->_body.size());

			memcpy(buffer, this->_body.c_str(), length);
			this->_body.erase(0, length);
			return (length);
		}
};

class FileBody: public IBody
{
	private:
		std::ifstream	_file;

	public:
		FileBody(const std::string &filename):
			_file(filename) {}
		~FileBody(void) {}

		bool	isOpen(void) const { return (this->_file.is_open()); }

		ssize_t	readBody(char *buffer, const size_t bytes) {
			this->_file.read(buffer, bytes);
			return (this->_file.gcount());
		}
};

class SocketBody: public IBody
{
	private:
		int			_fd;
		const int	_flags;

	public:
		SocketBody(const int fd, const int flags = 0):
			_fd(fd),
			_flags(flags) {}
		~SocketBody(void) {}

		bool	isOpen(void) const { return (this->_fd != -1); }

		ssize_t	readBody(char *buffer, const size_t bytes) {
			return (read(this->_fd, buffer, bytes));
			(void)this->_flags;
			// return (recv(this->_fd, buffer, bytes, this->_flags));
		}
};


void	tryRead(IBody *body, const size_t buffer_size)
{
	char	*buffer = new char[buffer_size];
	size_t	bytes_read = buffer_size;

	if (buffer == nullptr)
	{
		std::cerr << "Error allocating buffer: " << strerror(errno) << std::endl;
		return ;
	}
	while (bytes_read == buffer_size)
	{
		bytes_read = body->readBody(&buffer[0], buffer_size);
		buffer[bytes_read] = '\0';
		if (bytes_read == 0)
			break ;
		else if (bytes_read == SIZE_MAX)
		{
			std::cout << '\n';
			throw (std::system_error(errno, std::system_category(), "Error reading from body"));
		}
		std::cout << buffer;
	}
	std::cout << '\n';
	delete[] buffer;
}

int	main(void)
{
	IBody	*str = new StringBody("Hatsune Miku is cute");
	IBody	*file = new FileBody(".gitignore");
	IBody	*sock = new SocketBody(0);

	std::cout << "StringBody: " << str->isOpen() << std::endl;
	std::cout << "FileBody: " << file->isOpen() << std::endl;
	std::cout << "SocketBody: " << sock->isOpen() << std::endl;

	try
	{
		std::cout << "StringBody: ";
		tryRead(str, 10);
		std::cout << "FileBody: ";
		tryRead(file, 10);
		std::cout << "SocketBody: ";
		tryRead(sock, 10);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	delete str;
	delete file;
	delete sock;
}
