//PlayerBullet.cpp//

#include "PlayerBullet.hpp"


#include "NodeMan.h"
#include "TextureMan.h"
#include "PlayerObject.h"


PlayerBullet::PlayerBullet(TextureMan *p_xpTextureMan, sf::Vector2f p_xPos, float p_fRot){
	//std::cout << "SPAWN!!";
	m_xpTextureMan = p_xpTextureMan;
	
	//m_xpPlayer = p_xpPlayer;
	
	//m_xpEnemyMan = p_xpEnemyMan;

	m_xpTex = m_xpTextureMan->Get("Player_Bullet");
	m_xpTex->setSmooth(true);

	m_xpSprite = new sf::Sprite;
	m_xpSprite->setTexture(*m_xpTex);

	m_xPos = p_xPos;

	setPosition(p_xPos);

	m_fSpd = 600.0f;

	//m_xpSprite->setOrigin( 2.f, 2.f );
	m_xpSprite->setScale(1.1,1.1);
	
	
	setRotation(p_fRot);
	
		m_xVel = m_fSpd * sf::Vector2f(cosf((getRotation() + 90.f)* 3.141592 / 180 ), sinf((getRotation() + 90.f)* 3.141592 / 180 ));
	
}

PlayerBullet::~PlayerBullet(){

}

void PlayerBullet::Update(sf::Time p_xDtime){
	m_xpSprite->setRotation(getRotation() + 90 );

	move(m_xVel * p_xDtime.asSeconds());

	//setPosition(getPosition());
	
	m_xpSprite->setPosition(getPosition());
	
	/*for (int i = 0; i < m_xpEnemyMan->GetVector().size(); i++) {

	}*/

}

void PlayerBullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*m_xpSprite, states);
}