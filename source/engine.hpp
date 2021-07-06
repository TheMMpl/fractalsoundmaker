#pragma once

#include "pch.hpp"
#include "fractals.hpp"
#include "soundmaker.hpp"
#include "gui.hpp"
#include "settings.hpp"

class Engine
{
private:
    int sa=0;
    sf::RenderWindow* window;
    sf::Event ev;
    Fractal* fractals[2];
    bool state;
    sf::Mouse mouse;
    sf::SoundBuffer buffer;
    sf::Sound playing;
    sf::Font* font;
    synth *sm;
    Button* gui[6];
    Params* settings;
    sf::Shader shader;
    sf::RectangleShape rect;
    void initWindow();
public:
    Engine(/* args */);
    void run();
    void events();
    void sound();
    std::complex<double> ptopoint(sf::Vector2f mouse);
    ~Engine();
};

