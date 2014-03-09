//Gamestate.h//

#pragma once

#include <string>

#include "State.h"

class Menu_Button;

class FontMan;
class SoundPlayer;
class TextureMan;

class Menustate : public State {
public:
	Menustate(sf::RenderWindow *p_xpWindow, TextureMan *p_xpTextMan, FontMan *p_xpFontMan, SoundPlayer *p_xpSPlayer);
	~Menustate();

	bool Enter();
	void Exit();
	bool Update(sf::Time p_xDtime);
	void Draw();
	std::string Next();
	bool IsType(const std::string &p_sType);

private:
	sf::RenderWindow *m_xpWindow;

	sf::View *m_xpView;

	Menu_Button *m_xpaButtons[5];
};