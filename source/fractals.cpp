#include "fractals.hpp"

Fractal::Fractal(){id=0;}
//void Fractal::draworbit(std::complex<double> rec,std::complex<double> point){}
//std::complex<double> nextpos(std::complex<double> rec,std::complex<double> point){return 0;}
Fractal::~Fractal(){}

void Fractal::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::VertexArray orb(sf::LineStrip, orbit.size());
    sf::Vector2u screen=target.getSize();
    for(size_t it=0;it<orbit.size();it++)
    {
        orb[it].position=sf::Vector2f(orbit[it].real()*100+(screen.x/2),orbit[it].imag()*100+(screen.y/2));
        orb[it].color=sf::Color::Red;
    }
    target.draw(orb,states);
}
Mandlebrot::Mandlebrot()
{
    id=1;
    orbit_samples=441;
}
void Mandlebrot::draworbit(std::complex<double> rec,std::complex<double> point)
{
    //std::complex<float> r=rec;
    //std::complex<float> p=point;
    //std::cout<<"halo1";
    orbit.clear();
    //std::cout<<"halo2";
    for (int i=0;i<orbit_samples;i++)
    {
        //std::cout<<"halo3";
        rec=nextpos(rec,point);
        orbit.push_back(rec);
        if(abs(rec)>32) break;
    }
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
}
Sfx::~Sfx()
{

}
Mandlebrot::~Mandlebrot()
{
}
