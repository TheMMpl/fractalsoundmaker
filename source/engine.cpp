
#include "engine.hpp"

Engine::Engine()
{
    initWindow();
    curr=new Mandlebrot();
    //curr=new Sfx();
    state=0;
    startingpoint=new std::complex<double>(0.274,0.528);
    //startingpoint=new std::complex<double>(-0.1,0.8);
   // startingpoint=new std::complex<double>(1.2,-0.4);
    //startingpoint=new std::complex<double>(1.6,-0.3);
    //startingpoint=new std::complex<double>(1.6,-0.5);
    sm=new synth(curr);
}

void Engine::initWindow()
{
    window=new sf::RenderWindow(sf::VideoMode(1280,720),"ziuziu");
    window->setFramerateLimit(60);
}

void Engine::events()
{
    while (window->pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            if(ev.key.code==sf::Keyboard::Enter)
            {
                if(state)
                {
                    std::cout<<"liczba: "<<real<<" "<<imag<<" ";
                    startingpoint=new std::complex<double>/*(0.2,-0.4);//*/(std::stod(real),std::stod(imag));
                    state=0;
                    real="";
                    imag="";
                }
                else state=1;
            }
            /*else if(state){
                imag+=ev.key.code;
            } 
            else{
                real+=ev.key.code;
                std::cout<<real;
            } */
            break;
        case sf::Event::TextEntered:
            if(state) imag+=ev.text.unicode;
            else real+=ev.text.unicode;
            break;
        case sf::Event::MouseButtonPressed:
            sound();
            break;
        default:
            break;
        }
    }
}

void Engine::run()
{
    //int i=0;
    while (window->isOpen())
    {
        events();
        window->clear();
        //if(i==0)
        curr->draworbit(*startingpoint,*startingpoint);
        window->draw(*curr);
        window->display();
        //i++;
    }
}
void Engine::sound()
{
    playing.pause();
    sm->genoutput();
    if(fswitch)
    {
        sa++;
        std::cout<<"halo2";
        std::string name="sound"+std::to_string(sa)+".wav";
        const char *fname=name.c_str();
        FILE * f = wavfile_open(fname);
        if(!f)std::cout<<"nieziu!"<<std::endl;
        wavfile_write(f,sm->waveform,WAVFILE_SAMPLES_PER_SECOND);
	    wavfile_close(f);
    }
    else
    {
        buffer.loadFromSamples(sm->waveform,WAVFILE_SAMPLES_PER_SECOND,1,WAVFILE_SAMPLES_PER_SECOND);
        playing.setBuffer(buffer);
        playing.setLoop(true);
        playing.play();
    }
    std::cout<<"halo";
}

Engine::~Engine()
{
}
