#pragma once
#include "scenenode.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"
#include "SFML\Graphics.hpp"

class Film_Grain :
	public SceneNode
{
public:
									Film_Grain(sf::RenderWindow& window);

private:
	virtual void					drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void					updateCurrent(sf::Time dt);

	sf::RenderWindow&				mWindow;

	sf::VertexArray					mVertices;
	sf::Texture						mTex;
};