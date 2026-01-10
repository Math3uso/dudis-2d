#include "dudis2d/graphics/frameQueue/frameQueue.h"
#include "dudis2d/graphics/renderQueue/renderQueue.h"
#include <algorithm>
#include <iostream>

using namespace std;
using namespace dudis;

void FrameQueue::init() {
  _queues[0] = new RenderQueue();
  _queues[1] = new RenderQueue();
}

FrameQueue::~FrameQueue() {
  delete _queues[0];
  delete _queues[1];
}

RenderQueue *FrameQueue::beginWrite() {
  // frame 1
  uint32_t read = _index.load(std::memory_order_relaxed); // 0

  int write = 1 - read; // 1 - 0 = 0

  return _queues[write]; // return _queues[0]
}

const RenderQueue *FrameQueue::beginRead() const {
  uint32_t index = _index.load(std::memory_order_acquire);
  return _queues[index];
}

void FrameQueue::endWrite() {
  uint32_t currentRead = _index.load(std::memory_order_relaxed); // 0

  uint32_t newRead = 1 - currentRead;

  _index.store(newRead, std::memory_order_release);
}