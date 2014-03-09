//Player_Arms.h//

#pragma once

#include "SceneNode.hpp"

class TextureMan;

class Player_Arms : public SceneNode {
public:
	Player_Arms(TextureMan *p_xpTextMan, int p_iArmDir);

	void setArmsPosition(sf::Vector2f armLength);

	bool Punch();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	void UpdateCurrent(sf::Time p_xDtime);

	int m_iArmDir;

	float m_fPunchLength,
		m_fPunchInterp;

	float GetPt( int n1 , int n2 , float perc );

	bool m_bPunching;

	sf::VertexArray m_xControlVertices,
		m_xArms;

	sf::Texture *m_xpGloveTex;
	sf::Sprite *m_xpGlove;
};