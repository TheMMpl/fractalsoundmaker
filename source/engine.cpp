
#include "engine.hpp"

Engine::Engine()
{
    initWindow();
    settings=new Params();
    fractals[0]=new Mandlebrot();
    fractals[1]=new Sfx();
    font=new sf::Font();
    font->loadFromFile("ASCII.ttf");
    sf::Vector2f guiedge=window->mapPixelToCoords(sf::Vector2i(window->getSize()-sf::Vector2u(350,100)));
    gui[0]=new Block(sf::Vector2f(300,85),guiedge,font,"",settings,0);
    gui[1]=new TextField(sf::Vector2f(70,20),guiedge+sf::Vector2f(18,15),font,"",settings,sf::Color::White,0,1);
    gui[2]=new TextField(sf::Vector2f(70,20),guiedge+sf::Vector2f(2*18+70,15),font,"",settings,sf::Color::White,1,2);
    gui[3]=new PushButton(sf::Vector2f(80,20),guiedge+sf::Vector2f(3*18+2*70,15),font,"calculate",settings,3);
    gui[4]=new PlayButton(sf::Vector2f(70,20),guiedge+sf::Vector2f(18,50),font,"play",settings,1);
    gui[5]=new FractalEnum(sf::Vector2f(70,20),guiedge+sf::Vector2f(2*18+70,50),font,"next",settings,1);
    //curr=new Sfx();
    state=0;
    settings->point=std::complex<double>(0.274,0.528);
    //startingpoint=new std::complex<double>(-0.1,0.8);
    //startingpoint=new std::complex<double>(1.2,-0.4);
    //startingpoint=new std::complex<double>(1.6,-0.3);
    //startingpoint=new std::complex<double>(1.6,-0.5);
    sm=new synth(fractals[0]);
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
        sf::Vector2f m=sf::Vector2f(window->mapPixelToCoords(mouse.getPosition(*window)));
        switch (ev.type)
        {
        case sf::Event::Closed:
            playing.stop();
            window->close();
            break;
       /* case sf::Event::KeyPressed:
            if(ev.key.code==sf::Keyboard::Enter)
            {
                if(state)
                {
                   // std::cout<<"liczba: "<<real<<" "<<imag<<" ";
                    startingpoint=new std::complex<double>/*(0.2,-0.4);//(std::stod(real),std::stod(imag));
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
            } 
            break;*/

        case sf::Event::TextEntered:
            if(settings->buttonid==1) {
                settings->real+=ev.text.unicode;
                gui[1]->update(settings->real);
            }
            else if(settings->buttonid==2)
            {
                settings->imag+=ev.text.unicode;
                gui[2]->update(settings->imag);
            }
            break;

        case sf::Event::MouseButtonPressed:
            for(int i=0;i<6;i++)
            {
                //std::cout<<m.x<<" "<<m.y<<std::endl;
                if(gui[i]->selectable()&&gui[i]->isSelected(m))
                {
                    settings->buttonid=i;
                    gui[i]->onSelected();
                }
            }
           // std::cout<<gui[1]->selectable()<<std::endl;
            //std::cout<<"akrualny guzik: "<<settings->buttonid<<std::endl;
            if(settings->play)sound();
            else playing.pause();
            sm->setfractal(fractals[settings->fractalid]);
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
        fractals[settings->fractalid]->draworbit(settings->point,settings->point);
        window->draw(*fractals[settings->fractalid]);
        for(int i=0;i<6;i++)
        {
            window->draw(*gui[i]);
            //std::cout<<"ziu ";
        }
        //std::cout<<std::endl;
        window->display();
        //i++;
    }
}
void Engine::sound()
{
    playing.pause();
    sm->genoutput();
    if(settings->fswitch)
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
        buffer.loadFromSamples(sm->waveform,WAVFILE_SAMPLES_PER_SECOND,1,WAVFILE_SAMPLES_PER_SECOND);
        playing.setBuffer(buffer);
        playing.setLoop(true);
        playing.play();
    //std::cout<<"halo";
}

Engine::~Engine()
{
}
