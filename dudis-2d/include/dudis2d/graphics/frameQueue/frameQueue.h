#pragma once

#include <atomic>

namespace dudis
{

#define DD_INDEX_READ 1
#define DD_INDEX_WRITE 1

  class RenderQueue;

  class FrameQueue
  {
  private:
    std::atomic<uint32_t> _index = 0;
    uint32_t _writeIndex = 1;
    RenderQueue *_queues[2];

  public:
    FrameQueue() = default;
    ~FrameQueue();
    void init();
    RenderQueue *beginWrite();
    void endWrite();

    const RenderQueue *beginRead() const;
  };
}; // namespace dudis