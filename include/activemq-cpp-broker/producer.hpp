#ifndef ACTIVEMQ_CPP_BROKER_PRODUCER_HPP
#define ACTIVEMQ_CPP_BROKER_PRODUCER_HPP

#include <string>
#include <cstdint>

#include <decaf/lang/Runnable.h>

#include <cms/Connection.h>
#include <cms/Session.h>

namespace amq {
class Producer : public decaf::lang::Runnable {
public:
    Producer(const std::string &brokerUri, uint32_t messageCount,
             bool shouldUseTopic, bool isSessionTransacted);
    virtual ~Producer();

    virtual void run() override;

private:
    Producer(const Producer &);
    Producer &operator=(const Producer &);

    cms::Connection *m_connection;
    cms::Session *m_session;
    cms::Destination *m_destination;
    cms::MessageProducer *m_messageProducer;

    uint32_t m_messageCount;
    bool m_shouldUseTopic;
    bool m_isSessionTransacted;
    std::string m_brokerUri;
};
} // namespace amq

#endif // ACTIVEMQ_CPP_BROKER_PRODUCER_HPP