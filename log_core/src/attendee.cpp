#include "attendee.hpp"
bool Attendee::operator<(const Attendee &rhs) const
{
    if (rhs._isEmployee == _isEmployee)
    {
        return _name < rhs._name;
    }

    return rhs._isEmployee;
}
bool Attendee::operator==(const Attendee &rhs) const
{
    return _isEmployee == rhs._isEmployee && _name == rhs._name;
}