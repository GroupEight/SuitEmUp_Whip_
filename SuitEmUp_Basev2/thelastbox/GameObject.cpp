//GameObject.cpp//

#include "GameObject.h"

#include "SoundPlayer.hpp"

#include <typeinfo>
#include <sstream>

GameObject::GameObject(){

}

void GameObject::SetVelocity(sf::Vector2f velocity){
	m_xVel = m_xVel;
}

sf::Vector2f GameObject::GetVelocity() const {
	return m_xVel;
}

void GameObject::SetPosition(sf::Vector2f p_xPos){
	m_xpBody->GetPosition().x = p_xPos.x;
	m_xpBody->GetPosition().y = p_xPos.y;
}

sf::Vector2f GameObject::GetPosition(){
	return sf::Vector2f(float(m_xpBody->GetPosition().x), float(m_xpBody->GetPosition().y));
}

void GameObject::Playsound( int sound ){
	/*SFX::ID s = static_cast<SFX::ID>(sound);
	m_xpSPlayer->Play(s);*/
}

void GameObject::Playsound( std::string p_sCname ){
	m_xpSPlayer->Play(p_sCname);
}

/*void GameObject::Update(sf::Time p_xDtime){	
	//move(m_xVel * p_xDtime.asSeconds());
	//setPosition(getPosition() + m_xVel);
	//m_xpBody->SetLinearVelocity(b2Vec2(cosf(getRotation()) * 50.0f / 32.0f * (float)p_xDtime.asSeconds(), sin(getRotation()) * 50.0f / 32.0f * (float)p_xDtime.asSeconds()));
	//m_xpBody->GetPosition().Set(m_xpBody->GetPosition().y + m_xVel.y * (float)p_xDtime.asSeconds(), m_xpBody->GetPosition().y + m_xVel.y * (float)p_xDtime.asSeconds());
	m_xpBody->GetPosition().x = m_xpBody->GetPosition().x + m_xVel.x * (float)p_xDtime.asSeconds();
	m_xpBody->GetPosition().y = m_xpBody->GetPosition().y + m_xVel.y * (float)p_xDtime.asSeconds();
}*/