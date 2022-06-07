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

    void Window::exec()
    {
        if (!_wndPtr) {
            // TODO: Assert
            return;
        }

        while (_wndPtr->isOpen()) {
            sf::Event event;
            while (_wndPtr->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    _wndPtr->close();
                }
            }

            _wndPtr->clear();
            _wndPtr->display();
        }
    }
}
