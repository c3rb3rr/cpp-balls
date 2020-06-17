#include "kulki.h"

//Szablon funckji
template <typename T>
T randomColor()
{
	T color = rand() % 255 + 1;
	return color;
}

void kulki::initShape(const sf::RenderWindow& window)
{
	this->kolka_z_punktami.setRadius(static_cast<float>(rand()%10+10));
	
	sf::Color color;
	switch (this->type)					//faktyczne rozró¿nianie kolorów kulek na to jakim typem s¹
	{
	case DEFAULT:										//normalne kulki za które dostajemy punkty, UWAGA - te¿ mo¿e byæ czerwona, ale nie ma obwódki, przez co nie zabiera punktów
		color = sf::Color(randomColor<int>(), randomColor<int>(), randomColor<int>());
		break;
	case DAMAGING:										//kulka czerwona Z BIA£¥ OBWÓDK¥ zabiera hp
		color = sf::Color::Red;
		this->kolka_z_punktami.setOutlineColor(sf::Color::White);
		this->kolka_z_punktami.setOutlineThickness(2.f);
		break;
	case HEALING:										//kulka zielona leczy
		color = sf::Color::Green;
		this->kolka_z_punktami.setOutlineColor(sf::Color::White);
		this->kolka_z_punktami.setOutlineThickness(2.f);
		break;
	}
	
	this->kolka_z_punktami.setFillColor(color);
	this->kolka_z_punktami.setPosition(
		sf::Vector2f(
			static_cast<float>(rand() % window.getSize().x - this->kolka_z_punktami.getGlobalBounds().width),					//pocz¹tek to lewy górny róg, wiêc ten "-" jest po to, ¿eby kó³ko nie wychodzi³o poza mapê 
			static_cast<float>(rand() % window.getSize().y - this->kolka_z_punktami.getGlobalBounds().height)
		)
	);
}

kulki::kulki(const sf::RenderWindow& window, int type)					//potrzebne do typów kulek
	: type(type)
{
	this->initShape(window);
}

kulki::~kulki()
{

}

const sf::CircleShape kulki::getShape() const
{
	return this->kolka_z_punktami;
}

const int & kulki::getType() const
{
	return this->type;
}



void kulki::update()
{

}

void kulki::render(sf::RenderTarget & target)
{
	target.draw(this->kolka_z_punktami);
}

