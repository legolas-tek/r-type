/*
** EPITECH PROJECT, 2023
** R-Type Networking
** File description:
** Circular Buffer
*/

#include "CircularBuffer.hpp"

#include <cstring>

net::CircularBuffer::CircularBuffer(std::size_t size)
    : _buffer(size)
    , _reader(0)
    , _writer(0)
{
    std::memset(_buffer.data(), 0, size);
}

void net::CircularBuffer::updateWriteIndexAfterWrite(std::size_t writedLength)
{
    _writer = (_writer + writedLength) % _buffer.size();
}

char *net::CircularBuffer::getWritePtr()
{
    return _buffer.data() + _writer;
}

std::size_t net::CircularBuffer::getAvailableCapacityUntilWrappingAround() const
{
    return _buffer.size() - _writer;
}

bool net::CircularBuffer::canRead(size_t size) const noexcept
{
    if (_writer < _reader)
        return _buffer.size() - _reader + _writer >= size;
    return _writer - _reader >= size;
}

void net::CircularBuffer::readInto(void *dest, size_t size)
{
    if (not canRead(size))
        throw CannotReadException();
    // Do it in two steps if we need to wrap around
    if (_reader + size > _buffer.size()) {
        std::size_t first_part = _buffer.size() - _reader;
        std::size_t second_part = size - first_part;

        std::memcpy(dest, _buffer.data() + _reader, first_part);
        std::memcpy(
            static_cast<char *>(dest) + first_part, _buffer.data(), second_part
        );
    } else {
        std::memcpy(dest, _buffer.data() + _reader, size);
    }
    _reader = (_reader + size) % _buffer.size();
}

std::size_t net::CircularBuffer::getReadIndex() const
{
    return _reader;
}
void net::CircularBuffer::resetReadIndex(std::size_t index)
{
    _reader = index;
}

char const *net::CircularBuffer::CannotReadException::what() const noexcept
{
    return "Cannot read from buffer";
}
