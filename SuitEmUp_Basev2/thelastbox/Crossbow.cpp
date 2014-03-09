//Crossbow.cpp//

#include "Crossbow.hpp"

Crossbow::Crossbow( sf::Texture *p_xpTex ){
	m_xpTex->setSmooth( true );

	m_xpAnimSprite->setTexture( m_xpTex );
	m_xpAnimSprite->setRotation( 90 );
	m_xpAnimSprite->setOrigin( m_xpAnimSprite->getFrameSize().x/10, m_xpAnimSprite->getFrameSize().y/2 );
	m_xpAnimSprite->setPosition( 280.f, -90.f );
	m_xpAnimSprite->setReversed( false );
	m_xpAnimSprite->setFrameSize( sf::Vector2i( 178, 291 ) );
	m_xpAnimSprite->setDuration( sf::seconds( 0.4f ) );
	m_xpAnimSprite->setNumFrames( 7 );
	m_xpAnimSprite->setRepeating( true );
	m_xpAnimSprite->setScale( 1.f, 1.f );
}

void Crossbow::setTexture(sf::Texture *p_xpTex){
	m_xpTex = p_xpTex;
}

void Crossbow::setState( Crossbow::State state ){
	if( mState != state ){
		mState = state;
	}
}

Crossbow::State Crossbow::getState(){
	return mState;
}

void Crossbow::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if( mState != State::Passive ){
		target.draw( *m_xpAnimSprite, states );
	}
}

void Crossbow::updateCurrent(sf::Time dt){
	m_xpAnimSprite->setOrigin( m_xpAnimSprite->getFrameSize().x/2, m_xpAnimSprite->getFrameSize().y/2 );
	
	switch (mState){
	case Crossbow::Idle:
		
		break;
	case Crossbow::Active:
		m_xpAnimSprite->update( dt );
		break;
	default:
		break;
	}
}