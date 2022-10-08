#include "Framework.h"
#include "InputMgr.h"
#include "../Scene/SceneMgr.h"
#include "../DataTable/DataTableMGR.h"
#include "ResourceMgr.h"
#include "SoundMgr.h"

Framework::Framework()
    :timeScale(1.f)
{
}

Framework::~Framework()
{

}

void Framework::SetWindowSize(int width, int height)
{
    windowSize = Vector2i(width, height);
    window.create(VideoMode(windowSize.x, windowSize.y), "Game");
}

const Vector2i& Framework::GetWindowSize() const
{
    return windowSize;
}

float Framework::GetDT() const
{
    return deltaTime.asSeconds() * timeScale;
}

float Framework::GetRealDT() const
{
    return deltaTime.asSeconds();
}

bool Framework::Init()
{
    RESOURCE_MGR->LoadAll();
    DATATABLE_MGR->Init();
    SOUND_MGR->Init();
    SCENE_MGR->Init();
    InputMgr::Init();
    return true;
}

bool Framework::Do()
{
    while (window.isOpen())
    {
        deltaTime = clock.restart();
        float dt = GetDT();

        InputMgr::ClearInput();
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
                window.close();
            InputMgr::UpdateInput(ev);
        }
        SCENE_MGR->Update(dt);
        window.clear();
        SCENE_MGR->Draw(window);
        window.display();
    }
    return true;
}
