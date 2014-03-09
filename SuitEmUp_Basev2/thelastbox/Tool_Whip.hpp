#pragma once
#include "scenenode.hpp"

class TextureMan;

class Tool_Whip :
	public SceneNode
{
public:
	enum State{
		Inactive,
		Passive,
		Swinging,
		Whipping,
		Dragging,
	};

public:
	Tool_Whip(TextureMan *p_xpTextureMan);
	~Tool_Whip(void);

	virtual void Update(sf::Time p_xDtime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void							setState(Tool_Whip::State state);
	Tool_Whip::State				getState();

	void							setWhipDistance(float distance);

private:
	float							getPt( int n1 , int n2 , float perc );


	TextureMan*						m_xpTexMan;

	sf::Texture						*m_xpTex, *m_xpEndTex;

	sf::VertexArray					m_xVerts;

	sf::Sprite*						m_xpSprite;

	Tool_Whip::State				m_eState;

	float							m_fSwing, m_fSwingStart, m_fWhipDist;
};

