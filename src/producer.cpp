#include "activemq-cpp-broker/producer.hpp"

#include <memory>
#include <iostream>

#include <activemq/core/ActiveMQConnectionFactory.h>

#include <cms/TextMessage.h>

#include <decaf/lang/Long.h>
#include <decaf/lang/Thread.h>

namespace amq {
Producer::Producer(const std::string &brokerUri, uint32_t messageCount,
                   bool shouldUseTopic, bool isSessionTransacted)
    : m_connection(nullptr), m_session(nullptr), m_destination(nullptr),
      m_messageProducer(nullptr), m_messageCount(messageCount),
      m_shouldUseTopic(shouldUseTopic),
      m_isSessionTransacted(isSessionTransacted), m_brokerUri(brokerUri) {}

Producer::~Producer() {
    // If the connection is non-null, attempt to close it.
    if (m_connection) {
        try {
            m_connection->close();
        } catch (const cms::CMSException &e) {
            e.printStackTrace();
        }
    }

    // Free resources
    try {
        delete m_destination;
        m_destination = nullptr;

        delete m_messageProducer;
        m_messageProducer = nullptr;

        delete m_session;
        m_session = nullptr;

        delete m_connection;
        m_connection = nullptr;
    } catch (const cms::CMSException &e) {
        e.printStackTrace();
    }
}

void Producer::run() {
    try {
        // Create a connection factory
        std::unique_ptr<cms::ConnectionFactory> connectionFactory(
            cms::ConnectionFactory::createCMSConnectionFactory(m_brokerUri));

        // Create a connection
        m_connection = connectionFactory->createConnection();
        m_connection->start();

        // Create a session
        if (m_isSessionTransacted) {
            m_session =
                m_connection->createSession(cms::Session::SESSION_TRANSACTED);
        } else {
            m_session =
                m_connection->createSession(cms::Session::AUTO_ACKNOWLEDGE);
        }

        // Create the destination (topic or queue)
        if (m_shouldUseTopic) {
            m_destination = m_session->createTopic("TestTopicName.foo");
        } else {
            m_destination = m_session->createQueue("TestQueueName.foo");
        }

        // Create a message producer from the session to the topic/queue
        m_messageProducer = m_session->createProducer(m_destination);
        m_messageProducer->setDeliveryMode(cms::DeliveryMode::NON_PERSISTENT);

        // Create a thread id string
        std::string threadIdString = decaf::lang::Long::toString(
            decaf::lang::Thread::currentThread()->getId());

        // Create message string using threadId
        std::string threadMessage =
            "Hello, World! from thread " + threadIdString;

        for (uint32_t i = 0; i < m_messageCount; ++i) {
            std::unique_ptr<cms::TextMessage> message(
                m_session->createTextMessage(threadMessage));
            message->setIntProperty("Integer", i);

            m_messageProducer->send(message.get());
            std::cout << "Sent message " << i + 1 << ", from thread "
                      << threadIdString << '\n';
        }

    } catch (const cms::CMSException &e) {
        e.printStackTrace();
    }
}

} // namespace amq
