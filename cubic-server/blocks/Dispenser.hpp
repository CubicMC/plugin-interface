#include <cstdint>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace Blocks {
typedef int32_t BlockId;

namespace Dispenser {
namespace Properties {
enum class Facing {
    NORTH,
    EAST,
    SOUTH,
    WEST,
    UP,
    DOWN
};
enum class Triggered {
    TRUE,
    FALSE
};
}
BlockId toProtocol(Properties::Facing facing, Properties::Triggered triggered);
}

}
