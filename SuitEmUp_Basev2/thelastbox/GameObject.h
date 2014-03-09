//GameObject.h//

#pragma once

#include "SceneNode.hpp"

class SoundPlayer;

class GameObject : public SceneNode {
public:
	GameObject();

	void SetVelocity(sf::Vector2f velocity);
	sf::Vector2f GetVelocity() const;

	void SetPosition(sf::Vector2f p_xPos);
	sf::Vector2f GetPosition();

	void Playsound(int sound);
	void Playsound(std::string p_sCname);

protected:
	b2Body *m_xpBody;

	SoundPlayer	*m_xpSPlayer;

	sf::Vector2f m_xVel;
};