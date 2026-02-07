#include "dudis2d/dudis2d.h"
#include "dudis2d/debug.h"

using namespace std;
using namespace dudis;

int main()
{
  Window window(dudis::Size(800, 600), "Init window Test");

  debug::Test::Expect(window.init()).Equal(true);

  return 0;
}
