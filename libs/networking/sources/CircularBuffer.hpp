/*
** EPIcharECH PROJECT, 2023
** zappy gui
** File description:
** CircularBuffer
*/

#ifndef CIRCULARBUFFER_HPP_
#define CIRCULARBUFFER_HPP_

#include <algorithm>
#include <atomic>
#include <cstring>
#include <iostream>
#include <vector>

namespace net {

class CircularBuffer {

public:
    CircularBuffer(std::size_t size);

    void updateWriteIndexAfterWrite(std::size_t writtenLength);

    std::vector<char> readUntil(char delim);
    std::vector<char> readAvailableData();

    char *getWritePtr();
    std::size_t getAvailableCapacityUntilWrappingAround() const;

    bool isAvailableData(char delim) const;
    bool isAvailableData() const;

    bool canRead(size_t size) const;
    void readInto(void *dest, size_t size);
    std::size_t getReadIndex() const;
    void resetReadIndex(std::size_t index);

    char *data();

public:
    class CannotReadException : public std::exception {
    public:
        char const *what() const noexcept override;
    };

private:
    std::vector<char> _buffer;

    std::atomic_size_t _reader;
    std::atomic_size_t _writer;
};

}

#endif /* CIRCULARBUFFER_HPP_ */
