// #ifndef ACTIONS_HPP
// #define ACTIONS_HPP
// #include "attendee_state.hpp"
// #include "typedefs.hpp"
// #include <exception>
// #include <stdexcept>
// enum ActionEnum
// {
//     Leave,
//     Arrive
// };

// class Action
// {
// protected:
//     ActionEnum _action;

// public:
//     Action() = delete;
//     Action(ActionEnum action) : _action(action) {}
//     ActionEnum getAction() { return _action; }
//     virtual void apply(EventLog &log)
//     {
//         switch (_action)
//         {
//         case Leave:
//             log.transitionState(log.getState()->leave());
//             break;
//         case Arrive:
//             log.transitionState(log.getState()->arrive());
//             break;
//         default:
//             throw std::domain_error("Action not supported.");
//         }
//     }
// };

// class RoomAction : public Action
// {
// private:
//     RoomID _room;

// public:
//     RoomAction(ActionEnum action, unsigned long room) : Action(action), _room(room) {}
//     RoomAction(Action action, unsigned long room) : RoomAction(action.getAction(), room) {}

//     virtual void apply(EventLog &log)
//     {
//         switch (_action)
//         {
//         case Leave:
//             log.transitionState(log.getState()->leave(_room));
//             break;
//         case Arrive:
//             log.transitionState(log.getState()->arrive(_room));
//             break;
//         default:
//             throw std::domain_error("Action not supported.");
//         }
//     }
// };
// #endif