/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Common Deserializer
*/

#ifndef R_TYPE_DESERIALIZER_HPP
#define R_TYPE_DESERIALIZER_HPP

#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>

namespace engine {

class Deserializer {
public:
    explicit Deserializer(std::vector<std::byte> const &data)
        : _data(data)
    {
    }

    Deserializer(Deserializer const &) = default;
    Deserializer(Deserializer &&) = delete;
    Deserializer &operator=(Deserializer const &) = delete;
    Deserializer &operator=(Deserializer &&) = delete;

    template <typename T> void deserializeTrivial(T &value)
    {
        if (_offset + sizeof(T) > _data.size())
            throw std::runtime_error("Not enough data");
        std::memcpy(&value, _data.data() + _offset, sizeof(T));
        _offset += sizeof(T);
    }

    template <typename SizeType> void deserializePascalString(std::string &str)
    {
        SizeType size = 0;
        deserializeTrivial(size);
        if (_offset + size > _data.size())
            throw std::runtime_error("Not enough data");
        str.assign(
            reinterpret_cast<char const *>(_data.data() + _offset), size
        );
        _offset += size;
    }

    std::size_t getOffset() const
    {
        return _offset;
    }

    void skip(std::size_t size)
    {
        if (_offset + size > _data.size())
            throw std::runtime_error("Not enough data");
        _offset += size;
    }

    bool isFinished() const
    {
        return _offset == _data.size();
    }

private:
    std::vector<std::byte> const &_data;
    std::size_t _offset = 0;
};

}

#endif /* !R_TYPE_DESERIALIZER_HPP */
