//PlayerBullet.h//
/*
#pragma once

#include "GameObject.h"

class PlayerBullet : public GameObject {
public:
	//PlayerBullet(sf::Texture texture);
	PlayerBullet(sf::Texture *p_xpTex, sf::Vector2f p_xPos, float p_fRot);
	~PlayerBullet();

	void Update(sf::Time p_xDtime);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states ) const;

private:

	sf::Sprite *m_xpSprite;
	sf::Texture *m_xpTex;
};*/

//PlayerBullet.hpp//

#pragma once

#include "SceneNode.hpp"

 //class PlayerObject;
class TextureMan;

class NodeMan;

class PlayerBullet : public SceneNode {
public:
	//PlayerBullet(sf::Texture texture);

	PlayerBullet(TextureMan *p_xpTextureMan, sf::Vector2f p_xPos, float p_fRot);
	~PlayerBullet();

	TextureMan *m_xpTextureMan;

	//PlayerObject *m_xpPlayer;

	//NodeMan *m_xpEnemyMan;

	void Update(sf::Time p_xDtime);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states ) const;

private:
	float m_fSpd;
	sf::Sprite *m_xpSprite;
	sf::Texture *m_xpTex;
};