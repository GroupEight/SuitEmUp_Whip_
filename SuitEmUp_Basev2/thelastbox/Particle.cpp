#include "Particle.hpp"
#include <Windows.h>
#include <sstream>
#include <typeinfo>

Particle::Particle(sf::Texture texture, sf::Vector2f velocity, float initRot,float rotRate, sf::Vector2f initScale, sf::Vector2f scaleRate, int spread, float direction, float lifespan)
	: mTex()
	, mSprite()
	, mSpread( spread )
	, mLifespan( lifespan )
	, mDir( cosf( direction + ( rand() % mSpread ) * 3.1415192 / 180 ),	 sinf( direction + ( rand() % mSpread ) * 3.141592 / 180 ) ){
	mTex = texture;
	mTex.setSmooth( true );
	mSprite.setTexture( mTex );

	mSprite.setOrigin( mSprite.getLocalBounds().width / 2.f, mSprite.getLocalBounds().height / 2.f );

	m_xVel = velocity;
	setRotation( initRot );
	//this->setScale( initScale );
}

void Particle::updateCurrent(sf::Time dt){
	this->move( sf::Vector2f( mDir.x * m_xVel.x, mDir.y * m_xVel.y ) );
	this->rotate( 60.f / 360.f * mRotRate );
}

void Particle::draw(sf::RenderTarget& target, sf::RenderStates states)const{
	target.draw( mSprite, states );
}