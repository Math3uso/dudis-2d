#include "dudis2d/core/debug/dd-debug.h"
#include "dudis2d/dudis2d.h"
#include "dudis2d/scenes/scene/scene.h"

using namespace std;
using namespace dudis;

unordered_map<Scene *, size_t> DD_DebugDetails::_s_scenes;
unordered_map<void *, size_t> DD_DebugDetails::_s_models;

void DD_DebugDetails::registerScene(Scene *data) {
  if (!data)
    return;

  _s_scenes[data] = sizeof(*data);
}

void DD_DebugDetails::_registerModel(DDModel *data) {}

size_t DD_DebugDetails::getSceneBytes() {
  size_t bytes = 0;

  for (const auto &scene : _s_scenes) {
    bytes += scene.second;
  }

  return bytes;
}

// void dudis::DDPrintMemoryUsage() {
//   // somente das scenes
//   size_t bytes = DD_DebugDetails::getSceneBytes();

//   Log::Info("================ Debug ================");
//   Log::Alert("Bytes: " + to_string(bytes));
//   Log::Info("================ Debug ================");
// }

// {
//   // somente das scenes
//   size_t bytes = DD_DebugDetails::getSceneBytes();

//   dudis::Log::Info("================ Debug ================");
//   dudis::Log::Alert("Bytes: " + std::to_string(bytes));
//   dudis::Log::Info("================ Debug ================");
// }