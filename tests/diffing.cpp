/*
** EPITECH PROJECT, 2023
** rtype tests
** File description:
** diffing
*/

#include <gtest/gtest.h>
#include <vector>

#include "Snapshot.hpp"

using namespace engine;

std::byte operator ""_b(unsigned long long value)
{
    return std::byte(value);
}

TEST(Diffing, Empty)
{
    Snapshot dummy;
    Snapshot empty;

    auto diff = diffSnapshots(dummy, empty);
    ASSERT_EQ(diff.size(), 0);
}

TEST(Diffing, Initial)
{
    Snapshot dummy;
    Snapshot current;

    current.tick = 3;
    current.data.push_back(ComponentData { .entity = Entity(0x01),
                                           .componentId = 0x02,
                                           .data = { 0x03_b, 0x04_b, 0x05_b } });
    current.data.push_back(ComponentData { .entity = Entity(0x02),
                                           .componentId = 0x02,
                                           .data = { 0x04_b, 0x05_b, 0x06_b } });
    std::vector<std::byte> diff = diffSnapshots(dummy, current);
    std::vector<std::byte> expected = {
        // First Component Data
        0x01_b, 0x00_b, 0x00_b, 0x00_b, // entity number
        0x02_b, // component id
        0x01_b, // added
        0x03_b, 0x04_b, 0x05_b, // data
        // Second Component Data
        0x02_b, 0x00_b, 0x00_b, 0x00_b, // entity number
        0x02_b, // component id
        0x01_b, // added
        0x04_b, 0x05_b, 0x06_b, // data
    };

    ASSERT_EQ(diff, expected);
}

TEST(Diffing, RemoveOnly)
{
    Snapshot one;
    Snapshot empty;

    one.data.push_back(ComponentData { .entity = Entity(0x01),
                                           .componentId = 0x02,
                                           .data = { 0x03_b, 0x04_b, 0x05_b } });
    std::vector<std::byte> diff = diffSnapshots(one, empty);
    std::vector<std::byte> expected = {
        // Component Data
        0x01_b, 0x00_b, 0x00_b, 0x00_b, // entity number
        0x02_b, // component id
        0x00_b, // removed
    };

    ASSERT_EQ(diff, expected);
}

TEST(Diffing, SingleUpdate)
{
    Snapshot previous;
    Snapshot current;

    previous.data.push_back(ComponentData { .entity = Entity(0x01),
                                           .componentId = 0x02,
                                           .data = { 0x05_b, 0x04_b, 0x05_b } });
    current.data.push_back(ComponentData { .entity = Entity(0x01),
                                           .componentId = 0x02,
                                           .data = { 0x03_b, 0x04_b, 0x05_b } });
    std::vector<std::byte> diff = diffSnapshots(previous, current);
    std::vector<std::byte> expected = {
        // First Component Data
        0x01_b, 0x00_b, 0x00_b, 0x00_b, // entity number
        0x02_b, // component id
        0x01_b, // updated
        0x03_b, 0x04_b, 0x05_b, // data
    };

    ASSERT_EQ(diff, expected);
}


TEST(Diffing, RemoveAndAdd)
{
    Snapshot previous;
    Snapshot current;

    previous.data.push_back(ComponentData { .entity = Entity(0x01),
                                           .componentId = 0x02,
                                           .data = { 0x05_b } });
    current.data.push_back(ComponentData { .entity = Entity(0x01),
                                           .componentId = 0x03,
                                           .data = { 0x03_b, 0x04_b, 0x05_b } });
    std::vector<std::byte> diff = diffSnapshots(previous, current);
    std::vector<std::byte> expected = {
        // Second Component Data
        0x01_b, 0x00_b, 0x00_b, 0x00_b, // entity number
        0x03_b, // component id
        0x01_b, // added
        0x03_b, 0x04_b, 0x05_b, // data
        // First Component Data
        0x01_b, 0x00_b, 0x00_b, 0x00_b, // entity number
        0x02_b, // component id
        0x00_b, // removed
    };

    ASSERT_EQ(diff, expected);
}
