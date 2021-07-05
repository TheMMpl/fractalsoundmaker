#include "soundmaker.hpp"

synth::synth(Fractal* f)
{
    fractal=f;
    samples_per_second=WAVFILE_SAMPLES_PER_SECOND;
    volume = 32000;
}

void synth::genoutput()
{
    int sampledist=samples_per_second/fractal->orbit.size(); 
    for(int i=0;i<SOUNDSIZE;i+=2)
    {
        if(i%sampledist==0)
        {
            waveform[i]=fractal->orbit[i/(sampledist*1)].real();
        }
        else {
            double mp=1/(i%sampledist);
            double mv = (1-cos(mp*M_PI))/2;
            waveform[i]=volume*(fractal->orbit[i/sampledist].real()*(1-mv)+fractal->orbit[i/sampledist+1].real()*mv);
        }
    }
    for (int i = 1; i <SOUNDSIZE; i+=2)
    {
        if(i%sampledist==1)
        {
            waveform[i]=fractal->orbit[i/sampledist].imag();
        }
        else  {
            double mp=1/(i%sampledist);
            double mv = (1-cos(mp*M_PI))/2;
            waveform[i]=volume*(fractal->orbit[i/sampledist].imag()*(1-mv)+fractal->orbit[i/sampledist+1].imag()*mv);
        }
    }
}
void synth::setfractal(Fractal* f)
{
    fractal=f;
}