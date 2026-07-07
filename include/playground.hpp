#pragma once

#include <string>
#include <memory> 
#include "math.hpp"

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
    
    void addObject(std::string objectPath, Vec4 initPosition);

protected:
    virtual void _ready() = 0;
    virtual void _process() = 0;

    virtual void _keyPressed() = 0;
    virtual void _keyReleased() = 0;

private:
    class Impl;
    std::unique_ptr<Impl> impl;
};