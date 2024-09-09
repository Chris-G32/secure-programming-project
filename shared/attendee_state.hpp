#ifndef ATTENDEE_STATE_HPP
#define ATTENDEE_STATE_HPP
#include <exception>
#include <string>
#include "attendee.hpp"
class StateTransitionNotSupportedError : public std::exception
{
private:
    std::string message;

public:
    // Constructor to initialize the custom message
    explicit StateTransitionNotSupportedError(const std::string &msg)
        : message("StateTransitionNotSupportedError: " + msg) {}

    // Override the what() method to return the custom message
    const char *what() const noexcept override
    {
        return message.c_str();
    }
};

enum AttendeeStateEnum
{
    Outside,
    InGallery,
    InRoom
};

class AttendeeState
{
public:
    virtual AttendeeState *clone() const = 0;
    virtual AttendeeState *arrive() { throw StateTransitionNotSupportedError("Cannot perform arrive from the given state"); }
    virtual AttendeeState *arrive(unsigned long room) { throw StateTransitionNotSupportedError("Cannot perform arrive from the given state"); }
    virtual AttendeeState *leave() { throw StateTransitionNotSupportedError("Cannot perform arrive from the given state"); }
    virtual AttendeeState *leave(unsigned long room) { throw StateTransitionNotSupportedError("Cannot perform arrive from the given state"); }
    virtual AttendeeStateEnum getState() = 0;
};

class InRoomState : public AttendeeState
{
public:
    virtual AttendeeState *leave(unsigned long room) override;
    virtual AttendeeStateEnum getState() { return AttendeeStateEnum::InRoom; }
    unsigned long getRoom() { return _room; }
    virtual InRoomState *clone() const override { return new InRoomState(_room); }

private:
    friend class InGalleryState;
    InRoomState(unsigned long room) : _room(room) {}
    unsigned long _room;
};

class OutsideState : public AttendeeState
{
public:
    virtual AttendeeState *arrive() override;
    virtual AttendeeStateEnum getState() { return AttendeeStateEnum::Outside; }
    virtual OutsideState *clone() const override { return new OutsideState(); }
};

class InGalleryState : public AttendeeState
{
public:
    virtual InGalleryState *clone() const override { return new InGalleryState(); }

    virtual AttendeeState *arrive(unsigned long room) override
    {
        return new InRoomState(room);
    }
    virtual AttendeeState *leave() override
    {
        return new OutsideState();
    }
    virtual AttendeeStateEnum getState() { return AttendeeStateEnum::InGallery; }
};

AttendeeState *InRoomState::leave(unsigned long room)
{
    if (room != _room)
    {
        throw new StateTransitionNotSupportedError("Invalid room provided to leave.");
    };
    return new InGalleryState();
}
AttendeeState *OutsideState::arrive()
{
    return new InGalleryState();
}
#endif