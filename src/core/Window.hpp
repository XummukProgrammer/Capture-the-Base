#ifndef __WINDOW_INCLUDE_FILE__
#define __WINDOW_INCLUDE_FILE__

#include <SFML/System/Vector2.hpp>

#include <string>
#include <functional>

namespace sf
{
    class RenderWindow;
    class Event;
}

namespace Core
{
    class Window final
    {
    public:
        using UpdateCallback = std::function<void(float)>;
        using DrawCallback = std::function<void(sf::RenderWindow*)>;
        using EventCallback = std::function<void(sf::Event*)>;

    public:
        Window() = default;
        ~Window() = default;

    public:
        void create(std::string_view title, unsigned width, unsigned height, unsigned framerateMax);
        void destroy();

        void setOnUpdateCallback(const UpdateCallback& callback);
        void setOnDrawCallback(const DrawCallback& callback);
        void setOnEventCallback(const EventCallback& callback);

        void start();

    public:
        sf::Vector2i getMousePosition() const;

    private:
        void onUpdate(float deltaTime);
        void onDraw();

    private:
        sf::RenderWindow* _wndPtr = nullptr;
        UpdateCallback _onUpdateCallback;
        DrawCallback _onDrawCallback;
        EventCallback _onEventCallback;
    };
}

#endif // __WINDOW_INCLUDE_FILE__
