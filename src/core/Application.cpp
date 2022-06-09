#include "Application.hpp"

#include "Window.hpp"
#include "Assets.hpp"
#include "Factory.hpp"
#include "States.hpp"

#include <SFML/Graphics.hpp>

namespace Core
{
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
        initWindow();
        initStates();
    }

    void Application::deinit()
    {
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
        _wndPtr = new Window();
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
        _assetsPtr = new Assets;
        _assetsPtr->loadFromFile("assets\\Assets.xml");

        getDelegate()->onInitAssets(_assetsPtr);
    }

    void Application::destroyAssets()
    {
        delete _assetsPtr;
    }

    void Application::initFactory()
    {
        _factoryPtr = new Factory;
        _factoryPtr->registerType<AssetTexture>("AssetTexture");

        getDelegate()->onInitFactory(_factoryPtr);
    }

    void Application::destroyFactory()
    {
        delete _factoryPtr;
    }

    void Application::initStates()
    {
        _statesPtr = new States;

        getDelegate()->onInitStates(_statesPtr);
    }

    void Application::destroyStates()
    {
        delete _statesPtr;
    }

    void Application::onUpdate(float deltaTime)
    {
        _statesPtr->onUpdate(deltaTime);

        getDelegate()->onUpdate(deltaTime);
    }

    void Application::onDraw(sf::RenderWindow* wndPtr)
    {
        if (auto* asset = _assetsPtr->getAsset<AssetTexture>("test")) {
            sf::Sprite sprite;
            sprite.setTexture(*asset);
            sprite.setTextureRect({ 0, 0, 32, 32 });
            wndPtr->draw(sprite);
        }

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

    const std::string& Application::getExecuteDir() const
    {
        return _executeDir;
    }
}
