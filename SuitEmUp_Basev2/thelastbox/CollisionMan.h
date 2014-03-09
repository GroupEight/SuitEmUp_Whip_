//CollisionMan.h//

#pragma once

class CollisionMan {
public:
	CollisionMan();
	~CollisionMan();

	void Update(sf::Time p_xDtime);

	b2Body *GetNewBody(sf::Vector2f p_xPos, float p_fRadius, int p_iDensity);

	b2World *GetWorld();

private:
	b2World *m_xpThisWorld;

	std::vector<b2Body*> m_xaDefs;
};