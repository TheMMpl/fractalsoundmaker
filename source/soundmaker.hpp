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
public:
    short waveform[44100];  
    synth(Fractal* f);
    void setfractal(Fractal* f);
    void genoutput();
};