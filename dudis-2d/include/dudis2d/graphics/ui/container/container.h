#include "dudis2d/graphics/ui/renderUI.h"

namespace dudis {

enum class Layout { Row, Colunm };

enum class HorizontalAlignment { Left, Center, Right };

enum class VerticalAlignment { Top, Center, Bottom };

class Alignment {
public:
  HorizontalAlignment h = HorizontalAlignment::Left;
  VerticalAlignment v = VerticalAlignment::Top;

  Alignment(HorizontalAlignment hor = HorizontalAlignment::Left,
            VerticalAlignment ver = VerticalAlignment::Top)
      : h(hor), v(ver) {};
};

class Container : public RenderUI {
protected:
  Layout layout;

public:
  Container(Layout nLayout = Layout::Colunm) : RenderUI(), layout(nLayout) {}
  void render() override;

  // void setChildrenProps(A)

  static std::shared_ptr<Container> create(Layout nLayout = Layout::Colunm);

  friend RenderUI;
};
} // namespace dudis