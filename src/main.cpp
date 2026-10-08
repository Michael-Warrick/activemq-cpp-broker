#include <iostream>
#include <activemq/library/ActiveMQCPP.h>

int main(int argc, char *argv[]) {
    activemq::library::ActiveMQCPP::initializeLibrary();
    std::cout << "ActiveMQ-CPP Init\n";

    activemq::library::ActiveMQCPP::shutdownLibrary();
    std::cout << "ActiveMQ-CPP Shutdown\n";

    return 0;
}