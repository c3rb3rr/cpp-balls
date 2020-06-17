#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum 
rodzaje_kulek {DEFAULT = 0, DAMAGING, HEALING, NROFTYPES};					//typy kulek które pojawiaj¹ siê w grze

class kulki
{
private:
	sf::CircleShape kolka_z_punktami;
	int type;

	void initShape(const sf::RenderWindow& window);

public:
	kulki(const sf::RenderWindow& window, int type);
	virtual ~kulki();						//Destruktor Wirtualny

	//Accessor
	const sf::CircleShape getShape() const;
	const int& getType() const;

	//Funkcje
	void update();
	void render(sf::RenderTarget& target);
};

/*
//Klasa dziedziczona
class kulki: public kulki
	private:
		int kolor;
	public:
	*/