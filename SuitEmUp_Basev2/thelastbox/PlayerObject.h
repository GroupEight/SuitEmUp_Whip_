//PlayerObject.h//

#pragma once

#include "GameObject.h"

class Animation;
class Player_Arms;
class Tool_Whip;

class CollisionMan;
class NodeMan;
class TextureMan;
class EnemyObject;

class PlayerObject : public GameObject {
public:
	enum State {
		Idle,
		Run_F, 
		Run_B,
		Run_L,
		Run_R,
		Whipping
	};

	enum Tool {
		Melee,
		Crossbow,
		Whip,
	};

public:
	PlayerObject(sf::RenderWindow *p_xpWindow, CollisionMan *p_xpCollisionMan, NodeMan *p_xpBulletMan, NodeMan *p_xpEnemyMan, TextureMan *p_xpTextureMan);
	~PlayerObject();

	virtual void Update(sf::Time p_xDtime);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setState(PlayerObject::State state);
	void setTool(PlayerObject::Tool tool);

	void doWhip(sf::Vector2f _pos);

	PlayerObject::State GetState();
	PlayerObject::Tool GetTool();

	bool m_bColliding;

	bool m_bPunching;

private:

	sf::RenderWindow *m_xpWindow;
	CollisionMan *m_xpCollisionMan;
	NodeMan *m_xpBulletMan;
	NodeMan *m_xpEnemyMan;
	TextureMan *m_xpTextureMan;

	PlayerObject::State m_eState;
	PlayerObject::Tool m_eTool;

	sf::Vector2f lastPosition;

	sf::Sprite mSprite;

	Animation *m_xpIdleAnim,
		*m_xpRunAnim,
		*m_xpStepAnim,
		*m_xpCurrentAnim,
		*m_xpCrossbow;

	Player_Arms *m_xpPlayerArms[2];
	Tool_Whip *m_xpWhip;

	bool punchArm;
	
	float m_fBulletspd,
		m_fPlayerspd,
		m_fFiretime,
		m_fFrate,
		m_fMaxrate,
		m_fHeat,
		m_fHeatup,
		m_fCooldown,
		m_fMaxheat,
		m_fMinheat;

	bool m_bOverheat;

	sf::Vector2f m_xWhipPos;

	sf::Texture *m_xpIdleTex, 
		*m_xpRunTex, 
		*m_xpSStepTex, 
		*m_xpCrossbowTex,
		*m_xpBulletTex;
};