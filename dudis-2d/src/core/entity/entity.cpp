#include "dudis2d/core/entity/entity.h"
#include "dudis2d/core/log/log.h"
#include "dudis2d/core/motion/motion.h"
#include <algorithm>

using namespace std;
using namespace dudis;

shared_ptr<Entity> Entity::create(const string &tag)
{
  return make_shared<Entity>(tag);
}

void Entity::defaultUpdate()
{
  this->update();
  if (_physicsComponent)
  {
    // Temporarily disabled: physics sync handled elsewhere
  }
  // this->updateChildren();
  this->runMotions();
}

void Entity::runMotions()
{
  if (_action)
  {
    if (_action->isDone())
    {
      _action.reset();
      puts("motion liberada");
    }
    else
    {
      _action->step();
    }
  }
  // if (_action && !_action->isDone()) {
  //   _action->step();
  // }
}

void Entity::_setRootEntity(Entity *root)
{
  _root = root;
}

void Entity::updateChildren() {}

void Entity::render() { this->getGlobalMatrix(); }

void Entity::addChild(shared_ptr<Entity> child)
{

  child->setParent(this);

  if (_transformType == TransformType::DisableParentTransform)
  {
    child->setTransformType(TransformType::Absolute);
  }

  if (child->_parent)
  {
    // caso o elemento filho tenha um zOrder ele faz: ZChild + zParent.
    //  mas c o z do child for 0 ele faz: filho.z = Zparent +1;
    int baseZ = child->getParent()->_zOrder;
    child->_zOrder += (child->_zOrder == 0) ? (_children.size() + 1) + baseZ : baseZ;
  }

  if (child->getRootEntity() == nullptr && child->getParent() != nullptr)
  {
    const auto parent = child->getParent();
    child->_setRootEntity(parent->getRootEntity());
  }

  _children.push_back(child);

  this->setDirty();

  _orderChildren = true;

  this->onAddedToParent();
  this->onAddedToParent(this);

  this->_sortChildrenByIndex();
}

void Entity::addChild(shared_ptr<Entity> child, const int zOrder)
{
  child->_zOrder = zOrder;
  this->addChild(child);
  return;
}

void Entity::removeChild()
{
  _children.pop_back();
};

void Entity::removeChild(const std::string &tag)
{
  _children.erase(std::remove_if(_children.begin(), _children.end(), [&tag](const shared_ptr<Entity> &child)
                                 { return child->tag == tag; }),
                  _children.end());

  this->onRemovedFromParent();
};

/**
 * @brief Calcula e retorna a matriz de transformação local do Entity.
 *
 * Esta matriz representa a posição, rotação e escala do Entity
 * relativas ao seu elemento pai (se houver).
 *
 * A matriz é recalculada apenas quando a posição, rotação, escala
 * do Entity ou do seu pai é modificada, evitando cálculos desnecessários.
 *
 * Transformações aplicadas na ordem:
 * 1. Translação (posição)
 * 2. Rotação (ângulo em torno do eixo Z)
 * 3. Escala (dimensões local X e Y)
 *
 * @return const glm::mat4& Referência constante à matriz de transformação
 * local.
 */
const glm::mat4 &Entity::getLocalMatrix()
{
  if (_localDirty)
  {
    _localMatrix = glm::mat4(1.0f);
    _localMatrix = glm::translate(_localMatrix, glm::vec3(pos.x, pos.y, 0));
    _localMatrix = glm::rotate(_localMatrix, angle, glm::vec3(0, 0, 1));
    _localMatrix = glm::scale(_localMatrix, glm::vec3(scale.x, scale.y, 1));

    _localDirty = false;
  }

  return _localMatrix;
}

/**
 * @brief Calcula e retorna a matriz de transformação global do Entity.
 *
 * Esta matriz representa a transformação completa do Entity no espaço mundial,
 * considerando a hierarquia de pais e o tipo de transformação.
 *
 * - Se o Entity tiver um pai e seu tipo de transformação não for Absolute,
 *   a matriz global é calculada como: matrizGlobalPai * matrizLocal.
 * - Caso contrário, a matriz global é igual à matriz local.
 *
 * A matriz global é recalculada apenas quando o Entity ou algum de seus pais
 * é modificado (_globalDirty é true), evitando cálculos desnecessários.
 *
 * @return const glm::mat4& Referência constante à matriz de transformação
 * global.
 */
