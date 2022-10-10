#include <SFML/Graphics.hpp>
#include "Framework/Framework.h"

int main()
{
    Framework* framework = FRAMEWORK;
    framework->SetWindowSize(640, 1000);
    framework->Init();
    framework->Do();
    return 0;
}