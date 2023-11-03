/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Event encapsulation
*/

#ifndef R_TYPE_EVENT_HPP
#define R_TYPE_EVENT_HPP

#include <deque>
#include <memory>
#include <stdexcept>

#include "Entity.hpp"
#include "IEvent.hpp"

#include <iostream>

namespace Event {

class EventQueue {
public:
    using valueType = std::unique_ptr<IEvent>;
    using container = std::deque<valueType>;
    using iterator = container::iterator;
    using const_iterator = container::const_iterator;
    using pointerType = valueType *;
    using referenceType = valueType &;

public:
    template <class Event> struct eventsIterator {

    public:
        explicit eventsIterator(iterator it, iterator end)
            : _it(_it)
            , _end(end)
        {
        }

        referenceType operator*() const
        {
            return *_it;
        }
        pointerType operator->()
        {
            return _it.operator->();
        }

        eventsIterator &operator++()
        {
            _it++;
            while (_it != _end
                   && not dynamic_cast<Event *>(_it->get())) {
                _it++;
            }
            return *this;
        }

        eventsIterator operator++(int)
        {
            eventsIterator tmp = *this;

            ++(*this);
            return tmp;
        }

        friend bool operator==(eventsIterator const &a, eventsIterator const &b)
        {
            return a._it == b._it;
        };

        friend bool operator!=(eventsIterator const &a, eventsIterator const &b)
        {
            return a._it != b._it;
        };

    private:
        iterator _it;
        iterator _end;
    };

public:
    template <class Event> eventsIterator<Event> beginIterator()
    {
        eventsIterator<Event> it(_events.begin(), _events.end());

        if (it != endIterator<Event>() and not dynamic_cast<Event *>(it->get()))
            it++;
        return it;
    }

    template <class Event> eventsIterator<Event> endIterator()
    {
        return eventsIterator<Event>(_events.end(), _events.end());
    }

    template <class Event> Event const &getEvent()
    {
        for (auto &event : _events) {
            auto ptr = dynamic_cast<Event *>(event.get());

            if (ptr)
                return *ptr;
        }
    }

    template <class Event, class... Params> void addEvent(Params &&...params)
    {
        _events.push_back(std::make_unique<Event>(std::forward<Params>(params)...));
    }

    template <class Event> void eraseEvent(Event event) noexcept
    {
        for (auto it = _events.begin(); it != _events.end(); it++) {
            auto ptr = dynamic_cast<Event *>(it->get());

            if (ptr && *ptr == event) {
                _events.erase(it);
                return;
            }
        }
    }

    template <class Event> Event const &popEvent()
    {
        for (auto it = _events.begin(); it != _events.end(); it++) {
            auto ptr = dynamic_cast<Event *>(it->get());

            if (ptr) {
                Event event = *ptr;
                _events.erase(it);
                return event;
            }
        }
        throw std::runtime_error("EventQueue not found");
    }

    iterator begin() noexcept
    {
        return _events.begin();
    }

    iterator end() noexcept
    {
        return _events.end();
    }

    [[nodiscard]] const_iterator begin() const noexcept
    {
        return _events.begin();
    }

    [[nodiscard]] const_iterator end() const noexcept
    {
        return _events.end();
    }

    void clear() noexcept
    {
        _events.clear();
    }

private:
    std::deque<std::unique_ptr<IEvent>> _events;
};

}

#endif // !R_TYPE_EVENT_HPP
