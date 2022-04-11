#include "System.hpp"
#include <string>
namespace SEngine{
class GetEntitySystem : public System{
public:
    Entity Get(std::string name);
};
}