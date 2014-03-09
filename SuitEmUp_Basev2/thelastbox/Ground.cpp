//Ground.cpp//

#include "Ground.hpp"

#include "PlayerObject.h"

#include "TextureMan.h"

Ground::Ground(TextureMan *p_xpTextMan, sf::Vector2f size, PlayerObject *p_xpPlayer, sf::RenderWindow *p_xpWindow)
: m_xVertArray(sf::Quads, 100){
	m_xpTex = p_xpTextMan->Get( "Ground" );

	m_xpTex->setRepeated( true );

	m_xpPlayer = p_xpPlayer;

	m_xpWindow = p_xpWindow;

	m_fHeight = m_xpWindow->getSize().y;
	m_fWidth = m_xpWindow->getSize().x;

    int i = 0;

	m_xVertArray[i+0].position = sf::Vector2f( 0, 0 );
	m_xVertArray[i+1].position = sf::Vector2f( 0, m_fHeight );
	m_xVertArray[i+2].position = sf::Vector2f( m_fWidth, 0 );
	m_xVertArray[i+3].position = sf::Vector2f( m_fWidth, m_fHeight );

	//Tex-Coords
	m_xVertArray[i+0].texCoords = sf::Vector2f( 0, 0 );
	m_xVertArray[i+1].texCoords = sf::Vector2f( 0, m_fWidth );
	m_xVertArray[i+2].texCoords = sf::Vector2f( m_fHeight, 0 );
	m_xVertArray[i+3].texCoords = sf::Vector2f( m_fHeight, m_fWidth );
}

void Ground::Update(sf::Time dt){
	float t = 2.f;
	sf::Vector2f l_xPos = sf::Vector2f(m_xpWindow->getView().getCenter());
	sf::Vector2f p_xOffset = sf::Vector2f(m_xpPlayer->getPosition().x / t, m_xpPlayer->getPosition().y / t);

	int i = 0;
	m_xVertArray[i+0].position = sf::Vector2f(l_xPos.x - m_xpWindow->getSize().x, l_xPos.y - m_xpWindow->getSize().y);
	m_xVertArray[i+1].position = sf::Vector2f(l_xPos.x - m_xpWindow->getSize().x, l_xPos.y + m_xpWindow->getSize().y);
	m_xVertArray[i+2].position = sf::Vector2f(l_xPos.x + m_xpWindow->getSize().x, l_xPos.y + m_xpWindow->getSize().y);
	m_xVertArray[i+3].position = sf::Vector2f(l_xPos.x + m_xpWindow->getSize().x, l_xPos.y - m_xpWindow->getSize().y);

	m_xVertArray[i+0].texCoords = sf::Vector2f( 0, m_fHeight ) - p_xOffset;
	m_xVertArray[i+1].texCoords = sf::Vector2f( 0, 0 ) - p_xOffset;
	m_xVertArray[i+2].texCoords = sf::Vector2f( -m_fWidth, 0 ) - p_xOffset;
	m_xVertArray[i+3].texCoords = sf::Vector2f( -m_fWidth, m_fHeight ) - p_xOffset;
}

void Ground::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.texture = m_xpTex;
	target.draw( m_xVertArray, states );
}