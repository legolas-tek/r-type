/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Sparse_array
*/

#ifndef SPARSE_ARRAY_HPP_
#define SPARSE_ARRAY_HPP_

#include <vector>
#include <optional>
#include <iostream>

template <typename Component> // You can also mirror the definition of std::vector ,that takes an additional allocator.

class sparse_array
{
public:
    using value_type = std::optional<Component>; // optional component type
    using reference_type = value_type &;
    using const_reference_type = value_type const &;
    using container_t = std::vector<value_type>; // optionally add your allocator template here.
    using size_type = typename container_t::size_type;
    using const_iterator = typename container_t ::const_iterator;
    using pointer_type = value_type *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

public:
    struct Components_iterator
    {
    public:
        Components_iterator(pointer_type ptr, pointer_type end_ptr = 0) : m_ptr(ptr), _end_ptr(end_ptr) {}

        reference_type operator*() const { return *m_ptr; }

        pointer_type operator->() { return m_ptr; }

        // Prefix increment
        Components_iterator &operator++()
        {
            m_ptr++;
            _iterations++;
            while (m_ptr != _end_ptr && !m_ptr->has_value()) {
                m_ptr++;
                _iterations++;
            }
            return *this;
        }

        size_t get_entity()
        {
            return _iterations;
        }

        // Postfix increment
        Components_iterator operator++(int)
        {
            Components_iterator tmp = *this;

            ++(*this);
            ++_iterations;
            while (m_ptr != _end_ptr && !this->m_ptr->has_value()) {
                ++(*this);
                ++_iterations;
            }
            return tmp;
        }

        friend bool operator==(const Components_iterator &a, const Components_iterator &b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!=(const Components_iterator &a, const Components_iterator &b) { return a.m_ptr != b.m_ptr; };

    private:
        pointer_type m_ptr;
        pointer_type _end_ptr;
        size_t _iterations = 0;
    };

    using iterator = sparse_array<Component>::Components_iterator;

    sparse_array() = default;                         // You can add more constructors .
    sparse_array(sparse_array const &) = default;     // copy constructor
    sparse_array(sparse_array &&) noexcept = default; // move constructor
    ~sparse_array() = default;

    sparse_array &operator=(sparse_array const &other)
    {
        this = other;
        return *this;
    }

    sparse_array &operator=(sparse_array &&other) noexcept
    {
        this = other;
        return *this;
    }

    reference_type operator[](size_t idx)
    {
        if (idx >= _data.size())
            _data.resize(idx + 1);
        return _data[idx];
    }

    const_reference_type operator[](size_t idx) const
    {
        if (idx >= _data.size())
            throw std::out_of_range("Position out of range.");
        return _data[idx];
    }

    iterator begin()
    {
        iterator it(&_data[0], &_data[_data.size()]);

        if (it != end() && !it->has_value())
            it++;
        return it;
    }

    const_iterator begin() const
    {
        return _data.begin();
    }

    const_iterator cbegin() const
    {
        return _data.cbegin();
    }

    iterator end()
    {
        return iterator(&_data[_data.size()]);
    }

    const_iterator end() const
    {
        return _data.end();
    }

    const_iterator cend() const
    {
        return _data.cend();
    }

    size_type size() const
    {
        return _data.size();
    }

    reference_type insert_at(size_type pos, Component const &comp)
    {
        if (pos >= _data.size())
            _data.resize(pos + 1);
        if (_data.at(pos))
            _data.erase(_data.begin() + pos);
        _data.insert(_data.begin() + pos, comp);
        return *(_data.begin() + pos);
    }

    reference_type insert_at(size_type pos, Component &&comp)
    {
        if (pos >= _data.size())
            _data.resize(pos + 1);
        if (_data.at(pos))
            _data.erase(_data.begin() + pos);
        _data.insert(_data.begin() + pos, comp);
        return *(_data.begin() + pos);
    }

    template <class... Params>

    reference_type emplace_at(size_type pos, Params &&...args)
    {
        if (pos >= _data.size())
            _data.resize(pos + 1);
        if (_data[pos])
            _data.erase(_data.begin() + pos);
        return *_data.emplace(_data.begin() + pos, std::forward<Params>(args)...);
    }

    void erase(size_type pos)
    {
        if (pos >= _data.size())
            throw std::out_of_range("Position out of range.");
        _data.erase(_data.begin() + pos);
    }

    size_type get_index(value_type const &value_searched) const
    {
        size_type pos = 0;

        for (auto it = _data.begin(); it != _data.end(); it++)
        {
            if (*it == value_searched)
                return pos;
            pos++;
        }
        return -1;
    }

private:
    container_t _data;
};

#endif /* !SPARSE_ARRAY_HPP_ */
