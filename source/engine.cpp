
#include "engine.hpp"

Engine::Engine()
{
    settings=new Params();
    initWindow();
    fractals[0]=new Mandlebrot();
    fractals[1]=new Sfx();
    fractals[2]=new Chirkov();
    font=new sf::Font();
    font->loadFromFile("ASCII.ttf");
    sf::Vector2f guiedge=window->mapPixelToCoords(sf::Vector2i(window->getSize()-sf::Vector2u(350,100)));
    gui[0]=new Block(sf::Vector2f(300,85),guiedge,font,"",settings,0);
    gui[1]=new TextField(sf::Vector2f(70,20),guiedge+sf::Vector2f(18,15),font,"",settings,sf::Color::White,0,1);
    gui[2]=new TextField(sf::Vector2f(70,20),guiedge+sf::Vector2f(2*18+70,15),font,"",settings,sf::Color::White,1,2);
    gui[3]=new PushButton(sf::Vector2f(80,20),guiedge+sf::Vector2f(3*18+2*70,15),font,"calculate",settings,3);
    gui[4]=new PlayButton(sf::Vector2f(70,20),guiedge+sf::Vector2f(18,50),font,"play",settings,1);
    gui[5]=new FractalEnum(sf::Vector2f(70,20),guiedge+sf::Vector2f(2*18+70,50),font,"next",settings,1);
    state=0;
    settings->point=std::complex<double>(0.274,0.528);
    //startingpoint=new std::complex<double>(-0.1,0.8);
    //startingpoint=new std::complex<double>(1.2,-0.4);
    //startingpoint=new std::complex<double>(1.6,-0.3);
    //startingpoint=new std::complex<double>(1.6,-0.5);
    sm=new synth(fractals[0]);
    if(!shader.loadFromFile("source/vertex.glsl","source/fragment.glsl"))
    std::cout<<"tywala"<<std::endl;
    shader.setUniform("res",sf::Glsl::Vec2(settings->windowx,settings->windowy));
    shader.setUniform("fractalid",settings->fractalid);
    rect.setPosition(0,0);
    rect.setSize(window->mapPixelToCoords(sf::Vector2i(window->getSize())));
}

void Engine::initWindow()
{
    window=new sf::RenderWindow(sf::VideoMode(settings->windowx,settings->windowy),"FSM");
    window->setFramerateLimit(60);
}

void Engine::events()
{
    while (window->pollEvent(ev))
    {
        sf::Vector2f m=sf::Vector2f(window->mapPixelToCoords(mouse.getPosition(*window)));
        bool butttonpressed=false;
        switch (ev.type)
        {
        case sf::Event::Closed:
            playing.stop();
            window->close();
            break;

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
                if(gui[i]->selectable()&&gui[i]->isSelected(m))
                {
                    settings->buttonid=i;
                    gui[i]->onSelected();
                    butttonpressed=true;
                }
            }
            if(settings->play)sound();
            else playing.pause();
            sm->setfractal(fractals[settings->fractalid]);
            shader.setUniform("fractalid",settings->fractalid);
            if(!butttonpressed)
            {
                settings->point=ptopoint(m);
                settings->changed=true;
            }
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
        window->draw(rect,&shader);
        if(settings->changed)
        {
            fractals[settings->fractalid]->draworbit(settings->point,settings->point);
            settings->changed=false;
        } 
        else
        {
            fractals[settings->fractalid]->draworbit(fractals[settings->fractalid]->recpoint,settings->point);
        }
        
        
        window->draw(*fractals[settings->fractalid]);
        for(int i=0;i<6;i++)
        {
            window->draw(*gui[i]);
        }
        window->display();
    }
}
void Engine::sound()
{
    //playing.pause();
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
        buffer.loadFromSamples(sm->waveform,WAVFILE_SAMPLES_PER_SECOND,2,WAVFILE_SAMPLES_PER_SECOND);
        playing.setBuffer(buffer);
        playing.setLoop(true);
        playing.play();
}

std::complex<double> Engine::ptopoint(sf::Vector2f mouse)
{
    return std::complex<double>((mouse.x-(settings->windowx/2))/200,(mouse.y-settings->windowy/2)/200);
}

Engine::~Engine()
{
    
}
