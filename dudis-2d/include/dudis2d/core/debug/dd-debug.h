#pragma once

#include "dudis2d/core/log/log.h"
#include <unordered_map>

// #ifdef DD_DEBUG
// #define DD_DEBUG(x) x
// #else
// #define DD_DEBUG(x)
// #endif

#define DD_DEBUG

#ifndef DD_DEBUG_MODE
#define DD_DEBUG_MODE 1
#endif

class Scene;

namespace dudis {
class DDModel;

class DDConfig {
public:
  static constexpr bool debugMode = DD_DEBUG_MODE;
};

class DD_DebugDetails {
private:
  static std::unordered_map<Scene *, size_t> _s_scenes;
  static std::unordered_map<void *, size_t> _s_models;

  // static void registerScene(Scene *data);
  static void _registerModel(DDModel *data);

public:
  static void registerScene(Scene *data);
  static size_t getSceneBytes();
};
// namespace dd_debug

inline void DDPrintMemoryUsage() {

  if constexpr (DDConfig::debugMode) {
    // somente das scenes
    size_t bytes = DD_DebugDetails::getSceneBytes();

    Log::Info("================ Debug ================");
    Log::Alert("Bytes: " + std::to_string(bytes));
    Log::Info("================ Debug ================");
  }
};

} // namespace dudis