#pragma once

#include "dudis2d/core/utils/types.h"
#include "raylib.h"

namespace dudis {

class CameraDebugOptions {
public:
  CameraDebugOptions() = default;
  CameraDebugOptions(const CameraDebugOptions &other) = default;
  // bool drawCameraBounds = false;
  // bool drawCameraCenter = false;
  bool drawCameraTarget = false;
  bool drawCameraOffset = false;
};

class DDCamera {

private:
  Camera2D _camera = {};
  CameraDebugOptions _debugOptions;
  bool _isDebugMode = false;
  bool _normalizedInScene = true;

public:
  DDCamera();
  void setTarget(const Vec2 &pos) { _camera.offset = pos; };
  void setRotation(const float angle) { _camera.rotation = angle; };
  void setZoom(int zoom) { _camera.zoom += zoom; }
  void setOffset(const Vec2 &offset) { _camera.offset = offset; }
  const Camera2D &getCameraProps() { return _camera; }

  void traslateTarget(const Vec2 &delta) {
    _camera.target.x += delta.x;
    _camera.target.y += delta.y;
  }

  void setDebugOptions(const CameraDebugOptions &options) {
    _debugOptions = options;
    _isDebugMode = true;
  }

  void traslateOffset(const Vec2 &delta) {
    _camera.offset.x += delta.x;
    _camera.offset.y += delta.y;
  }

  bool isDebugMode() const { return _isDebugMode; }
  const CameraDebugOptions &getDebugOptions() const { return _debugOptions; }

  void drawDebugInfo() const;

  void setNormalizedInScene(bool value) { _normalizedInScene = value; }
  bool isNormalizedInScene() const { return _normalizedInScene; }

  // Camera2D &getCameraProps() { return _camera; }
};
} // namespace dudis