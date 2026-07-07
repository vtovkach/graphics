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

    void addObject(std::string objectPath, Vec4 initPosition);
    void run();

private:
    class Impl;
    std::unique_ptr<Impl> impl;
};