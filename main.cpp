#include "MessageQueue.h"

#include <iostream>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>           
#include <sys/stat.h>
#include <cstdlib>
#include <array>


int main(int argc, char * argv[]) {

    for (int i = 0; i < argc; ++i) {

		std::cout << argv[i] << "\n";

    }

	logger::MessageQueue read = logger::MessageQueue::open(argv[1], logger::MessageQueueMode::read);

	std::array<char, 4096> buffer = 
		std::array<char, 4096>{};

	unsigned int bytesRead = read.read( logger::Buffer {
		buffer.data(),
		buffer.size()
	});

	std::cout << "I read " << bytesRead << " bytes\n";
    

    std::cout << "reveived this:\n";
    std::cout << buffer.data() << "\n";
    
    std::cin.get();
}
