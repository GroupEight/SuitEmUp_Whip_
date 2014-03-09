//Ground_Bump.cpp//

#include "Ground_Bump.hpp"

#include <sstream>
#include <typeinfo>

Ground_Bump::Ground_Bump(sf::Texture p_xGroundTex, sf::Texture p_xShadowTex, bool direction, float radius, GameObject *p_xpTarget)
: m_xQuads ( sf::Quads, 2000 )
, m_xTex ( p_xGroundTex ){
	m_xTex.setRepeated(true);
	m_xTex.setSmooth(true);

	//if (direction == 0){
		m_xShadow.setTexture( p_xShadowTex );
	/*}
	else {
		m_xShadow.setTexture( p_xBumpTex );
	}*/
	m_xShadow.setOrigin( m_xShadow.getLocalBounds().width / 2.f, m_xShadow.getLocalBounds().height / 2.f );

	m_fRadius = radius;
	m_fSubdivs = 20;
	m_fSegDif = m_fRadius/m_fSubdivs;
	m_fDistortion = 5;
	m_bDir = direction;

	int q = 0;
	float l_fQuadAngle = 0.f;

	for (int layer = 0; layer < m_fSubdivs; layer++){
		for (int i = 0; i<=13; i++){
			//Vertices
			m_xQuads[q].position = sf::Vector2f( cosf( l_fQuadAngle )*(layer*m_fSegDif), sinf( l_fQuadAngle )*(layer*m_fSegDif) );
			m_xQuads[q+1].position = sf::Vector2f( cosf( l_fQuadAngle )*(layer*m_fSegDif+m_fSegDif), sinf( l_fQuadAngle )*(layer*m_fSegDif+m_fSegDif) );
			//Tex-Coords
			m_xQuads[q].texCoords = sf::Vector2f( cosf( l_fQuadAngle )*(layer*m_fSegDif), sinf( l_fQuadAngle )*(layer*m_fSegDif) );
			m_xQuads[q+1].texCoords = sf::Vector2f( cosf( l_fQuadAngle )*(layer*m_fSegDif+m_fSegDif), sinf( l_fQuadAngle )*(layer*m_fSegDif+m_fSegDif) );

			l_fQuadAngle += (360/12) * 3.141592 / 180;

			m_xQuads[q+2].position = sf::Vector2f( cosf( l_fQuadAngle )*(layer*m_fSegDif+m_fSegDif), sinf( l_fQuadAngle )*(layer*m_fSegDif+m_fSegDif) );
			m_xQuads[q+3].position = sf::Vector2f( cosf( l_fQuadAngle )*(layer*m_fSegDif), sinf( l_fQuadAngle )*(layer*m_fSegDif) );
			//Tex-Coords
			m_xQuads[q+2].texCoords = sf::Vector2f( cosf( l_fQuadAngle )*(layer*m_fSegDif+m_fSegDif), sinf( l_fQuadAngle )*(layer*m_fSegDif+m_fSegDif) );
			m_xQuads[q+3].texCoords = sf::Vector2f( cosf( l_fQuadAngle )*(layer*m_fSegDif), sinf( l_fQuadAngle )*(layer*m_fSegDif) );

			q+=4;
		}
	}
}

void Ground_Bump::UpdateCurrent(sf::Time p_xDtime){
	//move( m_xVel * p_xDtime.asSeconds() );

	sf::Vector2f _offset = getWorldPosition() + sf::Vector2f( 512.f, 512.f);

	int q = 0;
	float quadAngle = 0.f;
	float sinWave = ( 90 / (m_fSubdivs) ) * 3.141592 / 180;

	float lRad1 = 0.f;
	float lRad2 = 0.f;

	for (int layer = 0; layer <= m_fSubdivs; layer++){
		switch (m_bDir){
		case 0:
			lRad2 = m_fSegDif * (layer+1) / ( sinf( sinWave ) );
			break;
		case 1:
			lRad2 = m_fSegDif * (layer+1) * ( sinf( sinWave ) );
			break;
		}

		for (int i = 0; i<=13; i++){
			m_xQuads[q].texCoords = sf::Vector2f( cosf( quadAngle )*lRad1, sinf( quadAngle )*lRad1 ) + _offset;
			m_xQuads[q+1].texCoords = sf::Vector2f( cosf( quadAngle )*lRad2, sinf( quadAngle )*lRad2 ) + _offset;

			quadAngle+=(360/12) * 3.141592 / 180;

			m_xQuads[q+2].texCoords = sf::Vector2f( cosf( quadAngle )*lRad2, sinf( quadAngle )*lRad2 ) + _offset;
			m_xQuads[q+3].texCoords = sf::Vector2f( cosf( quadAngle )*lRad1, sinf( quadAngle )*lRad1 ) + _offset;

			q+=4;
		}

		lRad1 = lRad2;
		sinWave += ( 90 / (m_fSubdivs) ) * 3.141592 / 180;
	}
}

void Ground_Bump::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.texture = &m_xTex;
	target.draw( m_xQuads, states );
	target.draw ( m_xShadow, states );
}