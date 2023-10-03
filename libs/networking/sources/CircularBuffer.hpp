/*
** EPIcharECH PROJECT, 2023
** zappy gui
** File description:
** CircularBuffer
*/

#ifndef CIRCULARBUFFER_HPP_
    #define CIRCULARBUFFER_HPP_

    #include <vector>
    #include <atomic>
    #include <algorithm>
    #include <cstring>
    #include <iostream>

namespace rtype {

class CircularBuffer
{

public:
    CircularBuffer(std::size_t size);

    void updateWriteIndexAfterWrite(std::size_t writtenLength);

    std::vector<char> readUntil(char delim);
    std::vector<char> readAvailableData();


    char *getWritePtr();
    std::size_t getAvailableCapacityUntilWrappingAround() const;


    bool isAvailableData(char delim) const;
    bool isAvailableData() const;

    char *data();

private:
    std::vector<char> _buffer;

    std::atomic_size_t _reader;

    std::atomic_size_t _writer;
};

}

#endif /* CIRCULARBUFFER_HPP_ */
