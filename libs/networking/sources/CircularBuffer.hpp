/*
** EPIcharECH PROJECT, 2023
** zappy gui
** File description:
** CircularBuffer
*/

#ifndef CIRCULARBUFFER_HPP_
#define CIRCULARBUFFER_HPP_

#include <atomic>
#include <exception>
#include <vector>

namespace net {

class CircularBuffer {

public:
    explicit CircularBuffer(std::size_t size);

    char *getWritePtr();
    std::size_t getAvailableCapacityUntilWrappingAround() const;
    void updateWriteIndexAfterWrite(std::size_t writtenLength);

    bool canRead(size_t size) const noexcept;
    void readInto(void *dest, size_t size);
    std::size_t getReadIndex() const;
    void resetReadIndex(std::size_t index);

public:
    class CannotReadException : public std::exception {
    public:
        [[nodiscard]] char const *what() const noexcept override;
    };

private:
    std::vector<char> _buffer;

    std::atomic_size_t _reader;
    std::atomic_size_t _writer;
};

}

#endif /* CIRCULARBUFFER_HPP_ */
