#include "Application.hpp"

#include "Window.hpp"

namespace Core
{
    void Application::exec()
    {
        init();
        start();
        deinit();
    }

    void Application::init()
    {
        initWindow();
    }

    void Application::deinit()
    {
        destroyWindow();
    }

    void Application::start()
    {
        if (!_wndPtr) {
            // TODO: Assert
            return;
        }

        _wndPtr->start();
    }

    void Application::initWindow()
    {
        _wndPtr = new Window();
        _wndPtr->create("Capture the Base", 800, 600, 60);

    }

    void Application::destroyWindow()
    {
        _wndPtr->destroy();
        delete _wndPtr;
    }
}
