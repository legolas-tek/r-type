
#include <cstddef>

/*! \class Entity
 *  \brief Brief class description
 *
 *  Detailed description
 */
class Entity
{
public:
    Entity(std::size_t id)
        : _id(id) {}
    virtual ~Entity() = default;

private:
    std::size_t _id;
};
