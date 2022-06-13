#include "Application.hpp"

#include "Window.hpp"
#include "Assets.hpp"
#include "Factory.hpp"
#include "States.hpp"
#include "VisualObjects.hpp"

#include <ecs/ECSWorld.hpp>

#include <SFML/Graphics.hpp>

#include <filesystem>

namespace Core
{
    Application::Application()
        : _wndPtr(new Window)
        , _assetsPtr(new Assets)
        , _factoryPtr(new Factory)
        , _statesPtr(new States)
        , _visualObjectsPtr(new VisualObjects)
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
        _wndPtr->setOnEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

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
        _factoryPtr->registerType<AssetRenderLayers>("AssetRenderLayers");
        _factoryPtr->registerType<AssetFont>("AssetFont");

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
        getDelegate()->onInitRenderVisualObjects(_visualObjectsPtr);
    }

    void Application::destroyRenderVisualObjects()
    {
        delete _visualObjectsPtr;
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
        _visualObjectsPtr->onUpdate(deltaTime);

        getDelegate()->onUpdate(deltaTime);
    }

    void Application::onDraw(sf::RenderWindow* wndPtr)
    {
        _visualObjectsPtr->onDraw(wndPtr);
        _ecsWorldPtr->onDraw(wndPtr);

        getDelegate()->onDraw(wndPtr);
    }

    void Application::onEvent(sf::Event* eventPtr)
    {
        _ecsWorldPtr->onEvent(eventPtr);
    }

    std::string Application::buildPath(std::string_view filePath) const
    {
        return _executeDir + "\\..\\" + std::string{filePath};
    }

    std::string Application::removeFileNameFromPath(const std::string& filePath) const
    {
        return std::filesystem::path(filePath).remove_filename().generic_string();
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

    VisualObjects* Application::getVisualObjects() const
    {
        return _visualObjectsPtr;
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
