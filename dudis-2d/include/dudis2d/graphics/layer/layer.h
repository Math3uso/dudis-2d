#include <vector>

#include "dudis2d/core/entity/entity.h"
#include "dudis2d/graphics/renderable.h"

namespace dudis {
class Layer : public Entity {
private:
public:
  Layer(Size nSize = {0, 0}) { size = nSize; };
};
} // namespace dudis