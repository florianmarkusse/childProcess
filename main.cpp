#include "MessageQueue.h"

#include <iostream>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>           
#include <sys/stat.h>
#include <cstdlib>
#include <array>

#define MESSAGE_SIZE 4096

#define EXIT_CHAR 1
#define INFO_CHAR 2
#define WARN_CHAR 3
#define ERROR_CHAR 4
#define SUCCESS_CHAR 5

#define NORMAL  "\x1B[0m" 
#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"
#define YELLOW  "\x1B[33m"


int main(int argc, char * argv[]) {

	if (argc != 2) {
		std::cerr 
			<< "not enough arguments\n"
			<< "call syntax: main [Messagequeue name]"
			<< std::endl;
		return EXIT_FAILURE;
	}

	logger::MessageQueue read = logger::MessageQueue::open(argv[1], logger::MessageQueueMode::read);

	std::array<char, MESSAGE_SIZE> buffer = 
		std::array<char, MESSAGE_SIZE>{};

	bool isQueueOpen = true;

	while (isQueueOpen) {

		unsigned int bytesRead = read.read( logger::Buffer {
			buffer.data(),
			buffer.size()
		});
		
		for (unsigned int i = 0; i < bytesRead; ++i) {

			switch (static_cast<unsigned int> (buffer[i]))
			{
				case EXIT_CHAR: {
					isQueueOpen = false;
				}
					break;
				case INFO_CHAR: {
					printf("%s", NORMAL);
				}
					break;
				case WARN_CHAR: {
					printf("%s", YELLOW);
				}
					break;
				case ERROR_CHAR: {
					printf("%s", RED);
				}
					break;
				case SUCCESS_CHAR: {
					printf("%s", GREEN);
				}
					break;
				default: {
					std::cout << buffer[i];
				}
					break;
			}

		}

	}

	return EXIT_SUCCESS;
}
