//Morker.h//

#pragma once

#include "GameObject.h"
#include "Gamestate.hpp"

//class Gamestate;



class CollisionMan;
class TextureMan;

class PlayerObject;

class Animation;

class EnemyBullet;

class Morker : public GameObject {
public:
	enum AIState {
		Passive,
		Aggro,
		Attacking,
	};

public:
	Morker(CollisionMan *p_xpCollisionMan, TextureMan *p_xpTexMan, float p_fAggroRange, float p_fAttackRange, sf::Vector2f p_xStartpos, PlayerObject *p_xpPlayer, NodeMan *p_xpEBulletMan, sf::Texture *p_xpTex);

	virtual void Update(sf::Time p_xDtime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void SetState(Morker::AIState state);
	Morker::AIState GetState();

	NodeMan *m_xpEBulletMan;

	

	TextureMan *m_xpTextureMan;

	sf::Texture *m_xpTex;

	float GetAggroRange();
	float GetAttackRange();

private:
	Animation *m_xpIdleAnim, 
		*m_xpRunAnim, 
		*m_xpAtkAnim,
		*m_xpCurrentAnim;

	sf::Texture *m_xpIdleTex, 
		*m_xpRunTex, 
		*m_xpAtkTex;

	Morker::AIState m_eState;

	PlayerObject *m_xpPlayer;

	

	//Gamestate *m_xpGamestate;

	

	float m_fAggroRange,
		m_fAttackRange,
		m_fSpd,
		m_fFirerate,
		m_fzigzag;

	EnemyBullet *m_xpEBullet;

	int m_iHp;
};