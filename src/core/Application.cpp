#include "Application.hpp"

#include "Window.hpp"
#include "Assets.hpp"
#include "Factory.hpp"
#include "States.hpp"
#include "RenderVisualObjects.hpp"

#include <ecs/ECSWorld.hpp>

#include <SFML/Graphics.hpp>

namespace Core
{
    Application::Application()
        : _wndPtr(new Window)
        , _assetsPtr(new Assets)
        , _factoryPtr(new Factory)
        , _statesPtr(new States)
        , _renderVisualObjectsPtr(new RenderVisualObjects)
        , _ecsWorldPtr(new ECS::World)
    {

    }

    Application& Application::getInstance()
    {
        static Application app{};
        return app;
    }

    void Application::exec(int argc, char* argv[])
    {
        init(argc, argv);
        start();
        deinit();
    }

    void Application::init(int argc, char* argv[])
    {
        initExecuteDir(argc, argv);
        initFactory();
        initAssets();
        initRenderVisualObjects();
        initWindow();
        initStates();
        initECSWorld();
    }

    void Application::deinit()
    {
        destroyECSWorld();
        destroyRenderVisualObjects();
        destroyWindow();
        destroyAssets();
        destroyFactory();
        destroyStates();
    }

    void Application::start()
    {
        _wndPtr->start();
    }

    void Application::initExecuteDir(int argc, char* argv[])
    {
        const std::string executePath = std::string(argv[0]);
        _executeDir = removeFileNameFromPath(executePath);
    }

    void Application::initWindow()
    {
        _wndPtr->create("Capture the Base", 800, 600, 60);
        _wndPtr->setOnUpdateCallback(std::bind(&Application::onUpdate, this, std::placeholders::_1));
        _wndPtr->setOnDrawCallback(std::bind(&Application::onDraw, this, std::placeholders::_1));

        getDelegate()->onInitWindow(_wndPtr);

    }

    void Application::destroyWindow()
    {
        _wndPtr->destroy();
        delete _wndPtr;
    }

    void Application::initAssets()
    {
        _assetsPtr->loadFromFile("assets\\Assets.xml");

        getDelegate()->onInitAssets(_assetsPtr);
    }

    void Application::destroyAssets()
    {
        delete _assetsPtr;
    }

    void Application::initFactory()
    {
        _factoryPtr->registerType<AssetTexture>("AssetTexture");

        getDelegate()->onInitFactory(_factoryPtr);
    }

    void Application::destroyFactory()
    {
        delete _factoryPtr;
    }

    void Application::initStates()
    {
        getDelegate()->onInitStates(_statesPtr);
    }

    void Application::destroyStates()
    {
        delete _statesPtr;
    }

    void Application::initRenderVisualObjects()
    {
        getDelegate()->onInitRenderVisualObjects(_renderVisualObjectsPtr);
    }

    void Application::destroyRenderVisualObjects()
    {
        delete _renderVisualObjectsPtr;
    }

    void Application::initECSWorld()
    {
        _ecsWorldPtr->create();

        getDelegate()->onInitECSWorld(_ecsWorldPtr);
    }

    void Application::destroyECSWorld()
    {
        _ecsWorldPtr->destroy();
        delete _ecsWorldPtr;
    }

    void Application::onUpdate(float deltaTime)
    {
        _statesPtr->onUpdate(deltaTime);
        _ecsWorldPtr->onUpdate(deltaTime);
        _renderVisualObjectsPtr->onUpdate(deltaTime);

        getDelegate()->onUpdate(deltaTime);
    }

    void Application::onDraw(sf::RenderWindow* wndPtr)
    {
        _renderVisualObjectsPtr->onDraw(wndPtr);

        getDelegate()->onDraw(wndPtr);
    }

    std::string Application::buildPath(std::string_view filePath) const
    {
        return _executeDir + "\\..\\..\\" + std::string{filePath};
    }

    std::string Application::removeFileNameFromPath(const std::string& filePath) const
    {
        return filePath.substr(0, filePath.find_last_of("\\"));
    }

    Window* Application::getWindow() const
    {
        return _wndPtr;
    }

    Assets* Application::getAssets() const
    {
        return _assetsPtr;
    }

    Factory* Application::getFactory() const
    {
        return _factoryPtr;
    }

    States* Application::getStates() const
    {
        return _statesPtr;
    }

    RenderVisualObjects* Application::getRenderVisualObjects() const
    {
        return _renderVisualObjectsPtr;
    }

    ECS::World* Application::getECSWorld() const
    {
        return _ecsWorldPtr;
    }

    const std::string& Application::getExecuteDir() const
    {
        return _executeDir;
    }
}
