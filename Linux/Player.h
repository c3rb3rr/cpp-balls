#ifndef _Player_h
#define _Player_h


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Player
{
private:
	sf::RectangleShape kolka_z_punktami;

	float movementSpeed;
	int hp;
	int hpMax;

	void initVariables();
	void initShape();

public:
	Player(float x = 0.f, float y = 0.f);
	//Destruktor wirtualny
	virtual ~Player();


	//Accessor
	const sf::RectangleShape& getShape() const;
	const int& getHp() const;
	const int& getHpMax() const;

	//Funkcje
	void dodaj_DMG(const int damage);
	void dodaj_HP(const int health);


	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

#endif _Player_H