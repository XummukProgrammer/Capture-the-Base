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
    class Factory;
    class States;
    class RenderVisualObjects;

    class ApplicationDelegate
    {
    public:
        ApplicationDelegate() = default;
        virtual ~ApplicationDelegate() = default;

    public:
        virtual void onInitWindow(Window* wndPtr) {}
        virtual void onInitAssets(Assets* assetsPtr) {}
        virtual void onInitFactory(Factory* factoryPtr) {}
        virtual void onInitStates(States* statesPtr) {}
        virtual void onInitRenderVisualObjects(RenderVisualObjects* renderVisualObjectsPtr) {}

        virtual void onUpdate(float deltaTime) {}
        virtual void onDraw(sf::RenderWindow* wndPtr) {}
    };

    class Application final
    {
    public:
        Application();
        ~Application() = default;

    public:
        static Application& getInstance();
        static ApplicationDelegate* getDelegate(); // Impl from game project

    public:
        void exec(int argc, char* argv[]);

    public:
        std::string buildPath(std::string_view filePath) const;
        std::string removeFileNameFromPath(const std::string& filePath) const;

        Window* getWindow() const;
        Assets* getAssets() const;
        Factory* getFactory() const;
        States* getStates() const;
        RenderVisualObjects* getRenderVisualObjects() const;
        const std::string& getExecuteDir() const;

    private:
        void init(int argc, char* argv[]);
        void deinit();

        void start();

        void initExecuteDir(int argc, char* argv[]);

        void initWindow();
        void destroyWindow();

        void initAssets();
        void destroyAssets();

        void initFactory();
        void destroyFactory();

        void initStates();
        void destroyStates();

        void initRenderVisualObjects();
        void destroyRenderVisualObjects();

    private:
        void onUpdate(float deltaTime);
        void onDraw(sf::RenderWindow* wndPtr);

    private:
        Window* _wndPtr = nullptr;
        Assets* _assetsPtr = nullptr;
        Factory* _factoryPtr = nullptr;
        States* _statesPtr = nullptr;
        RenderVisualObjects* _renderVisualObjectsPtr = nullptr;
        std::string _executeDir;
    };
}

#endif // __APPLICATION_INCLUDE_FILE__
