#include "soundmaker.hpp"

synth::synth(Fractal* f)
{
    fractal=f;
    samples_per_second=WAVFILE_SAMPLES_PER_SECOND;
    volume = 32000;
}

void synth::genoutput()
{
   // std::cout<<"ziu1"<<std::endl;
    int sampledist=samples_per_second/fractal->orbit.size(); 
       //std::cout<<"ziu"<<std::endl;
    for(int i=0;i<samples_per_second;i++)
    {
        if(i%sampledist==0)
        {
            waveform[i]=fractal->orbit[i/sampledist].real();
        }
        else{
            double mp=1/(i%sampledist);
            double mv = (1-cos(mp*M_PI))/2;
            waveform[i]=volume*(fractal->orbit[i/sampledist].real()*(1-mv)+fractal->orbit[i/sampledist+1].real()*mv);
        }
        //std::cout<<"ziu3"<<std::endl;
    }
}