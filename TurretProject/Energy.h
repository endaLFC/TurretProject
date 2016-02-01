#pragma once
class Energy
{
public:
	static Energy* GetInstance();
	~Energy();
	void Initialise();
	void Update(float time);
	void Shot1();
	void Draw(sf::RenderWindow &window);
	float GetEnergy() { return energyWidth; }

private:
	Energy()
	{ 
		
	}
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_pos;
	float energyWidth;

	static bool instanceFlag;
	static Energy* instance;
};

