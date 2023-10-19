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
    explicit Deserializer(std::vector<std::byte> &&data)
        : _data(std::move(data))
    {
    }

    Deserializer(Deserializer const &) = delete;
    Deserializer(Deserializer &&) = default;
    Deserializer &operator=(Deserializer const &) = delete;
    Deserializer &operator=(Deserializer &&) = default;

    template <typename T> void deserializeTrivial(T const &value)
    {
        if (_offset + sizeof(T) > _data.size())
            throw std::runtime_error("Not enough data");
        std::memcpy(&value, _data.data() + _offset, sizeof(T));
        _offset += sizeof(T);
    }

    template <typename SizeType>
    void deserializePascalString(std::string const &str)
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

private:
    std::vector<std::byte> _data;
    std::size_t _offset = 0;
};

}

#endif /* !R_TYPE_DESERIALIZER_HPP */
