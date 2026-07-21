#pragma once

#include <string>
#include <memory> 

#include "scene.hpp"

class PlayGround
{
public:
    PlayGround(const char *title, int width, int height);
    PlayGround();
    ~PlayGround();

    PlayGround(const PlayGround&) = delete;
    PlayGround& operator=(const PlayGround&) = delete; 

    PlayGround(PlayGround&&) = delete;
    PlayGround& operator=(PlayGround&&) = delete;

    void run();

protected:
    virtual void _ready() = 0;
    virtual void _process(Scene *activeScene) = 0;

    virtual void _keyPressed() = 0;
    virtual void _keyReleased() = 0;

    void addScene(std::unique_ptr<Scene> scene);
    void deleteScene(const std::string& sceneId);
    void setActiveScene(const std::string& sceneId);

    Scene* getScene(const std::string& sceneId) const;
    Scene* getActiveScene() const;

private:
    class Impl;
    std::unique_ptr<Impl> impl;
};