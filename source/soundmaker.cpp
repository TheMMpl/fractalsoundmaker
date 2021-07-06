#include "soundmaker.hpp"

synth::synth(Fractal* f)
{
    fractal=f;
    samples_per_second=WAVFILE_SAMPLES_PER_SECOND;
    volume = 32000;
}

void synth::genoutput()
{
    orbit=fractal->orbit;
    for(int i=0;i<orbit.size();i++)
    {
        if(abs(orbit[i])>2)
        {
            orbit[i]*=2/abs(orbit[i]);
        }
    }
    int sampledist=samples_per_second/fractal->orbit.size(); 
    for(int i=0;i<SOUNDSIZE;i+=2)
    {
        if(i%sampledist==0)
        {
            waveform[i]=orbit[i/(sampledist*1)].real();
        }
        else {
            double mp=1/(i%sampledist);
            double mv = (1-cos(mp*M_PI))/2;
            waveform[i]=volume*(orbit[i/sampledist].real()*(1-mv)+orbit[i/sampledist+1].real()*mv);
        }
    }
    for (int i = 1; i <SOUNDSIZE; i+=2)
    {
        if(i%sampledist==1)
        {
            waveform[i]=orbit[i/sampledist].imag();
        }
        else  {
            double mp=1/(i%sampledist);
            double mv = (1-cos(mp*M_PI))/2;
            waveform[i]=volume*(orbit[i/sampledist].imag()*(1-mv)+orbit[i/sampledist+1].imag()*mv);
        }
    }
}
void synth::setfractal(Fractal* f)
{
    fractal=f;
}