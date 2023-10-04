/*
** EPITECH PROJECT, 2023
** rtype tests
** File description:
** diffing
*/

#include <gtest/gtest.h>
#include <vector>

#include "Snapshot.hpp"

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
                                           .data = { 0x03, 0x04, 0x05 } });
    current.data.push_back(ComponentData { .entity = Entity(0x02),
                                           .componentId = 0x02,
                                           .data = { 0x04, 0x05, 0x06 } });
    std::vector<char> diff = diffSnapshots(dummy, current);
    std::vector<char> expected = {
        // First Component Data
        0x01, 0x00, 0x00, 0x00, // entity number
        0x02, // component id
        0x01, // added
        0x03, 0x04, 0x05, // data
        // Second Component Data
        0x02, 0x00, 0x00, 0x00, // entity number
        0x02, // component id
        0x01, // added
        0x04, 0x05, 0x06, // data
    };

    ASSERT_EQ(diff, expected);
}

TEST(Diffing, RemoveOnly)
{
    Snapshot one;
    Snapshot empty;

    one.data.push_back(ComponentData { .entity = Entity(0x01),
                                           .componentId = 0x02,
                                           .data = { 0x03, 0x04, 0x05 } });
    std::vector<char> diff = diffSnapshots(one, empty);
    std::vector<char> expected = {
        // Component Data
        0x01, 0x00, 0x00, 0x00, // entity number
        0x02, // component id
        0x00, // removed
    };

    ASSERT_EQ(diff, expected);
}
