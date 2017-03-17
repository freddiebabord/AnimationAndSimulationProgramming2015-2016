/**
 @file      MessageListener.hpp
 @author    Tyrone Davison
 @date      September 2012
 */

#pragma once
#ifndef __TYGA_MESSAGE_LISTENER__
#define __TYGA_MESSAGE_LISTENER__

// TODO: document me

#include <memory>
#include <string>
#include <unordered_map>

namespace tyga
{

class MessageCentre;

typedef std::unordered_map<std::string, std::string> MessageParameter;

class MessageListener
{
public:

    virtual void
    messageNotification(std::shared_ptr<MessageCentre> message_centre,
                        std::string message_identifier,
                        std::shared_ptr<void> object,
                        std::shared_ptr<const MessageParameter> params) =0;

};

} // end namespace tyga

#endif
