#include "dudis2d/core/ddCamera/ddCamera.h"
#include "dudis2d/core/window/window.h"
#include "dudis2d/globals/app.h"

using namespace dudis;
using namespace std;

DDCamera::DDCamera() {
  _camera.target = (Vec2){0.0f, 0.0f};
  _camera.offset = (Vec2){0, 0};
  _camera.rotation = 0;
  _camera.zoom = 1.0f;
}

void DDCamera::drawDebugInfo() const {
  if (!_isDebugMode)
    return;

  const auto &options = this->getDebugOptions();

  if (options.drawCameraTarget) {
    DrawCircleV(this->_camera.target, 50, BLUE);
  }

  if (options.drawCameraOffset) {
    DrawCircleV(this->_camera.offset, 50, YELLOW);
  }

  // if (options.drawCameraBounds) {
  //   DrawRectangleLinesEx(
  //       Rectangle{_camera.offset.x - 5, _camera.offset.y - 5, 100, 100}, 2,
  //       RED);
  // }
}