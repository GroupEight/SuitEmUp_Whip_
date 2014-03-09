//Crossbow.h//

#pragma once

#include "GameObject.h"
#include "Animation.hpp"

class Crossbow : public GameObject{
public:
	enum State {
		Idle,
		Active,
		Passive,
	};

public:
	Crossbow( sf::Texture *p_xpTex );

	void setState( Crossbow::State state );
	void setTexture(sf::Texture *p_xpTex);

	Crossbow::State getState();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateCurrent(sf::Time dt);

	Animation *m_xpAnimSprite;
	sf::Texture *m_xpTex;

	Crossbow::State mState;
};