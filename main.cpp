#include <core/Application.hpp>

int main(int argc, char* argv[])
{
    auto& app = Core::Application::getInstance();
    app.exec(argc, argv);
    return 0;
}
