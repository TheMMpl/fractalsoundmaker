#pragma once
#include "pch.hpp"

class Fractal : public sf::Drawable
{

protected:
    int id;
    int orbit_samples;
public:
    std::vector<std::complex<double> > orbit;
    std::complex<double> recpoint;
    Fractal();
    virtual std::complex<double> nextpos(std::complex<double> rec,std::complex<double> point)=0;
    virtual void draworbit(std::complex<double> rec,std::complex<double> point)=0;
    virtual ~Fractal();
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

class Mandlebrot : public Fractal
{
public:
    Mandlebrot(/* args */);
    std::complex<double> nextpos(std::complex<double> rec,std::complex<double> point);
    void draworbit(std::complex<double> rec,std::complex<double> point);
    //void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    ~Mandlebrot();
};

class Sfx : public Fractal
{
public:
    Sfx();
    std::complex<double> nextpos(std::complex<double> rec,std::complex<double> point);
    void draworbit(std::complex<double> rec,std::complex<double> point);
    ~Sfx();
};


