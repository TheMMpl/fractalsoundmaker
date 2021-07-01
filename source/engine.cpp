
#include "engine.hpp"

Engine::Engine()
{
    initWindow();
    curr=new Mandlebrot();
    state=0;
    //startingpoint=new std::complex<double>(0.274,0.528);
    startingpoint=new std::complex<double>(-0.1,0.8);
    //startingpoint=new std::complex<double>(-0.1,0.8);
    sm=new synth(curr);
}

void Engine::initWindow()
{
    window=new sf::RenderWindow(sf::VideoMode(800,600),"ziuziu");
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
    while (window->isOpen())
    {
        events();
        window->clear();
        curr->draworbit(0,*startingpoint);
        window->draw(*curr);
        window->display();
    }
}
void Engine::sound()
{
    std::cout<<"halo1";
    sm->genoutput();
    std::cout<<"halo2";
    FILE * f = wavfile_open("sound.wav");
    if(!f)std::cout<<"nieziu!"<<std::endl;
    wavfile_write(f,sm->waveform,WAVFILE_SAMPLES_PER_SECOND);
	wavfile_close(f);
    std::cout<<"halo";
}

Engine::~Engine()
{
}
