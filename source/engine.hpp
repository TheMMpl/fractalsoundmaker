#pragma once

#include "pch.hpp"
#include "fractals.hpp"
#include "soundmaker.hpp"

class Engine
{
private:
    sf::RenderWindow* window;
    sf::Event ev;
    Fractal* curr;
    bool state;
    std::string real;
    std::string imag;
    std::complex<double>* startingpoint;
    synth *sm;
    void initWindow();
public:
    Engine(/* args */);
    void run();
    void events();
    void sound();
    ~Engine();
};

