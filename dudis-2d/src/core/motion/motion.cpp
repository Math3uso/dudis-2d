#include <cassert>
#include <cmath>
#include "dudis2d/core/motion/motion.h"
#include "dudis2d/core/entity/entity.h"
#include "dudis2d/globals/time.h"
#include "glm/glm.hpp"

using namespace std;
using namespace dudis;

void Motion::startWithTarget(Entity *target)
{
    // if (!target)
    // {

    // }
    assert(target != nullptr && "[ERROR] o target n pode ser nulo");
    _target = target;
    _from = _target->getPos();
    _start = true;
    _elapsed = 0;
    return;
}

void Motion::update()
{
    if (!_start)
        return;

    _elapsed += Time::deltaTime;

    float rawT = fminf(_elapsed / _duration, 1.0f);
    float easedT = _easing(rawT);

    glm::vec2 from = glm::vec2(_from.x, _from.y);
    glm::vec2 to = glm::vec2(_to.x, _to.y);

    glm::vec2 pos = glm::mix(from, to, easedT);

    Vec2 res = Vec2(pos.x, pos.y);

    _target->setPos(res);

    if (rawT >= 1.0f)
    {
        _start = false;
        _isDone = true;
        if (_onComplete)
        {
            _onComplete();
        }
    }
}