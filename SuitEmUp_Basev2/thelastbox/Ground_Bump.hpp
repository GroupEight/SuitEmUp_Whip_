#pragma once

#include "GameObject.h"

class Ground_Bump : public GameObject {
public:
	Ground_Bump(sf::Texture p_xGroundTex, sf::Texture p_xShadowTex, bool direction, float radius, GameObject *p_xpTarget);

	void updateTexCoords();

	sf::VertexArray m_xQuads;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void UpdateCurrent(sf::Time p_xDtime);

	sf::Vector2f m_xSize;

	float m_fSubdivs,
		m_fRadius,
		m_fSegDif,
		m_fDistortion;
	
	bool m_bDir;

	GameObject *m_xpTarget;

	sf::Texture m_xTex;
	sf::Texture m_xShadowTex;

	sf::Sprite m_xShadow;
};