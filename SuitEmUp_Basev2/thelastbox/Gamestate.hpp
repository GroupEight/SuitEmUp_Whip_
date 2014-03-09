//Gamestate.h//

#pragma once

#include "State.h"

#include <array>

class FontHolder;
class TextureHolder;

class SoundPlayer;

class CollisionMan;
class NodeMan;
class TextureMan;

class Ground;

class BGObject;
class CursorObject;
class EnemyObject;
class HWallObject;
class Level;
class Menu_Button;
class PlayerObject;
class Prompt;

class Gamestate : public State {
	private:
	enum Layer {
		Background,
		Main,
		HUD,
		LayerCount
	};

	enum SubStates {
		Play,
		Pause,
		Quit
	};

	enum PauseStates {
		State0,
		State1
	};

public:
	Gamestate(sf::RenderWindow *p_xpWindow, CollisionMan *p_xpCollisionMan, TextureMan *p_xpTextMan, NodeMan *p_xpPBulletMan, NodeMan *p_xpEBulletMan, NodeMan *p_xpEnemyMan, PlayerObject *p_xpPlayer, CursorObject *p_xpCursor, Ground *p_xpGround);

	bool Enter();
	void Exit();

	bool Update(sf::Time p_xDtime);

	void Draw();

	std::string Next();

	bool IsType(const std::string &p_sType);

	void Gamestate::LoadResources();

	/*void handleInput(sf::Event event);
	void handleMouseInput(sf::Vector2f _pos);
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
	void buildScene();*/

private:
	// Used everywhere:
	sf::RenderWindow *m_xpWindow;
	sf::View *m_xpWorldView;

	TextureMan *m_xpTextureMan;
	FontHolder *m_xpFonts;
	SoundPlayer *m_xpSPlayer;

	CursorObject *m_xpCursor;
	Ground *m_xpGround;

	Gamestate::SubStates m_eState;

	float m_fMinZoom,
		m_fStrtZoom,
		m_fMaxZoom,
		m_fCurrZoom;

	// Used in Playstate:
	CollisionMan *m_xpCollisionMan;

	PlayerObject *m_xpPlayer;

	sf::Texture *m_xpTex;

	NodeMan *m_xpEnemyMan;
	NodeMan *m_xpEBulletMan;
	NodeMan *m_xpPBulletMan;

	Level* m_xpLevel;
	HWallObject* mHWall;

	sf::FloatRect m_xWorldBounds;
	sf::Vector2f m_xSpawnPosition;

	// Used in Pausestate/Quitstate
	NodeMan *m_xpMenuman;

	Prompt *m_xpQuitPrompt;

	Menu_Button *m_xpResumeBtn;
	Menu_Button *m_xpQuitBtn;

	sf::Sprite *m_xpBG;

	/*Ground_Bump *mGroundBump_Player;
	Ground_Bump *mGroundBump_Test;*/
};