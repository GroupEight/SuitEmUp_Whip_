//Prompt.h//

#pragma once

#include "SceneNode.hpp"

class Menu_Button;

class FontMan;
class TextureMan;

class Prompt : public SceneNode {
public:
	enum State {
		none,
		btn1,
		btn2
	};

public:
	Prompt(sf::RenderWindow *p_xpWindow, TextureMan *p_xpTextMan, FontMan *p_xpFontMan, sf::Text text);

	virtual void Update(sf::Time p_xDtime);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void handleInput(sf::Event event);

	Prompt::State m_eState;

private:
	sf::RenderWindow *m_xpWindow;

	sf::Sprite *m_xpFrame;
	sf::Texture *m_xpFrameTex;

	sf::Text *m_xpText;

	Menu_Button* m_xpBtn1;
	Menu_Button* m_xpBtn2;
};