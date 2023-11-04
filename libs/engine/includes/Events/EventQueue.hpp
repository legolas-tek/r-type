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
#include <utility>

namespace Event {

class EventQueue {
public:
    using ValueType = std::unique_ptr<IEvent>;
    using Container = std::deque<ValueType>;
    using Iterator = Container::iterator;
    using ConstIterator = Container::const_iterator;

public:
    template <class Event> struct EventsIterator {

    public:
        explicit EventsIterator(Iterator it, Iterator end)
            : _it(std::move(it))
            , _end(std::move(end))
        {
            while (_it != _end && not dynamic_cast<Event *>(_it->get())) {
                _it++;
            }
        }

        Event &operator*() const
        {
            return dynamic_cast<Event &>(*_it);
        }

        Event *operator->()
        {
            return dynamic_cast<Event *>(_it->get());
        }

        EventsIterator &operator++()
        {
            _it++;
            while (_it != _end && not dynamic_cast<Event *>(_it->get())) {
                _it++;
            }
            return *this;
        }

        EventsIterator operator++(int)
        {
            EventsIterator tmp = *this;

            ++(*this);
            return tmp;
        }

        friend bool operator==(EventsIterator const &a, EventsIterator const &b)
        {
            return a._it == b._it;
        };

        friend bool operator!=(EventsIterator const &a, EventsIterator const &b)
        {
            return a._it != b._it;
        };

    private:
        Iterator _it;
        Iterator _end;
    };

public:
    template <class Event> EventsIterator<Event> beginIterator()
    {
        return EventsIterator<Event>(_events.begin(), _events.end());
    }

    template <class Event> EventsIterator<Event> endIterator()
    {
        return EventsIterator<Event>(_events.end(), _events.end());
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
        _eventsToAdd.push_back(
            std::make_unique<Event>(std::forward<Params>(params)...)
        );
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

    Iterator begin() noexcept
    {
        return _events.begin();
    }

    Iterator end() noexcept
    {
        return _events.end();
    }

    [[nodiscard]] ConstIterator begin() const noexcept
    {
        return _events.begin();
    }

    [[nodiscard]] ConstIterator end() const noexcept
    {
        return _events.end();
    }

    void clear() noexcept
    {
        _events.clear();
    }

    void update() noexcept
    {
        for (auto &event : _eventsToAdd) {
            _events.push_back(std::move(event));
        }
        _eventsToAdd.clear();
    }

    template <class Event> bool hasEvent() noexcept
    {
        return this->beginIterator<Event>() != this->endIterator<Event>();
    }

private:
    std::deque<std::unique_ptr<IEvent>> _events;
    std::deque<std::unique_ptr<IEvent>> _eventsToAdd;
};

}

#endif // !R_TYPE_EVENT_HPP
