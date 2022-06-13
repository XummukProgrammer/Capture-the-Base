#include "Window.hpp"

#include <SFML/Graphics.hpp>

namespace Core
{
    void Window::create(std::string_view title, unsigned width, unsigned height, unsigned framerateMax)
    {
        _wndPtr = new sf::RenderWindow(sf::VideoMode(width, height), std::string{title});
        _wndPtr->setVerticalSyncEnabled(false);
        _wndPtr->setFramerateLimit(framerateMax);
    }

    void Window::destroy()
    {
        delete _wndPtr;
    }

    void Window::setOnUpdateCallback(const UpdateCallback& callback)
    {
        _onUpdateCallback = callback;
    }

    void Window::setOnDrawCallback(const DrawCallback& callback)
    {
        _onDrawCallback = callback;
    }

    void Window::start()
    {
        if (!_wndPtr) {
            // TODO: Assert
            return;
        }

        sf::Clock clock;

        while (_wndPtr->isOpen()) {
            sf::Time deltaTime = clock.getElapsedTime();
            clock.restart();

            sf::Event event;
            while (_wndPtr->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    _wndPtr->close();
                }
            }

            onUpdate(deltaTime.asSeconds());

            _wndPtr->clear(sf::Color::White);
            onDraw();
            _wndPtr->display();
        }
    }

    sf::Vector2i Window::getMousePosition() const
    {
        return sf::Mouse::getPosition(*_wndPtr);
    }

    void Window::onUpdate(float deltaTime)
    {
        if (_onUpdateCallback && _wndPtr->hasFocus()) {
            _onUpdateCallback(deltaTime);
        }
    }

    void Window::onDraw()
    {
        if (_onDrawCallback) {
            _onDrawCallback(_wndPtr);
        }
    }
}
