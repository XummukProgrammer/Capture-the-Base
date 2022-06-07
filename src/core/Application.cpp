#include "Application.hpp"

#include "Window.hpp"
#include "Assets.hpp"

#include <SFML/Graphics.hpp>

namespace Core
{
    Application& Application::getInstance()
    {
        static Application app{};
        return app;
    }

    void Application::exec()
    {
        init();
        start();
        deinit();
    }

    void Application::init()
    {
        initAssets();
        initWindow();
    }

    void Application::deinit()
    {
        destroyWindow();
        destroyAssets();
    }

    void Application::start()
    {
        if (!_wndPtr) {
            // TODO: Assert
            return;
        }

        _wndPtr->start();
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

        auto assetTexturePtr = std::make_unique<AssetTexture>();
        assetTexturePtr->loadFromFile("test.png");
        _assetsPtr->addAsset("test", std::move(assetTexturePtr));
    }

    void Application::destroyAssets()
    {
        delete _assetsPtr;
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
}
