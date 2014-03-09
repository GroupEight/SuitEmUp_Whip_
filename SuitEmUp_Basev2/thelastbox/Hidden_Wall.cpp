#include "Hidden_Wall.hpp"
#include <iostream>

#include "TextureMan.h"

Hidden_Wall::Hidden_Wall(TextureMan *p_xpTextMan, b2World *_bWorld)
: mBWorld( _bWorld )
, mWalls( sf::TrianglesStrip, 300 )
, mRope1( sf::TrianglesStrip, 4 )
, mRope2( sf::TrianglesStrip, 4 )
, mParallax( 0.2 )
, mWallWidth( 450.f )
, mWallSlide( -90 * 3.141592 / 180 )
, mState( Hidden_Wall::State::closed ){
	m_xpTex = p_xpTextMan->Get("Hidden_Wall");
	m_xpTex->setRepeated( true );
	m_xpTex->setSmooth( true );

	m_xpRTex = p_xpTextMan->Get("Rope");
	m_xpRTex->setRepeated( true );
	m_xpRTex->setSmooth( true );
}

void Hidden_Wall::CreateCollision(){

	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody; //this will be a dynamic body
	myBodyDef.angle = 0; //set the starting angle
	
	mBBody = mBWorld->CreateBody(&myBodyDef);
	mBBody->SetTransform( b2Vec2( getWorldPosition().x / 32.f, (getWorldPosition().y - 100.f) / 32.f ), 0.f );

	b2PolygonShape mBShape;
	mBShape.SetAsBox( 1, mWallWidth / 2.f / 32.f );
	
	b2FixtureDef mBFixtureDef;
	mBFixtureDef.shape = &mBShape;
	mBBody->CreateFixture(&mBFixtureDef);
}

void Hidden_Wall::PlaceWallVertices(){
	float distanceBetweenPoints = 0;
	float wallHeight = 200.f;
	int resolution = 100;
	float frequency = 4.f;

	int q = 0;

	for(int i = 0; i<=resolution; i++)
	{

		mWalls[q].position = sf::Vector2f( ((mWallWidth/resolution * i) - ( mWallWidth/resolution * i * ( sinf( mWallSlide ) + 1.f )/2.5 ) ), sinf( frequency / resolution * (360.f * 3.141592f / 180.f) * i ) * ( ( sinf( mWallSlide ) + 1.2f )/2.f ) * -(mWallWidth/frequency/3.f) );

		//float camDistance = sqrt( ( (controlVertices[i].position.x - cPos.x) * (controlVertices[i].position.x - cPos.x) ) + ( (controlVertices[i].position.y - cPos.y) * (controlVertices[i].position.y - cPos.y) ) );
		float camDistanceX = (getWorldPosition().x + mWalls[q].position.x ) - cPos.y;
		float camDistanceY = (getWorldPosition().y + mWalls[q].position.y ) + cPos.x;
		

		//POSITION
		mWalls[q+1].position = sf::Vector2f( mParallax * camDistanceX + mWalls[q].position.x + 100.f, mParallax * camDistanceY + mWalls[q].position.y + wallHeight );

		
		//TEX-COORDS
		mWalls[q].texCoords = sf::Vector2f( m_xpTex->getSize().x / resolution * i, m_xpTex->getSize().y );
		mWalls[q+1].texCoords = sf::Vector2f(m_xpTex->getSize().x / resolution * i, 0 );
		

		q+=2;
	}

	//Fix for weird extra vertex added
	mWalls[q].position = mWalls[q-1].position;
	mWalls[q].texCoords = mWalls[q-1].texCoords;

	//ROPE 1
	mRope1[0].position = sf::Vector2f( mWalls[1].position.x, mWalls[1].position.y + 4 );
	mRope1[1].position = sf::Vector2f( mWalls[1].position.x, mWalls[1].position.y - 4 );
	mRope1[2].position = sf::Vector2f( mWalls[q].position.x, mWalls[q].position.y + 4 );
	mRope1[3].position = sf::Vector2f( mWalls[q].position.x, mWalls[q].position.y - 4 );
	
	mRope1[0].texCoords = sf::Vector2f( mRope1[2].position.x, m_xpRTex->getSize().y );
	mRope1[1].texCoords = sf::Vector2f( mRope1[2].position.x, 0 );
	mRope1[2].texCoords = sf::Vector2f( mRope1[0].position.x, m_xpRTex->getSize().y );
	mRope1[3].texCoords = sf::Vector2f( mRope1[0].position.x, 0 );

	//ROPE 2
	mRope2[0].position = sf::Vector2f( mWalls[0].position.x, mWalls[0].position.y + 3 );
	mRope2[1].position = sf::Vector2f( mWalls[0].position.x, mWalls[0].position.y - 3 );
	mRope2[2].position = sf::Vector2f( mWalls[q-2].position.x, 3 );
	mRope2[3].position = sf::Vector2f( mWalls[q-2].position.x, -3 );

	mRope2[0].texCoords = sf::Vector2f( mRope2[2].position.x, m_xpRTex->getSize().y );
	mRope2[1].texCoords = sf::Vector2f( mRope2[2].position.x, 0 );
	mRope2[2].texCoords = sf::Vector2f( mRope2[0].position.x, m_xpRTex->getSize().y );
	mRope2[3].texCoords = sf::Vector2f( mRope2[0].position.x, 0 );

	//Collision

	//mBBody->SetTransform( b2Vec2( mBBody->GetPosition().x, (getWorldPosition().y + mWalls[q-2].position.y) / 32.f  ), 0.f );
	
}

void Hidden_Wall::SetState( Hidden_Wall::State state ){
	if(mState != state){
		mState = state;
	}
}

Hidden_Wall::State Hidden_Wall::getState(){
	return mState;
}

void Hidden_Wall::Update(sf::Time dt){
	PlaceWallVertices();

	switch (mState)
	{
	case Hidden_Wall::closed:
		//mWallSlide = -90.f * 3.141592 / 180;
		break;
	case Hidden_Wall::opening:
		mWallSlide += (360.f * dt.asSeconds() * 3.141592 / 180) / 0.5f;
		if(mWallSlide > (90.f * 3.141592 / 180)){
			mState = State::open;
		}
		break;
	case Hidden_Wall::open:
		//mWallSlide = 90.f * 3.141592 / 180;
		break;
	case Hidden_Wall::closing:
		mWallSlide -= (360.f * dt.asSeconds() * 3.141592 / 180) / 0.5f;
		if(mWallSlide < (-90.f * 3.141592 / 180)){
			mState = State::closed;
		}
		break;
	}
}

void Hidden_Wall::SetCameraPos( sf::Vector2f pos ){
	cPos = pos;
}

void Hidden_Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	//glEnable( GL_CULL_FACE );

	states.texture = m_xpRTex;
	target.draw( mRope2, states );

	states.texture = m_xpTex;
	target.draw( mWalls, states );

	states.texture = m_xpRTex;
	target.draw( mRope1, states );

	//glDisable( GL_CULL_FACE );
}