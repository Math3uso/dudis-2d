#include "dudis2d/dudis2d.h"
#include "dudis2d/debug.h"

class Test : public Scene
{
public:
    void start() override {
    };
    void update() override {

    };
    CREATE_SCENE(Test)
};

int main()
{

    auto scene = Test::create();

    return 0;
}
