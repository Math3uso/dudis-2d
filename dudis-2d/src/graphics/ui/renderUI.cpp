#include "dudis2d/graphics/ui/renderUI.h"
#include "dudis2d/graphics/ui/container/container.h"

using namespace dudis;
using namespace std;

void RenderUI::updateChildren() {
  for (const auto &child : children) {
    child->setPos({pos.x + child->getPos().x, pos.y + child->getPos().y});
  }
}

void RenderUI::setPos(Vec2 nPos) {
  pos = nPos;
  updateChildren();
}

void RenderUI::addChildren(shared_ptr<RenderUI> child) {
  puts("child add");
  child->setParent(this);
  this->children.push_back(child);
  std::cout << "total: " << children.size() << "\n";
}

// void RenderUI::render() {}

void RenderUI::udpateLayout() {

  auto inner = getInnerBounds();

  float yOffset = inner.y;
  float xOffset = inner.x;

  if (auto ui = dynamic_cast<Container *>(this)) {
    puts("elemento de layout recebido");
    if (ui->layout == Layout::Colunm) {
      for (const auto &child : children) {

        child->pos.x += inner.x;
        // child->pos.y += inner.y;
        child->pos.y += yOffset;

        // Limita o tamanho à área do pai
        child->size.w = std::min(child->size.w, (int)inner.width);
        child->size.h = std::min(child->size.h, (int)inner.height);

        yOffset += child->size.h + child->mrgin;

        // child->renderByParent();
        child->udpateLayout();
        child->render();
      }
      return;
    }
    for (const auto &child : children) {

      child->pos.x = xOffset;
      child->pos.y = inner.y;

      // Limita o tamanho à área do pai
      child->size.w = std::min(child->size.w, (int)inner.width);
      child->size.h = std::min(child->size.h, (int)inner.height);

      xOffset += child->size.w + child->mrgin;

      // child->renderByParent();
      child->udpateLayout();
      child->render();
    }
  }
}

void RenderUI::renderByParent() {
  if (!parent) {
    std::cerr << "parent is invalid\n";
    std::exit(1);
  }
}

Rectangle RenderUI::getInnerBounds() {
  Vec2 nPos = Vec2{pos.x + paddingGlobal, pos.y + paddingGlobal};
  SizeI nSize = SizeI(size.w - paddingGlobal * 2, size.h - paddingGlobal * 2);

  size = SizeI{size.w + paddingGlobal * 2, size.h + paddingGlobal * 2};

  return {nPos.x, nPos.y, nSize.w, nSize.h};
}