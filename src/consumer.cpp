#include "activemq-cpp-broker/consumer.hpp"

#include <iostream>

namespace amq {
Consumer::Consumer(const std::string &brokerUri, uint32_t messageCount,
                   bool shouldUseTopic, bool isSessionTransacted,
                   uint64_t waitDurationMilliseconds)
    : m_latch(1), m_completedLatch(messageCount), m_connection(nullptr),
      m_session(nullptr), m_destination(nullptr), m_messageConsumer(nullptr),
      m_waitDurationMilliseconds(waitDurationMilliseconds),
      m_shouldUseTopic(shouldUseTopic),
      m_isSessionTransacted(isSessionTransacted), m_brokerUri(brokerUri) {}

Consumer::~Consumer() {
    if (m_connection) {
        try {
            m_connection->close();
        } catch (const cms::CMSException &e) {
            e.printStackTrace();
        }

        try {
            delete m_destination;
            m_destination = nullptr;

            delete m_messageConsumer;
            m_messageConsumer = nullptr;

            delete m_session;
            m_session = nullptr;

            delete m_connection;
            m_session = nullptr;
        } catch (const cms::CMSException &e) {
            e.printStackTrace();
        }
    }
}

void Consumer::onException(const cms::CMSException &ex) {
    std::cout << "CMS Exception occrured! Shutting down client...\n";
    ex.printStackTrace();
    exit(EXIT_FAILURE);
}

void Consumer::onMessage(const cms::Message *message) {
    static int count = 0;
    try
    {
        ++count;
        const cms::TextMessage *textMessage = dynamic_cast<const cms::TextMessage *>(message);
        std::string text = "";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void Consumer::run() {

}

void Consumer::waitUntilReady() {
    
}

} // namespace amq
