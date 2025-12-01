#pragma once

namespace dudis {

enum class ComponentType { Physics };

class Component {
public:
  // ComponentType type;
  virtual ~Component() = default;
};

} // namespace dudis