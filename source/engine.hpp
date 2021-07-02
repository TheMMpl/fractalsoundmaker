#pragma once

#include "pch.hpp"
#include "fractals.hpp"
#include "soundmaker.hpp"

class Params
{
public:
    //char synthtype;
    sf::Vector2u size;
    sf::ContextSettings settings;
};

class Engine
{
private:
    int sa=0;
    sf::RenderWindow* window;
    sf::Event ev;
    Fractal* curr;
    bool state;
    bool fswitch=false;
    std::string real;
    std::string imag;
    std::complex<double>* startingpoint;
    sf::SoundBuffer buffer;
    sf::Sound playing;
    synth *sm;
    void initWindow();
public:
    Engine(/* args */);
    void run();
    void events();
    void sound();
    ~Engine();
};

