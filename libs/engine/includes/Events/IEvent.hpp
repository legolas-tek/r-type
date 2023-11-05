/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Interface of events
*/

#ifndef R_TYPE_INTERFACE_EVENT_HPP
#define R_TYPE_INTERFACE_EVENT_HPP

#include <iosfwd>

namespace event {

class IEvent {
public:
    virtual ~IEvent() = default;
    /**
     * @brief dumps the event to an output stream (for debugging).
     * By default, it outputs the mangled name of the class.
     * @param stream
     */
    virtual void dump(std::ostream &) const;
};

}

inline std::ostream &operator<<(std::ostream &stream, event::IEvent &event)
{
    event.dump(stream);
    return stream;
}

#endif // R_TYPE_INTERFACE_EVENT_HPP
