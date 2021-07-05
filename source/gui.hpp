#pragma once
#include "pch.hpp"
#include "settings.hpp"

class Button : public sf::Drawable
{
protected:
    sf::RectangleShape button;
    Params* settings;
    sf::Text text;
    int id;
public:
    Button(sf::Vector2f size,sf::Vector2f position,sf::Font* font,std::string text,Params* settings,int id);
    bool isSelected(sf::Vector2f mouse);
    virtual void update(std::string text);
    virtual void onSelected();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual bool selectable()=0;
    virtual ~Button();
};

class Block : public Button
{
public:
    Block(sf::Vector2f size,sf::Vector2f position,sf::Font* font,std::string text,Params* settings,int id);
    void update(std::string text);
    void onSelected();
    bool selectable();
    ~Block();
};

class TextField : public Button
{
private:
    bool type;
public:
    TextField(sf::Vector2f size,sf::Vector2f position,sf::Font* font,std::string text,Params* settings,sf::Color color,bool t,int id);
    void update(std::string text);
    void onSelected() override;
    bool selectable() override;
    ~TextField();
};

class FractalEnum : public Button
{
    public:
    FractalEnum(sf::Vector2f size,sf::Vector2f position,sf::Font* font,std::string text,Params* settings,int id);
    void update(std::string text);
    void onSelected();
    bool selectable();
    ~FractalEnum();
};

class PushButton : public Button
{
public:
    PushButton(sf::Vector2f size,sf::Vector2f position,sf::Font* font,std::string text,Params* settings,int id);
    void update(std::string text);
    void onSelected();
    bool selectable();
    ~PushButton();
};

class PlayButton : public Button
{
public:
    PlayButton(sf::Vector2f size,sf::Vector2f position,sf::Font* font,std::string text,Params* settings,int id);
    void update(std::string text);
    void onSelected();
    bool selectable();
    ~PlayButton();
};
