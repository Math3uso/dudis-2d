#pragma once

#include <box2d/box2d.h>

namespace dudis {
class ContactListner : public b2ContactListener {
public:
  void BeginContact(b2Contact *contact) override;
  void EndContact(b2Contact *contact) override;
};
} // namespace dudis