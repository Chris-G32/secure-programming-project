#ifndef GALLERY_HPP
#define GALLERY_HPP
#include <map>
#include "attendee_state.hpp"
#include "attendee.hpp"
#include <string>
#include <iostream>
#include "typedefs.hpp"

class Gallery
{
protected:
    std::map<Attendee, EventLog> _gallery; // NOTE: You cannot use the [] operator bc we do not want the event logs to be called without args ever.
public:
    Gallery(const std::string &);
    ~Gallery();
};

Gallery::Gallery(const std::string &logFilePath)
{
    
}

Gallery::~Gallery()
{
}

#endif