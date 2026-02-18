#include "dudis2d/core/math/react.h"

using namespace dudis;

bool DDRect::intersects(const DDRect &other)
{
    return right() > other.left() &&
           left() < other.right() &&
           top() > other.bottom() &&
           bottom() < other.top();
}