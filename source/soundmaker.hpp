#pragma once
#include "pch.hpp"
#include "fractals.hpp"
#include "wavfile.hpp"

class synth
{
protected:
    Fractal* fractal;
    int samples_per_second;
    int volume;
    std::vector<std::complex<double> > orbit;
public:
    short waveform[SOUNDSIZE];  
    synth(Fractal* f);
    void setfractal(Fractal* f);
    void genoutput();
};