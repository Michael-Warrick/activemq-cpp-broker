#ifndef ACTIVEMQ_CPP_BROKER_CONSUMER_HPP
#define ACTIVEMQ_CPP_BROKER_CONSUMER_HPP

#include <string>
#include <cstdint>

#include <decaf/lang/Runnable.h>
#include <decaf/util/concurrent/CountDownLatch.h>

#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/Destination.h>
#include <cms/MessageConsumer.h>

namespace amq {
class Consumer : public cms::ExceptionListener,
                 public cms::MessageListener,
                 public decaf::lang::Runnable {
public:
    Consumer(const std::string &brokerUri, uint32_t messageCount,
             bool shouldUseTopic, bool isSessionTransacted,
             uint64_t waitDurationMilliseconds);
    virtual ~Consumer();

    virtual void onException(const cms::CMSException &ex) override;
    virtual void onMessage(const cms::Message *message) override;
    virtual void run() override;

    void waitUntilReady();

private:
    Consumer(const Consumer &);
    Consumer &operator=(const Consumer &);

    decaf::util::concurrent::CountDownLatch m_latch;
    decaf::util::concurrent::CountDownLatch m_completedLatch;
    cms::Connection *m_connection;
    cms::Session *m_session;
    cms::Destination *m_destination;
    cms::MessageConsumer *m_messageConsumer;
    uint64_t m_waitDurationMilliseconds;
    bool m_shouldUseTopic;
    bool m_isSessionTransacted;
    std::string m_brokerUri;
};

} // namespace amq

#endif // ACTIVEMQ_CPP_BROKER_CONSUMER_HPP