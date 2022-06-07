#ifndef __APPLICATION_INCLUDE_FILE__
#define __APPLICATION_INCLUDE_FILE__

namespace sf
{
    class RenderWindow;
}

namespace Core
{
    class Window;
    class Assets;

    class Application final
    {
    public:
        Application() = default;
        ~Application() = default;

    public:
        static Application& getInstance();

    public:
        void exec();

    private:
        void init();
        void deinit();

        void start();

        void initWindow();
        void destroyWindow();

        void initAssets();
        void destroyAssets();

    private:
        void onUpdate(float deltaTime);
        void onDraw(sf::RenderWindow* wndPtr);

    private:
        Window* _wndPtr = nullptr;
        Assets* _assetsPtr = nullptr;
    };

}

#endif // __APPLICATION_INCLUDE_FILE__
