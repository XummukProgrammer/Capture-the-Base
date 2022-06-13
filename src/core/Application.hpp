#ifndef __APPLICATION_INCLUDE_FILE__
#define __APPLICATION_INCLUDE_FILE__

#include <string>

namespace sf
{
    class RenderWindow;
    class Event;
}

namespace ECS
{
    class World;
}

namespace Core
{
    class Window;
    class Assets;
    class Factory;
    class States;
    class VisualObjects;
    class Store;

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
        virtual void onInitRenderVisualObjects(VisualObjects* visualObjectsPtr) {}
        virtual void onInitECSWorld(ECS::World* worldPtr) {}
        void onInitStore(Store* storePtr) {}

        virtual void onUpdate(float deltaTime) {}
        virtual void onDraw(sf::RenderWindow* wndPtr) {}
        virtual void onEvent(sf::Event* eventPtr) {}
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
        VisualObjects* getVisualObjects() const;
        ECS::World* getECSWorld() const;
        Store* getStore() const;
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

        void initECSWorld();
        void destroyECSWorld();

        void initStore();
        void destroyStore();

    private:
        void onUpdate(float deltaTime);
        void onDraw(sf::RenderWindow* wndPtr);
        void onEvent(sf::Event* eventPtr);

    private:
        Window* _wndPtr = nullptr;
        Assets* _assetsPtr = nullptr;
        Factory* _factoryPtr = nullptr;
        States* _statesPtr = nullptr;
        VisualObjects* _visualObjectsPtr = nullptr;
        ECS::World* _ecsWorldPtr = nullptr;
        Store* _storePtr = nullptr;
        std::string _executeDir;
    };
}

#endif // __APPLICATION_INCLUDE_FILE__
