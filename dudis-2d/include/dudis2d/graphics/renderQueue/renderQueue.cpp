#include "dudis2d/graphics/renderQueue/renderQueue.h"
#include "dudis2d/core/log/log.h"

using namespace std;
using namespace dudis;

void RenderQueue::collectRenderCommands(const DrawCommand &cmd) {
  _renderList.push_back(cmd);
  this->_checkRelocation();
}

void RenderQueue::collectRenderCommands(
    const vector<DrawCommand> &&renderList) {
  _renderList.insert(_renderList.end(), renderList.begin(), renderList.end());
  this->_checkRelocation();
}

void RenderQueue::_checkRelocation() {
  size_t renderChunck = _renderList.size() * sizeof(DrawCommand);
  _current = renderChunck > _current ? renderChunck : _current;

  if (_current >= _size) {
    Log::Info("[INFO] realocando _renderList [RenderQueue]");
    _size = _size * 2;
    _renderList.reserve(_size);
  }
}

void RenderQueue::clear() { _renderList.clear(); }