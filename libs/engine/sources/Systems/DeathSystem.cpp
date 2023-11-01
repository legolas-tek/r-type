/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** DeathSystem
*/

#include "Systems/DeathSystem.hpp"
#include "Events/Death.hpp"

System::DeathSystem::DeathSystem(
    SparseArray<Component::Health> &healths,
    SparseArray<Component::Life> &lifes, engine::Registry &reg
)
    : _healths(healths)
    , _reg(reg)
    , _lifes(lifes)
{
}

bool isEntityInDeathEvent(
    engine::Entity entity, std::deque<std::unique_ptr<Event::IEvent>> &events
)
{
    return std::ranges::any_of(events, [entity](auto &event) {
        auto death = dynamic_cast<Event::Death *>(event.get());

        if (not death)
            return false;

        return death->entity == entity;
    });
}

void System::DeathSystem::operator()()
{
    for (auto it = _healths.begin(); it != _healths.end(); it++) {
        if (isEntityInDeathEvent(it.get_entity(), _reg.events)) {
            _reg.erase_entity(it.get_entity());
            continue;
        }
        if ((*it)->health <= 0 && _lifes[it.get_entity()]
            && _lifes[it.get_entity()]->lifes <= 0) {
            _reg.events.push_back(std::make_unique<Event::Death>(it.get_entity()
            ));
        }
    }
}
