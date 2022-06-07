#include "Application.hpp"

#include "Window.hpp"

#include <SFML/Graphics.hpp>

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
        _wndPtr->setOnUpdateCallback(std::bind(&Application::onUpdate, this, std::placeholders::_1));
        _wndPtr->setOnDrawCallback(std::bind(&Application::onDraw, this, std::placeholders::_1));

    }

    void Application::destroyWindow()
    {
        _wndPtr->destroy();
        delete _wndPtr;
    }

    void Application::onUpdate(float deltaTime)
    {
    }

    void Application::onDraw(sf::RenderWindow* wndPtr)
    {
    }
}
