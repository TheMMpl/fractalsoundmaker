#include "fractals.hpp"

Fractal::Fractal(){id=0;}

Fractal::~Fractal(){}

void Fractal::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::VertexArray orb(sf::LineStrip, orbit.size());
    sf::Vector2u screen=target.getSize();
    for(size_t it=0;it<orbit.size();it++)
    {
        orb[it].position=sf::Vector2f(orbit[it].real()*200+(screen.x/2),orbit[it].imag()*200+(screen.y/2));
        orb[it].color=sf::Color::Red;
    }
    target.draw(orb,states);
}
Mandlebrot::Mandlebrot()
{
    id=1;
    orbit_samples=441;
    recpoint=std::complex<double>(0,0);
}
void Mandlebrot::draworbit(std::complex<double> rec,std::complex<double> point)
{
    orbit.clear();
    for (int i=0;i<orbit_samples;i++)
    {
        rec=nextpos(rec,point);
        orbit.push_back(rec);
        if(abs(rec)>32) break;
    }
    recpoint=orbit[orbit.size()-1];
    //orbit.push_back(orbit[0]);
    /*for(size_t i=0;i<orbit.size();i++)
    {
        std::cout<<orbit[i].real()<<" "<<orbit[i].imag()<<std::endl;
    }
    std::cout<<std::endl;
    //draw()*/
}
std::complex<double> Mandlebrot::nextpos(std::complex<double> rec,std::complex<double> point)
{
    return rec*rec+point;
}

double rqrare(std::complex<double> c)
{
    return c.real()*c.real();
}
double imqrare(std::complex<double> c)
{
    return c.imag()*c.imag();
}

std::complex<double> Sfx::nextpos(std::complex<double> rec,std::complex<double> point)
{
    std::complex<double> c(rqrare(point),imqrare(point));
    return rec*(rqrare(rec)+imqrare(rec))-(rec*c);
}
void Sfx::draworbit(std::complex<double> rec,std::complex<double> point)
{
    orbit.clear();
    for (int i=0;i<orbit_samples;i++)
    {
        //std::cout<<"halo3";
        rec=nextpos(rec,point);
        orbit.push_back(rec);
        if(abs(rec)>32) break;
    }
    recpoint=orbit[orbit.size()-1];
   /* for(size_t i=0;i<orbit.size();i++)
    {
        std::cout<<orbit[i].real()<<" "<<orbit[i].imag()<<std::endl;
    }
    std::cout<<std::endl;*/
}
Sfx::Sfx()
{
    id=1;
    orbit_samples=441;
    recpoint=std::complex<double>(0,0);
}
Sfx::~Sfx()
{

}
Mandlebrot::~Mandlebrot()
{
}
