#pragma once 

#include "playground.hpp"

class Example : public PlayGround
{
public:
    Example(const char *title, int width, int height) : PlayGround(title, width, height)
    {
    }

private:
    void _ready() override
    {
    }
    void _process() override
    {
    }

    void _keyPressed() override
    {
    }

    void _keyReleased() override
    {
    }
};