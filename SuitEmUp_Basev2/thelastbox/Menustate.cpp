//Gamestate.cpp//

#include "stdafx.h"

#include "Menustate.h"

#include "Menu_Button.hpp"

#include "FontMan.h"
#include "SoundPlayer.hpp"
#include "TextureMan.h"

Menustate::Menustate(sf::RenderWindow *p_xpWindow, TextureMan *p_xpTextMan, FontMan *p_xpFontMan, SoundPlayer *p_xpSPlayer){
	m_xpWindow = p_xpWindow;

	m_xpView = new sf::View(m_xpWindow->getDefaultView());
	m_xpView->setCenter(m_xpWindow->getSize().x / 2, m_xpWindow->getSize().y / 2);

	m_xpWindow->setView(*m_xpView);

	// Create all of the buttons:

	m_xpaButtons[0] = new Menu_Button(p_xpTextMan, p_xpFontMan, m_xpWindow, p_xpSPlayer, 3.0f, "Start Game", 640, 120);

	m_xpaButtons[1] = new Menu_Button(p_xpTextMan, p_xpFontMan, m_xpWindow, p_xpSPlayer, 3.0f, "How To Play", 640, 240);

	m_xpaButtons[2] = new Menu_Button(p_xpTextMan, p_xpFontMan, m_xpWindow, p_xpSPlayer, 3.0f, "Settings", 640, 360);

	m_xpaButtons[3] = new Menu_Button(p_xpTextMan, p_xpFontMan, m_xpWindow, p_xpSPlayer, 3.0f, "High Score", 640, 480);

	m_xpaButtons[4] = new Menu_Button(p_xpTextMan, p_xpFontMan, m_xpWindow, p_xpSPlayer, 3.0f, "Quit", 640, 600);
}

Menustate::~Menustate(){
	for (int i = 0; i < 5; i++){
		delete m_xpaButtons[i];
		m_xpaButtons[i] = NULL;
	}
}

bool Menustate::Enter(){
	m_xpWindow->setView(*m_xpView);

	return true;
}

void Menustate::Exit(){

}

bool Menustate::Update(sf::Time p_xDtime){
	// Goes through all of the buttons and goes though with their intended functions - This is hardcoded
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
		if (m_xpaButtons[0]->isWithinLocalBounds()){
			if (m_xpaButtons[0]->Click()){
				m_sNext = "Gamestate";
				return false;
			}
		}
		if (m_xpaButtons[1]->isWithinLocalBounds()){
			if (m_xpaButtons[1]->Click()){
				m_sNext = "";
				return false;
			}
		}
		if (m_xpaButtons[2]->isWithinLocalBounds()){
			if (m_xpaButtons[2]->Click()){
				m_sNext = "";
				return false;
			}
		}
		if (m_xpaButtons[3]->isWithinLocalBounds()){
			if (m_xpaButtons[3]->Click()){
				m_sNext = "";
				return false;
			}
		}
		if (m_xpaButtons[4]->isWithinLocalBounds()){
			if (m_xpaButtons[4]->Click()){
				m_sNext = "";
				return false;
			}
		}
	}
	else {
		for (int i = 0; i < 5; i++){
			if (m_xpaButtons[i]->isWithinLocalBounds()){
				m_xpaButtons[i]->Hover();
			}
			else {
				m_xpaButtons[i]->Out();
			}
		}
	}

	return true;
}

void Menustate::Draw(){
	for (int i = 0; i < 5; i++){
		m_xpaButtons[i]->draw(*m_xpWindow, sf::RenderStates::Default);
	}
}

std::string Menustate::Next(){
	return m_sNext;
}

bool Menustate::IsType(const std::string &p_Type){
	return p_Type.compare("Menustate") == 0;
}