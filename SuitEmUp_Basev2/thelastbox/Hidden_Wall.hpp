#pragma once

#include "SceneNode.hpp"

class TextureMan;

class Hidden_Wall :
	public SceneNode
{
public:
	enum State
	{
		closed,
		opening,
		open,
		closing,
	};

public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void Update(sf::Time dt);

	Hidden_Wall(TextureMan *p_xpTextMan, b2World *_bWorld);

	void SetCameraPos( sf::Vector2f pos );
	void SetState( Hidden_Wall::State state );
	Hidden_Wall::State getState();

	void CreateCollision();

private:
	void PlaceWallVertices();

	int v;

	//Collision
	b2World* mBWorld;
	b2Body* mBBody;

	sf::Vector2f cPos;

	float mParallax,
		mWallWidth,
		mWallSlide;

	Hidden_Wall::State mState;

	sf::VertexArray mWalls,
		mRope1,
		mRope2;

	sf::Texture *m_xpTex, 
		*m_xpRTex;
};