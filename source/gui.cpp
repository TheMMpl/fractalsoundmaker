#include "gui.hpp"

Button::Button(sf::Vector2f size,sf::Vector2f position,sf::Font* font, std::string text,Params* settings,int id)
{
    button.setSize(size);
    button.setPosition(position);
    button.setOutlineColor(sf::Color::Blue);
    button.setFillColor(sf::Color::Black);
    button.setOutlineThickness(3);
    this->settings=settings;
    this->text.setFillColor(sf::Color::Black);
    this->text.setFont(*font);
    this->text.setCharacterSize(15);
    this->text.setStyle(sf::Text::Regular);
    this->text.setString(text);
    //sf::Rect bounds=this->text.getLocalBounds();
   // sf::Vector2f padding((size.x-bounds.width)/2,(size.y-bounds.height)/2);
    this->text.setPosition(position);
    this->id=id;
}

bool Button::isSelected(sf::Vector2f mouse)
{
    if((mouse.x>=button.getPosition().x&&mouse.x<=button.getPosition().x+button.getSize().x)&&
    (mouse.y>=button.getPosition().y&&mouse.y<=button.getPosition().y+button.getSize().y)) return true;
    else return false;
}

void Button::update(std::string text){}
void Button::onSelected(){}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(button,states);
    target.draw(text,states);
}

Button::~Button(){}

Block::Block(sf::Vector2f size,sf::Vector2f position,sf::Font* font,std::string text,Params* settings,int id) : 
Button(size,position,font,text,settings,id){}

void Block::update(std::string text){}
void Block::onSelected(){}
bool Block::selectable()
{
    return false;
}
Block::~Block(){}



TextField::TextField(sf::Vector2f size,sf::Vector2f position,sf::Font* font,std::string text,Params* settings,sf::Color color,bool t,int id) : 
Button(size,position,font,text,settings,id)
{
    button.setFillColor(sf::Color::White);
    type=t;
    //this->text.setPosition(button.getPosition());
}
void TextField::update(std::string text)
{
    this->text.setString(text);
}
void TextField::onSelected(){}
bool TextField::selectable()
{
    return true;
}

TextField::~TextField()
{
}
FractalEnum::FractalEnum(sf::Vector2f size,sf::Vector2f position,sf::Font* font,std::string text,Params* settings,int id) :
Button(size,position,font,text,settings,id)
{
    this->text.setFillColor(sf::Color::White);
}

void FractalEnum::update(std::string text){}
void FractalEnum::onSelected()
{
    if(settings->fractalid<FRACTALS)settings->fractalid++;
    else settings->fractalid=0;
}

bool FractalEnum::selectable()
{
    return true;
}

FractalEnum::~FractalEnum(){}


PushButton::PushButton(sf::Vector2f size,sf::Vector2f position,sf::Font* font,std::string text,Params* settings,int id) :
Button(size,position,font,text,settings,id) 
{
    this->text.setFillColor(sf::Color::White);
}

void PushButton::onSelected()
{
    settings->point=std::complex<double>(std::stod(settings->real),std::stod(settings->imag));
    settings->real="";
    settings->imag="";
    settings->changed=true;
}
bool PushButton::selectable()
{
    return true;
}
void PushButton::update(std::string text){}
PushButton::~PushButton(){}

PlayButton::PlayButton(sf::Vector2f size,sf::Vector2f position,sf::Font* font,std::string text,Params* settings,int id) :
Button(size,position,font,text,settings,id)
{
    this->text.setFillColor(sf::Color::White);
}

void PlayButton::update(std::string text){}
void PlayButton::onSelected()
{
    settings->play=!settings->play;
}
bool PlayButton::selectable()
{
    return true;
}
PlayButton::~PlayButton(){}