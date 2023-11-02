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

namespace Event {

class EventQueue {
public:
    using valueType = std::unique_ptr<IEvent>;
    using container = std::deque<valueType>;
    using iterator = container::iterator;
    using const_iterator = container::const_iterator;
    using pointerType = valueType *;
    using reference_type = valueType &;

public:
    template <class Event> struct eventsIterator {

    public:
        explicit eventsIterator(pointerType ptr, pointerType end_ptr = nullptr)
            : _m_ptr(ptr)
            , _end_ptr(end_ptr)
        {
        }

        reference_type operator*() const
        {
            return *_m_ptr;
        }
        pointerType operator->()
        {
            return _m_ptr;
        }

        eventsIterator &operator++()
        {
            _m_ptr++;
            _iterations++;
            while (_m_ptr != _end_ptr
                   && not dynamic_cast<Event *>(_m_ptr->get())) {
                _m_ptr++;
                _iterations++;
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
            return a._m_ptr == b._m_ptr;
        };

        friend bool operator!=(eventsIterator const &a, eventsIterator const &b)
        {
            return a._m_ptr != b._m_ptr;
        };

    private:
        pointerType _m_ptr;
        pointerType _end_ptr;
        size_t _iterations = 0;
    };

public:
    template <class Event> eventsIterator<Event> eventIteratorBegin()
    {
        eventsIterator<Event> it(&_events[0], &_events[_events.size()]);

        if (it != end())
            it++;
        return it;
    }

    template <class Event> eventsIterator<Event> eventIteratorEnd()
    {
        return eventsIterator<Event>(&_events[_events.size()]);
    }

    template <class Event> Event const &getEvent()
    {
        for (auto &event : _events) {
            auto ptr = dynamic_cast<Event *>(event.get());

            if (ptr)
                return *ptr;
        }
    }

    template <class Event> void addEvent(Event const &event) noexcept
    {
        _events.push_back(std::make_unique<Event>(event));
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

#endif // R_TYPE_EVENTQUEUE_HPP
