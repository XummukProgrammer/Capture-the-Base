#ifndef __WINDOW_INCLUDE_FILE__
#define __WINDOW_INCLUDE_FILE__

#include <string>
#include <functional>

namespace sf
{
    class RenderWindow;
}

namespace Core
{
    class Window final
    {
    public:
        using UpdateCallback = std::function<void(float)>;
        using DrawCallback = std::function<void(sf::RenderWindow* window)>;

    public:
        Window() = default;
        ~Window() = default;

    public:
        void create(std::string_view title, unsigned width, unsigned height, unsigned framerateMax);
        void destroy();

        void setOnUpdateCallback(const UpdateCallback& callback);
        void setOnDrawCallback(const DrawCallback& callback);

        void start();

    private:
        void onUpdate(float deltaTime);
        void onDraw();

    private:
        sf::RenderWindow* _wndPtr = nullptr;
        UpdateCallback _onUpdateCallback;
        DrawCallback _onDrawCallback;
    };
}

#endif // __WINDOW_INCLUDE_FILE__
