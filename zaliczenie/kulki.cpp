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
	switch (this->type)					//faktyczne rozr�nianie kolor�w kulek na to jakim typem s�
	{
	case DEFAULT:										//normalne kulki za kt�re dostajemy punkty, UWAGA - te� mo�e by� czerwona, ale nie ma obw�dki, przez co nie zabiera punkt�w
		color = sf::Color(randomColor<int>(), randomColor<int>(), randomColor<int>());
		break;
	case DAMAGING:										//kulka czerwona Z BIA�� OBW�DK� zabiera hp
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
			static_cast<float>(rand() % window.getSize().x - this->kolka_z_punktami.getGlobalBounds().width),					//pocz�tek to lewy g�rny r�g, wi�c ten "-" jest po to, �eby k�ko nie wychodzi�o poza map� 
			static_cast<float>(rand() % window.getSize().y - this->kolka_z_punktami.getGlobalBounds().height)
		)
	);
}

kulki::kulki(const sf::RenderWindow& window, int type)					//potrzebne do typ�w kulek
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

