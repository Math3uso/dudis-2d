#pragma once

#define DD_NAMESPACE                                                           \
  using namespace dudis;                                                       \
  using namespace std;

#define DD_RENDER
#ifdef DD_RENDER
#include "dudis2d/graphics.h"
#endif

#define DD_CORE
#ifdef DD_CORE
#include "dudis2d/dudis2d.h"
#endif

#define DD_PHYSICS
#ifdef DD_PHYSICS
#include "dudis2d/physics.h"
#endif