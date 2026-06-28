#include "playground.hpp"

constexpr const char* DEFAULT_TITLE = "Renderer";
constexpr int DEFAULT_WIDTH = 800;
constexpr int DEFAULT_HEIGHT = 600;

PlayGround::PlayGround() : window(DEFAULT_TITLE, DEFAULT_WIDTH, DEFAULT_HEIGHT), renderer(DEFAULT_WIDTH, DEFAULT_HEIGHT)
{

}

PlayGround::PlayGround(const char *title, int width, int height) : window(title, width, height), renderer(width ,height)
{

}

void PlayGround::run()
{

}