/*
** EPITECH PROJECT, 2023
** R-Type Networking
** File description:
** Circular Buffer
*/

#include "CircularBuffer.hpp"
#include <ciso646>

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

std::vector<char> net::CircularBuffer::readUntil(char delim)
{
    bool is_circular = _writer < _reader;
    std::vector<char>::iterator begin = _buffer.begin() + _reader;
    std::vector<char>::iterator end;

    if (is_circular)
        end = _buffer.end();
    else
        end = std::find(
            _buffer.begin() + _reader, _buffer.begin() + _writer, delim
        );

    std::vector<char> res(begin, end);

    if (is_circular)
        res.insert(
            res.end(), _buffer.begin(),
            std::find(_buffer.begin(), _buffer.begin() + _writer, delim)
        );

    _reader = (_reader + res.size()) % _buffer.size() + 1;
    return res;
}

std::vector<char> net::CircularBuffer::readAvailableData()
{
    bool is_circular = _writer < _reader;
    std::vector<char>::iterator begin = _buffer.begin() + _reader;
    std::vector<char>::iterator end = _buffer.begin() + _writer;

    if (not isAvailableData())
        return std::vector<char>();

    if (is_circular)
        end = _buffer.end();

    std::vector<char> res(begin, end);

    if (is_circular)
        res.insert(res.end(), _buffer.begin(), _buffer.begin() + _writer);

    _reader = _writer.load();
    return res;
}

char *net::CircularBuffer::getWritePtr()
{
    return _buffer.data() + _writer;
}

std::size_t net::CircularBuffer::getAvailableCapacityUntilWrappingAround() const
{
    return _buffer.size() - _writer;
}

bool net::CircularBuffer::isAvailableData(char delim) const
{
    std::vector<char>::const_iterator it;

    if (_writer == _reader)

        return false;
    if (_writer < _reader) {
        it = std::find(_buffer.begin() + _reader, _buffer.end(), delim);

        if (it != _buffer.end())
            return true;

        it = std::find(_buffer.begin(), _buffer.begin() + _writer, delim);
    } else
        it = std::find(
            _buffer.begin() + _reader, _buffer.begin() + _writer, delim
        );

    if (it == _buffer.begin() + _writer)
        return false;
    return true;
}

bool net::CircularBuffer::isAvailableData() const
{
    return _writer != _reader;
}

char *net::CircularBuffer::data()
{
    return _buffer.data();
}

bool net::CircularBuffer::canRead(size_t size) const
{
    if (_writer < _reader)
        return _buffer.size() - _reader + _writer >= size;
    return _writer - _reader >= size;
}

void net::CircularBuffer::readInto(void *dest, size_t size)
{
    if (not canRead(size))
        throw std::runtime_error("Not enough data to read");
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
