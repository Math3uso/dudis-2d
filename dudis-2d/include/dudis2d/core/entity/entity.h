#pragma once

#include "dudis2d/core/component/physicsComponent/physicsComponent.h"
#include "dudis2d/core/entity/entity.h"
#include "dudis2d/core/utils/types.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <memory>
#include <typeindex>
#include <unordered_map>

class Scene;

namespace dudis
{

  class Motion;
  class Component;
  class RenderQueue;
  class Renderable;
  // class PhysicsComponent;

  /**
   * @brief Tipo de transformação de uma entidade em relação ao seu pai.
   *
   * Define como a transformação local de uma entidade se combina com a
   * transformação do seu elemento pai.
   */
  enum class TransformType
  {
    /**
     * @brief Transformação relativa ao pai (padrão).
     *
     * O filho segue todas as transformações do pai. Ou seja,
     * posição, rotação e escala do pai influenciam diretamente no filho.
     */
    Relative,

    /**
     * @brief Transformação absoluta.
     *
     * A entidade ignora as transformações do pai e usa apenas sua
     * posição, rotação e escala locais. Somente esta entidade é afetada.
     */
    Absolute,

    /**
     * @brief Ignora transformações do pai para todos os filhos.
     *
     * Se um pai tiver este tipo, todos os seus filhos passam a ser
     * tratados como Absolute, ou seja, não recebem nenhuma
     * influência da transformação do pai.
     */
    DisableParentTransform
  };

  struct DDBufferPtr
  {
    void *ptr;
    void (*deleter)(void *);
    size_t size;
  };

#define DD_LOGS_ACTIVE 0
#define DD_NO_LOGS 1

  class Entity
  {

  private:
    bool _localDirty = false;
    bool _globalDirty = true;
    bool _orderChildren = false;
    glm::mat4 _localMatrix = glm::mat4(1.0f);
    glm::mat4 _globalMatrix = glm::mat4(1.0f);
    std::unordered_map<std::type_index, std::shared_ptr<Component>> _components;
    bool _physicsComponent = false;
    TransformType _transformType = TransformType::Relative;
    int _zOrder = 0;
    std::vector<DDBufferPtr> _owned;
    Entity *_root = nullptr;

    void _setRootEntity(Entity *root);
    void _propagateZOrderByChildren(int delta);

    template <typename T>
    static void _destroy(void *p)
    {
      delete static_cast<T *>(p);
    }

#ifdef DD_DEBUG
    static constexpr bool _DD_LOGS = DD_LOGS_ACTIVE;
#else
    static constexpr bool _DD_LOGS = DD_NO_LOGS;
#endif

  protected:
    std::string tag;
    dudis::SizeF size = {0.f, 0.f};
    dudis::Vec2 pos = {0, 0};
    Vec2 origin = {0, 0};
    Vec2 scale = {1, 1};
    float angle = 0.0f; // in radians
    std::vector<std::shared_ptr<Motion>> actions;
    std::shared_ptr<Motion> _action;
    std::vector<std::shared_ptr<Entity>> _children;
    Entity *_parent = nullptr;
    // bool _isUpdated = false;
    bool _ready = false;
    void _sortChildrenByIndex();

  public:
    char *labelT;
    Entity() = default;
    Entity(const std::string &tag) : tag(tag) {}
    float getAngle() const { return angle; }
    Vec2 getPos() const { return pos; }
    SizeF getSize() const { return size; }
    Vec2 getOrigin() const { return origin; }
    const std::string &getTag() const { return tag; }
    int getZOrder() { return _zOrder; }

    // void alloc(T* buff){}

    Entity *getRootEntity() { return _root; };
    const Entity *getRootEntity() const { return _root; };

    Entity *getParent() { return _parent; }
    const Entity *getParent() const { return _parent; }

    static std::shared_ptr<Entity> create()
    {
      return std::make_shared<Entity>();
    };
    static std::shared_ptr<Entity> create(const std::string &tag);

    const Vec2 getGlobalPos();
    float getGlobalRotation();
    const Vec2 getGlocalScale();
    Size getGlobalSize();

    void setTransformType(TransformType type) { _transformType = type; }

    virtual void setPos(const dudis::Vec2 &nPos);
    void setPos(float x, float y);
    void setZOrder(int zIndex);

    virtual void setSize(dudis::SizeF nSize);
    virtual void translate(const dudis::Vec2 &nPos);

    virtual void rotate(float nAngle);
    // virtual void start() {};
    virtual bool start() { return true; };
    virtual void init() {};
    virtual void update() {};
    virtual void render();
    virtual void updateChildren();
    virtual void buildRenderCommands(RenderQueue *queue) {};
    virtual void onAddedToParent() {};
    virtual void onAddedToParent(Entity *parent) {};
    virtual void onRemovedFromParent() {}

    bool intersectsWith(const std::shared_ptr<Entity> &other);

    void defaultUpdate();
    void runMotions();
    void setDirty();
    void updateTree();

    Rect getBoundingBox();

    const glm::mat4 &getLocalMatrix();
    const glm::mat4 &getGlobalMatrix();

    void setParent(Entity *parent) { _parent = parent; };
    void setOrigin(Vec2 nOrigin) { origin = nOrigin; }
    void setMotion(std::shared_ptr<Motion> action)
    {
      // this->actions.push_back(action);
      _action = action;
    };

    virtual void addChild(std::shared_ptr<Entity> entity);
    virtual void addChild(std::shared_ptr<Entity> entity, const int zOrder);
    void removeChild();
    void removeChild(const std::string &tag);

    const std::vector<std::shared_ptr<Entity>> &getChildren()
    {
      //_sortChildrenByIndex();
      return _children;
    };

    template <typename T, typename... Args>
    std::shared_ptr<T> addComponent(Args &&...args)
    {
      auto comp = std::make_shared<T>(std::forward<Args>(args)...);
      _components[typeid(T)] = comp;

      if (auto phys = std::dynamic_pointer_cast<PhysicsComponent>(comp))
      {
        _physicsComponent = true;
        puts("compoenent fisico enviado");
      }

      return comp;
    }

    // versão para usar instância já criada
    template <typename T>
    std::shared_ptr<T> addComponent(std::shared_ptr<T> &comp)
    {
      _components[typeid(T)] = comp;

      if (auto phys = std::dynamic_pointer_cast<PhysicsComponent>(comp))
      {
        _physicsComponent = true;
        if (_DD_LOGS)
        {
          puts("component fisico enviado [INSTANCIA]");
        }
      }

      return comp;
    }

    template <typename T>
    std::shared_ptr<T> getComponent()
    {
      auto it = _components.find(typeid(T));
      if (it != _components.end())
        return std::static_pointer_cast<T>(it->second);
      return nullptr;
    }

    template <typename T>
    void removeComponent() { _components.erase(typeid(T)); }

    template <typename T, typename... Args>
    T *New(Args &&...args)
    {
      T *data = new T(std::forward<Args>(args)...);

      if constexpr (_DD_LOGS)
      {
        _owned.push_back(DDBufferPtr{data, &_destroy<T>, sizeof(*data)});
      }
      else
      {
        _owned.push_back(DDBufferPtr{data, &_destroy<T>, 0});
      }
      return data;
    };

    template <typename T>
    static std::shared_ptr<T> create()
    {
      return std::make_shared<T>();
    }

    virtual ~Entity();

    friend Renderable;
    friend Scene;
  };
} // namespace dudis
