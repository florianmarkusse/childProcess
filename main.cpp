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
			if (static_cast<unsigned int> (buffer[i]) == EXIT_CHAR) {
				isQueueOpen = false;
				std::cout << "set to false\n";
			} else {
				std::cout << buffer[i];
			}
		}

	}

	return EXIT_SUCCESS;
}
