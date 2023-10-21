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

#include "Systems/Editable.hpp"
#include "Systems/Focusable.hpp"
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
    if (_serverLobby)
        _game._serverClients = std::move(_serverLobby->get().getClients());
}

void RTypeLobby::registerAdditionalSystems(engine::Registry &reg)
{
}

void RTypeLobby::initAssets(engine::Registry &reg)
{
}

static engine::Entity createField(
    engine::Registry &reg, std::string &&label, std::string &&value, int x,
    int y
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
createButton(engine::Registry &reg, std::string &&label, int x, int y)
{
    using namespace Component;
    engine::Entity button(reg.get_new_entity());

    reg.get_components<Position>().emplace_at(button, Position(x, y));
    reg.get_components<Text>().emplace_at(
        button, Text(std::move(label), FONT, 40, 1)
    );
    reg.get_components<Focusable>().emplace_at(button, Focusable());
    reg.get_components<HitBox>().emplace_at(button, HitBox(100, 50));
    return button;
}

void RTypeLobby::initScene(engine::Registry &reg)
{
    using namespace Component;
    engine::Entity title(reg.get_new_entity());

    reg.get_components<Position>().emplace_at(title, Position(0, 0));
    reg.get_components<Text>().insert_at(title, Text("R-Type", FONT, 50, 10));

    engine::Entity address = createField(reg, "Address", "127.0.0.1", 100, 100);
    engine::Entity port = createField(reg, "Port", "4242", 100, 200);
    engine::Entity name = createField(reg, "Name", "Player", 100, 300);
    engine::Entity join = createButton(reg, "Join", 500, 200);
}
