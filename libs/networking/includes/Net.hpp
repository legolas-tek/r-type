/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Main header of the net namespace
*/

#ifndef NET_HPP_
#define NET_HPP_

#include <vector>

namespace net {

constexpr struct ServerNetManager {
} server_netmanager;
constexpr struct ClientNetManager {
} client_netmanager;

using Buffer = std::vector<std::byte>;

namespace manager {

class Udp;

struct Client;
}

}

#endif /* NET_HPP_ */
