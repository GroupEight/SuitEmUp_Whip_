//EnemyBullet.h//

#pragma once

#include "SceneNode.hpp"

 class PlayerObject;
class TextureMan;



class EnemyBullet : public SceneNode {
public:
	//EnemyBullet(sf::Texture texture);

	EnemyBullet(TextureMan *p_xpTextureMan, sf::Vector2f p_xPos, float p_fRot, PlayerObject *p_xpPlayer);
	~EnemyBullet();

	TextureMan *m_xpTextureMan;

	PlayerObject *m_xpPlayer;



	void Update(sf::Time p_xDtime);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states ) const;

private:
	float m_fSpd;
	sf::Sprite *m_xpSprite;
	sf::Texture *m_xpTex;
};