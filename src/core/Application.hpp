#ifndef __APPLICATION_INCLUDE_FILE__
#define __APPLICATION_INCLUDE_FILE__

#include <string>

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
        void exec(int argc, char* argv[]);

    public:
        std::string buildPath(std::string_view filePath) const;

    private:
        void init(int argc, char* argv[]);
        void deinit();

        void start();

        void initExecuteDir(int argc, char* argv[]);

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
        std::string _executeDir;
    };
}

#endif // __APPLICATION_INCLUDE_FILE__
