/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MenuScene
*/

#ifndef MENUSCENE_HPP_
#define MENUSCENE_HPP_

#include "ContextManager.hpp"
#include "IScene.hpp"
#include "GameInfos.hpp"
#include "Parallax.hpp"
#include <memory>
#include <vector>
#include "Prompt.hpp"

namespace Indie
{
    class MenuScene : public IScene
    {
    public:
        MenuScene(ContextManager &context);
        ~MenuScene();

        void init() final;
        void reset() final;
        void update(irr::f32 deltaTime) final;
        void renderPre3D() final;
        void renderPost3D() final;
        void setColor(irr::video::SColor color);

        void saveHighScoreMap(std::string mapPath, int score);

        const GameInfos &getGameInfos(void) const;
        void setGameInfos(const GameInfos &gameInfos);

    private:
        static const irr::core::vector2df velocities[5];
        static const std::string filepaths[5];

        ContextManager &context;
        std::vector<std::unique_ptr<Parallax>> parallax;
        GameInfos gameInfos;
    };
}

#endif /* !MENUSCENE_HPP_ */