#include <core/Application.hpp>
#include <game/GameApplicationDelegate.hpp>

namespace Core
{
    ApplicationDelegate* Application::getDelegate()
    {
        static Game::GameApplicationDelegate delegate;
        return &delegate;
    }
}

int main(int argc, char* argv[])
{
    auto& app = Core::Application::getInstance();
    app.exec(argc, argv);
    return 0;
}
