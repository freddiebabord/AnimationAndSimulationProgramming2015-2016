/**
 @file      MessageCentre.hpp
 @author    Tyrone Davison
 @date      September 2012
 */

#pragma once
#ifndef __TYGA_MESSAGE_CENTRE__
#define __TYGA_MESSAGE_CENTRE__

// TODO: document me

#include "RunloopTaskProtocol.hpp"
#include <memory>
#include <string>

namespace tyga
{

class MessageListener;

class MessageCentre : public RunloopTaskProtocol
{
public:

    static std::shared_ptr<MessageCentre>
    defaultCentre();

    MessageCentre();

    ~MessageCentre();

    void
    addListener(std::shared_ptr<MessageListener> listener,
                std::string message_identifier);

    void
    removeListener(std::shared_ptr<MessageListener> listener);

private:

    virtual void
    runloopWillBegin(); // prepare new listener queues

    virtual void
    runloopExecuteTask(); /// iterate and call each listener as appropriate

    virtual void
    runloopDidEnd(); // update callback queues

};

} // end namespace tyga

#endif
