//Particle.h//

#pragma once

#include "GameObject.h"

class Particle : public GameObject {
public:
	Particle(sf::Texture texture, sf::Vector2f velocity, float initRot,float rotRate, sf::Vector2f initScale, sf::Vector2f scaleRate, int spread, float direction, float lifespan);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	virtual void updateCurrent(sf::Time dt);

	float mRotRate;
	sf::Vector2f mScaleRate;

	int mSpread;
	sf::Vector2f mDir;

	sf::Sprite mSprite;
	sf::Texture	mTex;

public:
	float mLifespan;
	float mLifeTimer;
};

