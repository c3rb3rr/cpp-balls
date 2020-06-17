#include "Player.h"



void Player::initVariables()
{
	this->movementSpeed = 3.f;				//prêdkoœæ z jak¹ porusza siê gracz
	this->hpMax = 10;				//pocz¹tkowe ¿ycie z jakim startuje gracz
	this->hp = hpMax;		//pocz¹tkowe ¿ycie z jakim startuje gracz
}

void Player::initShape()
{
	this->kolka_z_punktami.setFillColor(sf::Color::Green);
	this->kolka_z_punktami.setSize(sf::Vector2f(50.f, 50.f));				//mo¿na ustawiæ wiele innych rzeczy, this->kolka_z_punktami."reszta"
}

Player::Player(float x, float y)
{
	this->kolka_z_punktami.setPosition(x, y);				//ustawia pozycjê pocz¹tkow¹ gracza - lewy górny róg

	this->initVariables();
	this->initShape();
}

Player::~Player()
{

}

//Accessors
const sf::RectangleShape & Player::getShape() const
{
	return this->kolka_z_punktami;
}

const int & Player::getHp() const
{
	return this->hp;
}

const int & Player::getHpMax() const
{
	return this->hpMax;
}

//Functions
void Player::dodaj_DMG(const int damage)						//zabieranie hp przez kulki
{
	if (this->hp > 0)					//kiedy mamy jeszcze hp do stracenia to traci to hp
		this->hp -= damage;

	if (this->hp < 0)					//kiedy giniemy to hp nie spada poni¿ej 0, tylko niech zostaje na 0
		this->hp = 0;
}

void Player::dodaj_HP(const int health)
{
	if (this->hp < this->hpMax)				//kiedy nie mamy pelnego ¿ycia to jest ono uzupe³niane
		this->hp += health;

	if (this->hp > this->hpMax)				//je¿eli mamy pe³ne ¿ycie to nie ma co uzupe³niæ, wiêc zostaje takie samo
		this->hp = this->hpMax;
}

void Player::updateInput()
{
	//Keyboard input
	//Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->kolka_z_punktami.move(-this->movementSpeed, 0.f);						//move vs. setPosition - pierwsze bierze aktualn¹ pozycjê gracza i przesuwa go na nowe miejsce - drugie sztywno ustawia
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))					//else if zamiast if, poniewa¿ A i D nie wciska siê razem, nie ma to sensu, dlatego jest to wykluczone. Np. W i A ju¿ mo¿na, ¿eby iœæ na skos
	{
		this->kolka_z_punktami.move(this->movementSpeed, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->kolka_z_punktami.move(0.f, -this->movementSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))				//ponowne wykluczanie wciskania naraz W i S
	{
		this->kolka_z_punktami.move(0.f, this->movementSpeed);
	}
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget * target)
{
	//Left
	if (this->kolka_z_punktami.getGlobalBounds().left <= 0.f)
		this->kolka_z_punktami.setPosition(0.f, this->kolka_z_punktami.getGlobalBounds().top);					//getGlobalBounds odnosi siê do kopii
	//Right
	else if (this->kolka_z_punktami.getGlobalBounds().left + this->kolka_z_punktami.getGlobalBounds().width >= target->getSize().x)								//nie da siê wyjœæ graczem naraz poza lew¹ i praw¹ stronê mapy
		this->kolka_z_punktami.setPosition(target->getSize().x - this->kolka_z_punktami.getGlobalBounds().width, this->kolka_z_punktami.getGlobalBounds().top);				//pozorne sprawdzanie prawej strony, "+" po to, ¿eby wzi¹æ szerokoœæ gracza. Inaczej zatrzyma³oby siê dopiero wtedy kiedy lewa krawêdŸ gracza wyjdzie poza mapê
	//Top
	if (this->kolka_z_punktami.getGlobalBounds().top <= 0.f)
		this->kolka_z_punktami.setPosition(this->kolka_z_punktami.getGlobalBounds().left, 0.f);
	//Bottom
	else if (this->kolka_z_punktami.getGlobalBounds().top + this->kolka_z_punktami.getGlobalBounds().height >= target->getSize().y)							//ponownie pozorne sprawdzanie do³u mapy, poniewa¿ znowu gracz zatrzyma³by siê jak górna krawêdŸ dotknie granicy mapy
		this->kolka_z_punktami.setPosition(this->kolka_z_punktami.getGlobalBounds().left, target->getSize().y - this->kolka_z_punktami.getGlobalBounds().height);		
}

void Player::update(const sf::RenderTarget* target)
{
	this->updateInput();

	//Window bounds collision
	this->updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget * target)
{
	target->draw(this->kolka_z_punktami);
}
