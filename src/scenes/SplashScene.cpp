/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScene
*/

#include "SplashScene.hpp"
#include "MenuScene.hpp"
#include "ServiceLocator.hpp"
#include "TitleScene.hpp"
#include "ImageLoader.hpp"
#include "SceneManager.hpp"
#include "MusicManager.hpp"
#include "EventHandler.hpp"
#include "ServiceLocator.hpp"

const std::unordered_map<Indie::SplashScene::SPLASH_ASSETS, std::string> Indie::SplashScene::splashPaths
    = { { Indie::SplashScene::SPLASH_ASSETS::BG, "../ressources/images/splash/bg.png" },
          { Indie::SplashScene::SPLASH_ASSETS::LOGO, "../ressources/images/splash/Logo.png" },
          { Indie::SplashScene::SPLASH_ASSETS::PROJECT, "../ressources/images/splash/Project.png" },
          { Indie::SplashScene::SPLASH_ASSETS::BOMBER, "../ressources/images/splash/bomberLogos.png" } };

Indie::SplashScene::SplashScene(ContextManager &context)
    : context(context)
    , bg(nullptr)
{
}

Indie::SplashScene::~SplashScene()
{
    if (this->bg)
        this->context.getDriver()->removeTexture(this->bg);
    for (auto img : this->splashScreens) {
        if (img.second)
            this->context.getDriver()->removeTexture(img.second);
    }
}

void Indie::SplashScene::init()
{
    Indie::ServiceLocator::getInstance().get<MusicManager>().setMusic(0);
    this->bg = Indie::ServiceLocator::getInstance().get<ImageLoader>().getImage(
        this->splashPaths.at(Indie::SplashScene::SPLASH_ASSETS::BG).c_str());
    for (int type = (int)Indie::SplashScene::SPLASH_ASSETS::LOGO; type < (int)Indie::SplashScene::SPLASH_ASSETS::END; type++) {
        Image *newImage = Indie::ServiceLocator::getInstance().get<Indie::ImageLoader>().getImage(
            this->splashPaths.at((Indie::SplashScene::SPLASH_ASSETS)type).c_str());

        this->splashScreens.insert({ (Indie::SplashScene::SPLASH_ASSETS)type, newImage });
    }
    this->currentAsset = Indie::SplashScene::SPLASH_ASSETS::LOGO;
    this->lastTime = this->context.getDevice()->getTimer()->getTime();
}

void Indie::SplashScene::reset()
{
    if (this->bg)
        this->context.getDriver()->removeTexture(this->bg);
    for (auto img : this->splashScreens) {
        if (img.second)
            this->context.getDriver()->removeTexture(img.second);
    }
    this->splashScreens.clear();
    this->init();
}

void Indie::SplashScene::skipScene(void)
{
    auto &sceneManager = Indie::ServiceLocator::getInstance().get<SceneManager>();

    sceneManager.setScene<Indie::MenuScene>(this->context);
    sceneManager.setSubScene<Indie::TitleScene>();
    sceneManager.setSceneUpdateActive(true);
    sceneManager.setSceneRenderActive(true);
    sceneManager.setSubSceneUpdateActive(true);
    sceneManager.setSubSceneRenderActive(true);
}

void Indie::SplashScene::update(irr::f32)
{
    irr::u32 currentTime = this->context.getDevice()->getTimer()->getTime();
    irr::f32 elapsedTime = (irr::f32)((currentTime - this->lastTime) / 1000.f);

    if (elapsedTime >= 4.f) {
        if (this->currentAsset != Indie::SplashScene::SPLASH_ASSETS::BOMBER) {
            int currentAsset = (int)this->currentAsset;
            currentAsset++;
            this->currentAsset = (Indie::SplashScene::SPLASH_ASSETS)(currentAsset);
        }
        if (elapsedTime >= 4.f) {
            this->lastTime = currentTime;
        }
    }
    if (EventHandler::getInstance().isAnyKeyPressedAtOnce() || ServiceLocator::getInstance().get<MusicManager>().getStatus() == Music::Status::Loop) {
        ServiceLocator::getInstance().get<MusicManager>().setStatus(Music::Status::Loop);
        this->skipScene();
        Indie::EventHandler::getInstance().resetKeys();
    }
}

void Indie::SplashScene::renderPre3D()
{
    context.displayImage(this->bg, POS(0, 0));
    context.displayImage(this->splashScreens.at(this->currentAsset), POS(0, 0));
}

void Indie::SplashScene::renderPost3D() {}