//Scene.h//

#pragma once

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"

#include <array>

class Scene : private sf::NonCopyable{
private:
	enum Layer{
		Main,
		LayerCount
	};

public:
Scene(sf::RenderWindow& window);
	void update(sf::Time dt);
	void draw();

	sf::RenderWindow *m_xWindow;
	sf::View mWorldView;
//	TextureHolder mTextures;

	std::array<SceneNode*, LayerCount> mSceneLayers;

private:
	void loadTextures();
	void buildScene();		
};