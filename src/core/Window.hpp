#ifndef __WINDOW_INCLUDE_FILE__
#define __WINDOW_INCLUDE_FILE__

#include <string>

namespace sf
{
    class RenderWindow;
}

namespace Core
{
    class Window final
    {
    public:
        Window() = default;
        ~Window() = default;

    public:
        void create(std::string_view title, unsigned width, unsigned height, unsigned framerateMax);
        void destroy();

        void exec();

    private:
        sf::RenderWindow* _wndPtr = nullptr;
    };
}

#endif // __WINDOW_INCLUDE_FILE__
