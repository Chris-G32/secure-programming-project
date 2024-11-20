#ifndef ATTENDEE_HPP
#define ATTENDEE_HPP
#include <string>

class Attendee
{
private:
    std::string _name;
    bool _isEmployee;

public:
    bool operator<(const Attendee &rhs) const;
    bool operator==(const Attendee &rhs) const;
    bool isEmployee() const { return _isEmployee; }
    bool isGuest() const { return !_isEmployee; }
    const std::string &getName() const { return _name; }
    Attendee(const std::string &name, bool isEmployee) : _name(name), _isEmployee(isEmployee) {}
};
#endif