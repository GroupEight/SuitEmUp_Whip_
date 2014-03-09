#include "Film_Grain.hpp"


Film_Grain::Film_Grain(sf::RenderWindow& window)
	: mVertices( sf::Quads, 4 )
	, mWindow(window)
{
	mTex.loadFromFile( "../rec/Graphics/Film_Grain.png" );
	mTex.setRepeated( true );

	mVertices[0].position = sf::Vector2f( 0, 0 );
	mVertices[1].position = sf::Vector2f( 0, window.getSize().y );
	mVertices[2].position = sf::Vector2f( window.getSize().x, window.getSize().y );
	mVertices[3].position = sf::Vector2f( window.getSize().x, 0 );

	mVertices[0].texCoords = sf::Vector2f( 0, 0 );
	mVertices[1].texCoords = sf::Vector2f( 0, window.getSize().y );
	mVertices[2].texCoords = sf::Vector2f( window.getSize().x, window.getSize().y );
	mVertices[3].texCoords = sf::Vector2f( window.getSize().x, 0 );
}

void Film_Grain::updateCurrent(sf::Time dt)
{
	float dx = rand() % 5000;
	float dy = rand() % 2000;

	mVertices[0].texCoords = sf::Vector2f( dx, dy );
	mVertices[1].texCoords = sf::Vector2f( dx, dy + mWindow.getSize().y );
	mVertices[2].texCoords = sf::Vector2f( dx + mWindow.getSize().x, dy + mWindow.getSize().y );
	mVertices[3].texCoords = sf::Vector2f( dx + mWindow.getSize().x, dy );
}

void Film_Grain::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &mTex;
	target.draw( mVertices, states );
}