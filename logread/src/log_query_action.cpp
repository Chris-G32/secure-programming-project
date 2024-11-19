#include "log_query_action.hpp"
#include <iostream>
#include <list>
void RoomsQueryAction::execute(const Gallery &gallery)
{
    auto state = gallery.getGalleryState();
    auto attendeeState = state.find(_attendee);
    for (auto &event : attendeeState->second.first)
    {
        if (event.isRoomEntry())
        {
            std::cout << event.getRoomId().second << ",";
        }
    }
}
void StateQueryAction::execute(const Gallery &gallery)
{
    auto state = gallery.getGalleryState();
    std::map<RoomID, std::list<Attendee>> roomToAttendees;
    bool printComma = false;
    for (auto &attendeeState : state)
    {
        if (attendeeState.second.second == InRoom)
        {
            auto roomid = attendeeState.second.first.back().getRoomId().second;
            roomToAttendees[roomid].push_back(attendeeState.first);
        }
        if (attendeeState.first.isEmployee() && attendeeState.second.second != AttendeeState::OutsideGallery)
        {
            if (printComma)
            {
                std::cout << ",";
            }
            else
            {
                printComma = true;
            }
            std::cout << attendeeState.first.getName();
        }
    }
    std::cout << std::endl;
    printComma = false;
    for (auto &attendeeState : state)
    {
        if (attendeeState.first.isGuest() && attendeeState.second.second != AttendeeState::OutsideGallery)
        {
            if (printComma)
            {
                std::cout << ",";
            }
            else
            {
                printComma = true;
            }
            std::cout << attendeeState.first.getName();
        }
    }
    std::cout << std::endl;
    
    for (auto &roomOccupants : roomToAttendees)
    {
        roomOccupants.second.sort();
        std::cout << roomOccupants.first << ": ";
        printComma = false;
        for (auto &name : roomOccupants.second)
        {
            if (printComma)
            {
                std::cout << ",";
            }
            else
            {
                printComma = true;
            }
            std::cout << name.getName();
        }
        std::cout << std::endl;
    }
}