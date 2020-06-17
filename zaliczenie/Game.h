#pragma once

#include<iostream>
#include<ctime>
#include<vector>
#include<sstream>

#include "Player.h"
#include "kulki.h"

//Klasa
class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event sfmlEvent;					//pobieranie z klawiatury "evetów" czyli klawiszy ¿eby poruszaæ graczem

	Player player;

	int points;

	sf::Font font;					//do wyœwietlania tekstu
	sf::Text guiText;
	sf::Text endGameText;

	std::vector<kulki> kuleczki;
	float spawnTimerMax;
	float spawnTimer;
	int max_liczba_kulek;

	void initVariables();
	void initWindow();
	void initFonts();
	void initText();

public:
	Game();					//konstruktory i dekonstruktory
	~Game();

	const bool& getEndGame() const;					//Accessors


	//Funkcje
	const bool running() const;
	void pollEvents();

	void spawnowanie_kulek();
	const int losowy_typ_kulki() const;
	void updatePlayer();
	void updateCollision();
	void updateGui();
	void update();

	void renderGui(sf::RenderTarget* target);					//renderowanie tekstu
	void render();
};
