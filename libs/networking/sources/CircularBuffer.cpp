/*
** EPITECH PROJECT, 2023
** zappy gui
** File description:
** CircularBuffer
*/

#include "CircularBuffer.hpp"

rtype::CircularBuffer::CircularBuffer(std::size_t size)
: _buffer(size), _reader(0), _writer(0)
{
    std::memset(_buffer.data(), 0, size);
}

void rtype::CircularBuffer::updateWriteIndexAfterWrite(std::size_t writedLength)
{
    _writer = (_writer + writedLength) % _buffer.size();
}

std::vector<char> rtype::CircularBuffer::readUntil(char delim)
{
    bool is_circular = _writer < _reader;
    std::vector<char>::iterator begin = _buffer.begin() + _reader;
    std::vector<char>::iterator end;

    if (is_circular)
        end = _buffer.end();
    else
        end = std::find(_buffer.begin() + _reader, _buffer.begin() + _writer, delim);

    std::vector<char> res(begin, end);

    if (is_circular)
        res.insert(res.end(), _buffer.begin(), std::find(_buffer.begin(), _buffer.begin() + _writer, delim));

    _reader = (_reader + res.size()) % _buffer.size() + 1;
    return res;
}

std::vector<char> rtype::CircularBuffer::readAvailableData()
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


char *rtype::CircularBuffer::getWritePtr()
{
    return _buffer.data() + _writer;
}

std::size_t rtype::CircularBuffer::getAvailableCapacityUntilWrappingAround() const
{
    return _buffer.size() - _writer;
}


bool rtype::CircularBuffer::isAvailableData(char delim) const
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
        it = std::find(_buffer.begin() + _reader, _buffer.begin() + _writer, delim);

    if (it == _buffer.begin() + _writer)
        return false;
    return true;
}

bool rtype::CircularBuffer::isAvailableData() const
{
    return _writer != _reader;
}

char *rtype::CircularBuffer::data()
{
    return _buffer.data();
}
