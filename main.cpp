#include <iostream>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>           
#include <sys/stat.h>
#include <cstdlib>


int main(int argc, char * argv[]) {

    for (int i = 0; i < argc; ++i) {

		std::cout << argv[i] << "\n";

    }

    mqd_t messageQueueDescriptorClient;

    if ((messageQueueDescriptorClient = mq_open(argv[1], O_RDONLY)) == -1) {
        perror ("cant open server from client");
        exit (1);
    }

    char outBuffer[512];

    if ((mq_receive(messageQueueDescriptorClient, outBuffer, 512, NULL)) == -1) {
        perror ("cant receive from server");
        exit (1);
    }

    std::cout << "reveived this:\n";
    std::cout << outBuffer << "\n";
    
    std::cout << "hello from the other executable\n";
    std::cin.get();
}
