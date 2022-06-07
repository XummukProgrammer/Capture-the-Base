#include "Application.hpp"

#include "Window.hpp"
#include "Assets.hpp"
#include "Factory.hpp"

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
    }

    void Application::deinit()
    {
        destroyWindow();
        destroyAssets();
        destroyFactory();
    }

    void Application::start()
    {
        if (!_wndPtr) {
            // TODO: Assert
            return;
        }

        _wndPtr->start();
    }

    void Application::initExecuteDir(int argc, char* argv[])
    {
        const std::string executePath = std::string(argv[0]);
        _executeDir = executePath.substr(0, executePath.find_last_of("\\"));
    }

    void Application::initWindow()
    {
        _wndPtr = new Window();
        _wndPtr->create("Capture the Base", 800, 600, 60);
        _wndPtr->setOnUpdateCallback(std::bind(&Application::onUpdate, this, std::placeholders::_1));
        _wndPtr->setOnDrawCallback(std::bind(&Application::onDraw, this, std::placeholders::_1));

    }

    void Application::destroyWindow()
    {
        _wndPtr->destroy();
        delete _wndPtr;
    }

    void Application::initAssets()
    {
        _assetsPtr = new Assets;
        _assetsPtr->loadFromFile("assets/Assets.xml");
    }

    void Application::destroyAssets()
    {
        delete _assetsPtr;
    }

    void Application::initFactory()
    {
        _factoryPtr = new Factory;
        _factoryPtr->registerType<AssetTexture>("AssetTexture");
    }

    void Application::destroyFactory()
    {
        delete _factoryPtr;
    }

    void Application::onUpdate(float deltaTime)
    {
    }

    void Application::onDraw(sf::RenderWindow* wndPtr)
    {
        if (auto* asset = _assetsPtr->getAsset<AssetTexture>("test")) {
            sf::Sprite sprite;
            sprite.setTexture(*asset);
            sprite.setTextureRect({ 0, 0, 32, 32 });
            wndPtr->draw(sprite);
        }
    }

    std::string Application::buildPath(std::string_view filePath) const
    {
        return _executeDir + "/../../" + std::string{filePath};
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

    const std::string& Application::getExecuteDir() const
    {
        return _executeDir;
    }
}
