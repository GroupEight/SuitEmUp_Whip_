//PauseMenu.h//

/*#pragma once

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

#include <array>

class SceneNode;
class Menu_Button;
class Prompt;

class PauseMenu {
private:
	enum MouseEvent {
		hover,
		down,
		click
	};

public:
	PauseMenu(sf::RenderWindow *p_xpWindow);

	void Update(sf::Time dt);
	void draw();

	void HandleInput(sf::Event event);
	void HandleMouseInput(sf::Vector2f position);

private:
	void LoadResources();
	void BuildScene();
	void ShowQuitPrompt();
	void HideQuitPromp();

private:
	enum Layer{
		Main,
		LayerCount
	};

private:
	sf::RenderWindow *m_xpWindow;
	sf::View m_xWorldView;
	//StateManager *mStateMan;
	TextureHolder *m_xpTextures;
	FontHolder *m_xpFonts;

	std::array<SceneNode*, LayerCount>	mSceneLayers;

	Prompt *m_xQuitPrompt;
	sf::Sprite m_xBG;
	Menu_Button *m_xResumeBtn;
	Menu_Button *m_xQuitBtn;
};*/