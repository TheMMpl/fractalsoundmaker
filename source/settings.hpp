#pragma once
#include "pch.hpp"

class Params
{
public:
    //char synthtype;
    //sf::Vector2u size;
    //sf::ContextSettings settings;
    std::string real;
    std::string imag;
    bool fswitch;
    int fractalid;
    int buttonid;
    std::complex<double> point;
    bool play;
public:
    Params();
    ~Params();
};