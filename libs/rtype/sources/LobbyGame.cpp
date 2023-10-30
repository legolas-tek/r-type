/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game
*/

#include "Entity.hpp"
#include "Game.hpp"

#include "Components/Animation.hpp"
#include "Components/Drawable.hpp"
#include "Components/Focusable.hpp"
#include "Components/HitBox.hpp"
#include "Components/Position.hpp"
#include "Components/Text.hpp"

#include "Systems/AnimationSystem.hpp"
#include "Systems/Editable.hpp"
#include "Systems/Focusable.hpp"
#include "Systems/JoinButton.hpp"
#include "Systems/LobbyClientImpl.hpp"
#include "Systems/StartGameButton.hpp"
#include "Systems/Text.hpp"

#include "Rendering.hpp"

static constexpr char const *FONT = "./assets/fonts/Over_There.ttf";

void RTypeLobby::registerAllComponents(engine::Registry &reg)
{
    reg.register_component<Component::Position>();
    reg.register_component<Component::Drawable>();
    reg.register_component<Component::Animation>();
    reg.register_component<Component::Text>();
    reg.register_component<Component::Focusable>();
    reg.register_component<Component::HitBox>();
    reg.register_component<Component::Editable>();
}

void RTypeLobby::registerAdditionalClientSystems(engine::Registry &reg)
{
    reg.add_system<System::AnimationSystem>(reg);
    reg.add_system<rendering::system::Rendering>(reg);
    reg.add_system<rendering::system::Focusable>(
        reg.get_components<Component::Focusable>(),
        reg.get_components<Component::HitBox>(),
        reg.get_components<Component::Position>()
    );
    reg.add_system<rendering::system::Editable>(
        reg.get_components<Component::Editable>(),
        reg.get_components<Component::Focusable>(),
        reg.get_components<Component::Text>()
    );
    reg.add_system<System::JoinButton>(
        *this, reg, _joinButton, _addressInput, _portInput, _nameInput
    );
}

void RTypeLobby::registerAdditionalServerSystems(engine::Registry &reg)
{
    _serverLobby = dynamic_cast<net::lobby::Lobby &>(
        reg.add_system<net::lobby::Lobby>(4242, 4)
    );
}

RTypeLobby::RTypeLobby(RTypeGame &game)
    : _game(game)
{
}

RTypeLobby::~RTypeLobby()
{
    _game._playerHash = _playerHash;
    _game._playerNumber = _playerNumber;
    _game._address = std::move(_address);
    _game._port = _port;
    if (_serverLobby)
        _game._serverClients = std::move(_serverLobby->get().getClients());
}

void RTypeLobby::registerAdditionalSystems(engine::Registry &reg)
{
}

void RTypeLobby::initAssets(engine::Registry &reg)
{
    reg._assets_paths.emplace_back("./assets/images/space_ships.png");
}

static engine::Entity createField(
    engine::Registry &reg, std::string &&label, std::string &&value, float x,
    float y
)
{
    using namespace Component;
    engine::Entity labelEntity(reg.get_new_entity());
    engine::Entity valueEntity(reg.get_new_entity());

    reg.get_components<Position>().emplace_at(labelEntity, Position(x, y));
    reg.get_components<Text>().emplace_at(
        labelEntity, Text(std::move(label), FONT, 20, 1)
    );
    reg.get_components<Position>().emplace_at(
        valueEntity, Position(x + 10, y + 30)
    );
    reg.get_components<Text>().emplace_at(
        valueEntity, Text(std::move(value), FONT, 20, 1)
    );
    reg.get_components<Focusable>().emplace_at(valueEntity, Focusable());
    reg.get_components<Editable>().emplace_at(valueEntity, Editable());
    reg.get_components<HitBox>().emplace_at(valueEntity, HitBox(300, 50));
    return valueEntity;
}

static engine::Entity
createButton(engine::Registry &reg, std::string &&label, float x, float y)
{
    using namespace Component;
    engine::Entity button(reg.get_new_entity());

    reg.get_components<Position>().emplace_at(button, Position(x, y));
    reg.get_components<Text>().emplace_at(
        button, Text(std::move(label), FONT, 40, 1)
    );
    reg.get_components<Focusable>().emplace_at(button, Focusable());
    reg.get_components<HitBox>().emplace_at(button, HitBox(200, 100));
    return button;
}

void RTypeLobby::initScene(engine::Registry &reg)
{
    using namespace Component;
    engine::Entity title(reg.get_new_entity());

    reg.get_components<Position>().emplace_at(title, Position(125, 30));
    reg.get_components<Text>().insert_at(title, Text("R-Type", FONT, 50, 10));

    _addressInput = createField(reg, "Address", "127.0.0.1", 100, 100);
    _portInput = createField(reg, "Port", "4242", 100, 200);
    _nameInput = createField(reg, "Name", "Player", 100, 300);
    _joinButton = createButton(reg, "Join", 500, 200);
}

void RTypeLobby::onJoinSuccess(
    std::uint8_t playerNumber, std::uint64_t playerHash, std::string address,
    std::size_t port
)
{
    _playerNumber = playerNumber;
    _playerHash = playerHash;
    _address = std::move(address);
    _port = port;
}

void RTypeLobby::initLobbyScene(
    engine::Registry &reg, System::LobbyClientImpl &client
)
{
    reg.reset_scene();
    engine::Entity button = createButton(reg, "Start Game", 400, 300);
    reg.add_system<System::StartGameButton>(
        client, reg.get_components<Component::Focusable>()[button].value()
    );
}
