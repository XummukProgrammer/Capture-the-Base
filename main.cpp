#include <core/Application.hpp>

int main()
{
    auto& app = Core::Application::getInstance();
    app.exec();
    return 0;
}
