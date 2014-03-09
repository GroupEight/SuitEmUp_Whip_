//Menu_Button.h//

#pragma once

#include "GameObject.h"

class FontMan;
class TextureMan;
class SoundPlayer;

class Menu_Button : public GameObject {
public:
	enum state {
		hover,
		out,
		down,
		click,
	};

public:
	Menu_Button(TextureMan *p_xpTextMan, FontMan *p_xpFontMan, sf::RenderWindow *p_xpWindow, SoundPlayer *p_xpSPlayer, float p_fWidth, std::string p_sText, float p_fX, float p_fY);

	virtual void Update(sf::Time p_xDtime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool isWithinLocalBounds();

	void Hover();
	void Out();
	void Down();
	bool Click();

private:

	sf::Sprite m_xCenter, 
		m_xEnd1,
		m_xEnd2;

	sf::Texture *m_xpCenterTex, 
		*m_xpEndTex;

	SoundPlayer *m_xpSPlayer;

	sf::Text m_xTitle;

	Menu_Button::state m_xState;

	sf::RenderWindow *m_xpWindow;
};