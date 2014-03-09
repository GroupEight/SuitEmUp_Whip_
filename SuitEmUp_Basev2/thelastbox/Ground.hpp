//Ground.h//

#pragma once

#include "GameObject.h"

class PlayerObject;

class TextureMan;

class Ground : public GameObject {
public:
	Ground(TextureMan *p_xpTextMan, sf::Vector2f size, PlayerObject *p_xpPlayer, sf::RenderWindow *p_xpWindow);
	
	void UpdateTexCoords(sf::Vector2f position);

	sf::VertexArray m_xVertArray;

	virtual void Update(sf::Time dt);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	float m_fHeight;
	float m_fWidth;

	PlayerObject *m_xpPlayer;

	sf::RenderWindow *m_xpWindow;

	sf::Texture *m_xpTex;
};