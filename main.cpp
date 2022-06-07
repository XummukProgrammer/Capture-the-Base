#include <core/Window.hpp>

int main()
{
    Core::Window window;
    window.create("Capture the Base", 800, 600, 60);
    window.exec();
    window.destroy();
    return 0;
}
