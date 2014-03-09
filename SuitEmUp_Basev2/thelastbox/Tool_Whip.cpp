#include "stdafx.h"
#include "Tool_Whip.hpp"
#include "TextureMan.h"


Tool_Whip::Tool_Whip(TextureMan *p_xpTextureMan)
{
	m_xVerts.setPrimitiveType(sf::TrianglesStrip);
	m_xVerts.resize(40);

	m_xpTex = p_xpTextureMan->Get( "Rope" );
	m_xpTex->setSmooth( true );
	m_xpTex->setRepeated( true );

	m_xpEndTex = p_xpTextureMan->Get( "Rope_End" );
	m_xpEndTex->setSmooth( true );

	m_xpSprite = new sf::Sprite( *m_xpEndTex );
	m_xpSprite->setOrigin( m_xpSprite->getLocalBounds().width/2.f, m_xpSprite->getLocalBounds().height/2.f );

	setState( State::Inactive );
}

Tool_Whip::~Tool_Whip(void)
{
}

void Tool_Whip::setState(Tool_Whip::State state){
	if( m_eState != state ){
		m_eState = state;

		switch (m_eState)
		{
		case Tool_Whip::Inactive:
			break;
		case Tool_Whip::Passive:
			break;
		case Tool_Whip::Swinging:
			break;
		case Tool_Whip::Whipping:
			m_fSwingStart = 0.f;
			break;
		}
	}
}

Tool_Whip::State Tool_Whip::getState(){
	return m_eState;
}

void Tool_Whip::setWhipDistance( float distance ){
	m_fWhipDist = distance;
}

float Tool_Whip::getPt( int n1 , int n2 , float perc ){
    int diff = n2 - n1;

    return n1 + ( diff * perc );
}

void Tool_Whip::Update(sf::Time p_xDtime){
	if( m_eState != State::Inactive ){

		sf::Vector2f cp1 = sf::Vector2f( 0.f, 0.f );
		sf::Vector2f cp2 = sf::Vector2f( 0.f, 0.f );
		sf::Vector2f cp3 = sf::Vector2f( 0.f, 0.f );

		float _y = 0.f;
		float _x = 0.f;
		float _width = 0.f;

		if(m_eState == State::Passive){
			if( m_fSwingStart > 0.f ){
				m_fSwingStart -= p_xDtime.asSeconds() / 0.3f;
			}else{
				setState( State::Inactive );
			}

			m_fSwing -= p_xDtime.asSeconds() / 0.05;

			_y = sinf( m_fSwing ) * 200.f * m_fSwingStart;
			_x = -50.f * m_fSwingStart;
			_width = cosf( m_fSwing ) * 3 + 7.f;

			cp1 = sf::Vector2f( 0.f, 0.f );
			cp2 = sf::Vector2f( -40.f, 0.f);
			cp3 = sf::Vector2f( -20.f + _x, _y );
		}else if(m_eState == State::Swinging){
			if( m_fSwingStart < 1.f ){
				m_fSwingStart += p_xDtime.asSeconds() / 0.3f;
			}

			m_fSwing -= p_xDtime.asSeconds() / 0.05;

			_y = sinf( m_fSwing ) * 200.f * m_fSwingStart;
			_x = -50.f * m_fSwingStart;
			_width = cosf( m_fSwing ) * 3 + 7.f;

			cp1 = sf::Vector2f( 0.f, 0.f );
			cp2 = sf::Vector2f( -40.f, 0.f);
			cp3 = sf::Vector2f( -20.f + _x, _y );
		}else if(m_eState == State::Whipping){
			if( m_fSwingStart < 1.f ){
				m_fSwingStart += p_xDtime.asSeconds() / 0.2f;
			}else{
				setState( State::Dragging );
			}

			_width = 10.f;

			cp1 = sf::Vector2f( 0.f, 0.f );
			cp2 = sf::Vector2f( -40.f, m_fWhipDist / 2 * m_fSwingStart );
			cp3 = sf::Vector2f( getOrigin().x, m_fWhipDist * m_fSwingStart );
		}else if(m_eState == State::Dragging){
			_width = 10.f;

			cp1 = sf::Vector2f( 0.f, 0.f );
			cp2 = sf::Vector2f( -40.f, m_fWhipDist / 2 );
			cp3 = sf::Vector2f( getOrigin().x, m_fWhipDist );
		}

		int q = 0;
		float lastX = 0;
		float lastY = 0;

		for( float t = 0 ; t < 1 ; t = t )
		{
			float _color = (150.f + cosf( m_fSwing ) * 100.f) * (1.5f - t);
				// The interpolation Line
			float xa = getPt( cp1.x , cp2.x , t );
			float ya = getPt( cp1.y , cp2.y , t );
			float xb = getPt( cp2.x , cp3.x , t );
			float yb = getPt( cp2.y , cp3.y , t );
				// The resulting position
			float x = getPt( xa , xb , t );
			float y = getPt( ya , yb , t );
				//Determine angle
			float a = (90.f * 3.141592 / 180) + atan2f( (y - lastY), (x - lastX) );
				//Add vertices
			m_xVerts[q].position = sf::Vector2f( x + cosf(a) * -_width * (t + 0.5f), y + sinf(a) * -_width * (t + 0.5f));
			m_xVerts[q+1].position = sf::Vector2f( x + cosf(a) * _width * (t + 0.5f), y + sinf(a) * _width * (t + 0.5f) );

			if( m_eState == State::Passive || m_eState == State::Swinging ){
				m_xVerts[q].texCoords = sf::Vector2f( 100.f * t, 0.f);
				m_xVerts[q+1].texCoords = sf::Vector2f( 100.f * t, m_xpTex->getSize().y);

				m_xVerts[q].color = sf::Color( _color, _color, _color, 255.f );
				m_xVerts[q+1].color = sf::Color( _color, _color, _color, 255.f );
			}else if( m_eState == State::Whipping || m_eState == State::Dragging ){
				m_xVerts[q].texCoords = sf::Vector2f( m_fWhipDist * m_fSwingStart * t, 0.f);
				m_xVerts[q+1].texCoords = sf::Vector2f( m_fWhipDist * m_fSwingStart * t, m_xpTex->getSize().y);

				m_xVerts[q].color = sf::Color::White;
				m_xVerts[q+1].color = sf::Color::White;
			}

			q+=2;
			lastX = x;
			lastY = y;

			m_xpSprite->setPosition( x, y );
			m_xpSprite->setRotation( -90 + a * 180 / 3.141592 );
			m_xpSprite->setScale( cosf( m_fSwing ) * 0.5f + 0.8f * m_fSwingStart, cosf( m_fSwing ) * 0.5f + 0.8f * m_fSwingStart );
			m_xpSprite->setColor( sf::Color( _color, _color, _color, 255.f ) );

			t += 0.05f;
		}

	}
}

void Tool_Whip::draw(sf::RenderTarget& target, sf::RenderStates states) const{

	states.transform *= getTransform();

	if( m_eState != State::Inactive ){
		states.texture = m_xpTex;
		target.draw( m_xVerts, states );

		states.texture = nullptr;
		target.draw( *m_xpSprite, states );
	}
}
