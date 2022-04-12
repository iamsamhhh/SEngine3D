#include "System.hpp"
#include <string>

namespace SEngine{
class GetEntitySystem : public System{
public:
    Entity Get(std::string name);
    bool Exist(Entity id);
    bool Exist(std::string name);
};
}