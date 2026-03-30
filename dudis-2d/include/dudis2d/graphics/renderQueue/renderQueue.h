#pragma once

#include "dudis2d/graphics/drawCommand/drawCommand.h"
#include <vector>

namespace dudis
{
  class RenderQueue
  {
  private:
    std::vector<DrawCommand> _renderList;
    uint32_t _size = 500;
    uint32_t _current = 0;
    void _checkRelocation();

  public:
    RenderQueue() { _renderList.reserve(_size); };

    void addCommand(const DrawCommand &cmd);
    void addCommand(const std::vector<DrawCommand> &&renderList);
    std::vector<DrawCommand> &getCommands() { return _renderList; }
    const std::vector<DrawCommand> &getCommands() const { return _renderList; }
    void clear();

    static std::unique_ptr<RenderQueue> create()
    {
      return std::make_unique<RenderQueue>();
    }
  };
} // namespace dudis
