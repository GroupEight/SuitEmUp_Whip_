//Level.h//

#pragma once

#include <vector>

#include "SceneNode.hpp"

class CollisionMan;
class NodeMan;
class TextureMan;

class PlayerObject;

class Wall {
public:
	Wall(sf::Vector2f p_xPos, float p_fAng = 0, float p_fHe = 0);

	sf::Vector2f m_xPos;

	float m_fAng, m_fHe;
};

class Level : public SceneNode {
public:
	Level(std::string p_sDir, TextureMan *p_xpTextMan, CollisionMan *p_xpCMan, NodeMan *p_xpEnemyMan, PlayerObject *p_xpPlayer);
	~Level();

	virtual void Update(sf::Time dt);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool LoadLevel(std::string p_sFile);
	void ClearLevel();

	void placeWallVertices();
	void MakeWalls();

	void setCameraPos( sf::Vector2f pos );
	sf::Vector2f getControlVertexPos( int index );

private:
	//void createControlVertex(sf::Vector2f _pos, float _ang = 0.f, float _height = 0.f);

	b2Vec2 *vs;

	b2Body *m_xpLevelBody;

	std::vector<Wall*> m_xaWalls;

	CollisionMan *m_xpCMan;
	NodeMan *m_xpEnemyMan;
	TextureMan *m_xpTexMan;

	PlayerObject *m_xpPlayer;

	int v;

	sf::Vector2f cPos;
	float mParallax;

	sf::VertexArray m_xWalls,
		m_xRoof,
		m_xCVertices,
		m_xCVertexSpec;

	sf::Texture *m_xpTex;

	std::string m_sDir;
};