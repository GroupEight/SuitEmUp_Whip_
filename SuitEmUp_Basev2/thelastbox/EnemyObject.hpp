//EnemyObject.h//

#pragma once

#include "GameObject.h"

class CollisionMan;
class TextureMan;

class PlayerObject;

class Animation;

class EnemyObject : public GameObject {
public:
	enum AIState {
		Passive,
		Aggro,
		Attacking,
	};

public:
	EnemyObject(CollisionMan *p_xpCollisionMan, TextureMan *p_xpTexMan, float p_fAggroRange, float p_fAttackRange, sf::Vector2f p_xStartpos, PlayerObject *p_xpPlayer);

	virtual void Update(sf::Time p_xDtime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void SetState(EnemyObject::AIState state);
	EnemyObject::AIState GetState();

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

	EnemyObject::AIState m_eState;

	PlayerObject *m_xpPlayer;

	sf::CircleShape *m_hitradius;

	float m_fAggroRange,
		m_fAttackRange,
		m_fSpd;

	int m_iHp;
};