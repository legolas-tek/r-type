/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Common Serializer
*/

#ifndef R_TYPE_SERIALIZER_HPP
#define R_TYPE_SERIALIZER_HPP

#include <cstddef>
#include <cstring>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

namespace engine {

class Serializer {
public:
    Serializer() = default;
    ~Serializer() = default;

    Serializer(Serializer const &) = delete;
    Serializer(Serializer &&) = default;
    Serializer &operator=(Serializer const &) = delete;
    Serializer &operator=(Serializer &&) = default;

    template <typename T> void serializeTrivial(T const &value)
    {
        _data.resize(_offset + sizeof(T));
        std::memcpy(_data.data() + _offset, &value, sizeof(T));
        _offset += sizeof(T);
    }

    template <typename SizeType>
    void serializePascalString(std::string const &str)
    {
        if (str.size() > std::numeric_limits<SizeType>::max())
            throw std::runtime_error("String too long");
        SizeType size = SizeType(str.size());
        serializeTrivial<SizeType>(size);
        _data.resize(_offset + str.size());
        std::memcpy(_data.data() + _offset, str.data(), str.size());
        _offset += str.size();
    }

    void insert(std::vector<std::byte> const &data)
    {
        _data.insert(_data.end(), data.begin(), data.end());
        _offset += data.size();
    }

    [[nodiscard]] std::vector<std::byte> finalize()
    {
        return std::move(_data);
    }

    [[nodiscard]] std::size_t getSize() const
    {
        return _offset;
    }

private:
    std::vector<std::byte> _data;
    std::size_t _offset = 0;
};

}

#endif /* !R_TYPE_SERIALIZER_HPP */