const glm::mat4 &Entity::getGlobalMatrix()
{
  if (_globalDirty)
  {
    if (_parent && _transformType != TransformType::Absolute)
    {
      // std::cout << "n foi do cache." << "chamado de: " << this->labelT << "\n";
      _globalMatrix = _parent->getGlobalMatrix() * getLocalMatrix();
    }
    else
    {
      // std::cout << "c pa foi do cache " << "chamado de: " << this->labelT << "\n";
      _globalMatrix = getLocalMatrix();
    }
    _globalDirty = false;
  }
  return _globalMatrix;
}

void Entity::setPos(const dudis::Vec2 &nPos)
{
  this->setDirty();
  pos = nPos;
}

void Entity::setPos(float x, float y)
{
  this->setPos(Vec2{x, y});
  return;
}

void Entity::setSize(dudis::SizeF nSize)
{
  this->setDirty();
  size = nSize;
}

void Entity::setZOrder(int zIndex)
{
  _zOrder = zIndex;
  // temp entity precia de um zOrderGlobal
  _parent->_orderChildren = true;
  _parent->_sortChildrenByIndex();
}

void Entity::rotate(float nAngle)
{
  this->setDirty();
  angle = nAngle;
}

void Entity::translate(const Vec2 &nPos)
{

  this->setDirty();
  pos.x += nPos.x;
  pos.y += nPos.y;
}

void Entity::setDirty()
{
  _localDirty = true;
  _globalDirty = true;
  for (auto &child : _children)
  {
    child->setDirty();
  }
}

const Vec2 Entity::getGlobalPos()
{
  glm::mat4 m = getGlobalMatrix();
  return {m[3][0], m[3][1]};
}

float Entity::getGlobalRotation()
{
  glm::mat4 m = getGlobalMatrix();

  float scaleX = glm::length(glm::vec3(m[0]));
  float scaleY = glm::length(glm::vec3(m[1]));

  float rot = atan2(m[1][0] / scaleY, m[0][0] / scaleX);

  return rot;
}

const Vec2 Entity::getGlocalScale()
{
  glm::mat4 m = getGlobalMatrix();
  float scaleX = glm::length(glm::vec3(m[0])); // 1ª coluna
  float scaleY = glm::length(glm::vec3(m[1])); // 2ª coluna
  return {scaleX, scaleY};
}

Size Entity::getGlobalSize()
{

  glm::mat4 m = getGlobalMatrix();

  float scaleX = glm::length(glm::vec3(m[0])); // coluna X
  float scaleY = glm::length(glm::vec3(m[1])); // coluna Y

  return {size.w * scaleX, size.h * scaleY};
}

Rect Entity::getBoundingBox()
{
  auto globalSize = this->getGlobalSize();
  auto scale = this->getGlocalScale();

  float minX = this->getGlobalPos().x - origin.x * scale.x;
  float minY = this->getGlobalPos().y - origin.y * scale.y;

  return Rect{minX, minY, (float)globalSize.w, (float)globalSize.h};
}

bool Entity::intersectsWith(const std::shared_ptr<Entity> &other)
{
  return this->getBoundingBox().intersects(other->getBoundingBox());
}

// void Entity::release() { _children.clear(); }

void Entity::_sortChildrenByIndex()
{
  //_children
  if (_orderChildren)
  {
    Log::Info("order chamado");
    sort(
        _children.begin(), _children.end(),
        [](const shared_ptr<Entity> &child1, const shared_ptr<Entity> &child2)
        {
          return child1->_zOrder < child2->_zOrder;
        });
    _orderChildren = false;
  }
  return;
}

Entity::~Entity()
{

  Log::Info("Entity liberada [ENTITY]");

  if (_owned.size() > 0)
  {
    Log::Alert("\n[ENTITY] Deletando dados extras [OWNED]\n");
    for (auto &data : _owned)
    {

      std::cout << "\u2003bytes liberados: " << data.size << "\n";

      data.deleter(data.ptr);
    }
    _owned.clear();
    Log::Alert("\n[ENTITY] Deletando dados extras [OWNED]\n");
  }
  else
  {
    Log::Success("vazio sem dados extras");
  }
  _components.clear();
  _children.clear();
}