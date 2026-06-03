add_library(dudis-core OBJECT
    async/asyncWorker.cpp
    # component/physicsComponent/body/body.cpp
    # component/physicsComponent/contactListenear/contactListenear.cpp
    # component/physicsComponent/debugDraw/debugDraw.cpp
    # component/physicsComponent/physicsComponent.cpp
    debug/dd-debug.cpp
    entity/entity.cpp
    math/rect.cpp
    math/vec2.cpp
    math/vec3.cpp
    math/vec4.cpp
    model/model.cpp
    motion/easing/easing.cpp
    motion/motion.cpp
    test/ddContext.cpp
    ../globals/time.cpp
)

dd_configure_module(dudis-core)

target_link_libraries(dudis-core
    PRIVATE
        raylib
        box2d
        glm
)
