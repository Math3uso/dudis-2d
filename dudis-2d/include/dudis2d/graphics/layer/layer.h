#include "dudis2d/core/entity/entity.h"
#include "dudis2d/graphics/renderable.h"
#include <vector>

namespace dudis {
class Layer : public Entity {
private:
  std::vector<std::shared_ptr<Renderable>> _children;

public:
  Layer(Size nSize = {0, 0}) { size = nSize; };
};
} // namespace dudis