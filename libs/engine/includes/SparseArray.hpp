/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Sparse_array
*/

#ifndef SPARSEARRAY_HPP_
#define SPARSEARRAY_HPP_

#include <optional>
#include <stdexcept>
#include <vector>

#include "Entity.hpp"

template <typename Component> class SparseArray {

public:
    using value_type = std::optional<Component>;
    using reference_type = value_type &;
    using const_reference_type = value_type const &;
    using container_t = std::vector<value_type>;
    using size_type = typename container_t::size_type;
    using pointer_type = value_type *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

public:
    struct components_iterator {

    public:
        explicit components_iterator(pointer_type ptr, pointer_type end_ptr = 0)
            : _m_ptr(ptr)
            , _end_ptr(end_ptr)
        {
        }

        reference_type operator*() const
        {
            return *_m_ptr;
        }
        pointer_type operator->()
        {
            return _m_ptr;
        }
        components_iterator &operator++()
        {
            _m_ptr++;
            _iterations++;
            while (_m_ptr != _end_ptr && !_m_ptr->has_value()) {
                _m_ptr++;
                _iterations++;
            }
            return *this;
        }
        components_iterator operator++(int)
        {
            components_iterator tmp = *this;

            ++(*this);
            return tmp;
        }

        engine::Entity get_entity()
        {
            return engine::Entity(_iterations);
        }

        friend bool
        operator==(components_iterator const &a, components_iterator const &b)
        {
            return a._m_ptr == b._m_ptr;
        };
        friend bool
        operator!=(components_iterator const &a, components_iterator const &b)
        {
            return a._m_ptr != b._m_ptr;
        };

    private:
        pointer_type _m_ptr;
        pointer_type _end_ptr;
        size_t _iterations = 0;
    };

public:
    using iterator = SparseArray<Component>::components_iterator;

public:
    SparseArray()
        : _data(container_t(500))
    {
    }
    SparseArray(SparseArray const &other) = default;
    SparseArray(SparseArray &&) noexcept = default;

    ~SparseArray() = default;

    SparseArray &operator=(SparseArray const &other)
    {
        this->_data = other._data;
        return *this;
    }

    SparseArray &operator=(SparseArray &&other) noexcept
    {
        this->_data = std::move(other._data);
        return *this;
    }

    reference_type operator[](size_t idx)
    {
        if (idx >= _data.size()) {
            _data.resize(idx + 1);
        }
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
        iterator it(&_data[0], &_data.data()[_data.size()]);

        if (it != end() && !it->has_value())
            it++;
        return it;
    }

    iterator end()
    {
        return iterator(&_data.data()[_data.size()]);
    }

    size_type size() const
    {
        return _data.size();
    }

    reference_type insert_at(size_type pos, Component const &comp)
    {
        _data[pos] = comp;
        return _data[pos];
    }

    reference_type insert_at(size_type pos, Component &&comp)
    {
        _data[pos] = comp;
        return _data[pos];
    }

    template <class... Params>
    reference_type emplace_at(size_type pos, Params &&...args)
    {
        if (pos >= _data.size()) {
            _data.resize(pos + 1);
        }
        if (_data[pos])
            _data[pos].reset();
        return *_data.emplace(
            _data.begin() + pos, std::forward<Params>(args)...
        );
    }

    void erase(size_type pos)
    {
        if (pos >= _data.size())
            throw std::out_of_range("Position out of range.");
        _data[pos].reset();
    }

private:
    container_t _data;
};

#endif /* !SPARSEARRAY_HPP_ */
