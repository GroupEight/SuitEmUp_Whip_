//Menu_Button.cpp//

#include "Menu_Button.hpp"

#include "FontMan.h"
#include "SoundPlayer.hpp"
#include "TextureMan.h"

Menu_Button::Menu_Button(TextureMan *p_xpTextMan, FontMan *p_xpFontMan, sf::RenderWindow *p_xpWindow, SoundPlayer *p_xpSPlayer, float p_fWidth, std::string p_sText, float p_fX, float p_fY){
	m_xpCenterTex = p_xpTextMan->Get("Button1_Center");
	m_xpEndTex = p_xpTextMan->Get("Button1_End");

	m_xTitle.setFont(*p_xpFontMan->Get("Standard"));

	m_xTitle.setString(p_sText);

	m_xpWindow = p_xpWindow;

	m_xpSPlayer = p_xpSPlayer;

	m_xpCenterTex->setSmooth( true );
	m_xpEndTex->setSmooth( true );

	setPosition(sf::Vector2f(p_fX, p_fY));

	m_xCenter.setTexture( *m_xpCenterTex );
	m_xCenter.setOrigin( m_xCenter.getLocalBounds().width / 2.f, m_xCenter.getLocalBounds().height / 2.f );
	m_xCenter.setScale( p_fWidth, 1 );
	m_xCenter.setPosition(p_fX, p_fY);

	m_xEnd1.setTexture( *m_xpEndTex );
	m_xEnd1.setOrigin( 0, m_xEnd1.getLocalBounds().height / 2.f );
	m_xEnd1.setRotation( 180.f );
	m_xEnd1.setPosition( -m_xCenter.getLocalBounds().width / 2.f * m_xCenter.getScale().x, 0 );
	m_xEnd1.setPosition(p_fX - m_xCenter.getTexture()->getSize().x - (-71.f + 35.5f * p_fWidth), p_fY);

	m_xEnd2.setTexture( *m_xpEndTex );
	m_xEnd2.setOrigin( 0, m_xEnd2.getLocalBounds().height / 2.f );
	m_xEnd2.setPosition( m_xCenter.getLocalBounds().width / 2.f * m_xCenter.getScale().x, 0 );
	m_xEnd2.setPosition(p_fX + m_xCenter.getTexture()->getSize().x + (-71.f + 35.5f * p_fWidth), p_fY);

	m_xTitle.setOrigin( m_xTitle.getLocalBounds().width / 2.f, m_xTitle.getLocalBounds().height / 2.f );
	m_xTitle.setPosition( m_xCenter.getPosition().x, m_xCenter.getPosition().y - 15.f );
}

void Menu_Button::Hover(){
	if (m_xState != state::hover){
		m_xState = state::hover;
		setScale(1.1f, 1.1f);
		m_xpSPlayer->Play("Button_Hover");
	}
}

void Menu_Button::Out(){
	if (m_xState != state::out){
		m_xState = state::out;
		setScale(1.f, 1.f);
	}
}

bool Menu_Button::Click(){
	if (m_xState != state::click){
		m_xState = state::click;
		m_xpSPlayer->Play("Button_Click");
	}

	return true;
}

bool Menu_Button::isWithinLocalBounds(){
	sf::Vector2f l_xSize = sf::Vector2f(m_xCenter.getTextureRect().width + m_xEnd1.getTextureRect().width, m_xCenter.getTextureRect().height / 2);

	// TODO: Make it so that the l_xMouse value is modified depending on if the game is in fullscreen or not

	//if (m_xpWindow->getSettings())
	// Set l_xMouse to the Mouse's position, the reasoning behind this is that the mouse's position is taken from the entire screen as opposed to it's position in the screen
	sf::Vector2f l_xMouse = sf::Vector2f(sf::Mouse::getPosition().x - m_xpWindow->getPosition().x, sf::Mouse::getPosition().y - m_xpWindow->getPosition().y);

	// Check if the mouse is inside the box
	if (m_xCenter.getPosition().x - l_xSize.x < l_xMouse.x && m_xCenter.getPosition().x + l_xSize.x > l_xMouse.x){
		if (m_xCenter.getPosition().y < l_xMouse.y && m_xCenter.getPosition().y + l_xSize.y > l_xMouse.y){
			// Return true if the box is "clicked"
			return true;
		}
	}
	return false;
}

void Menu_Button::Update(sf::Time p_xDtime){

}

void Menu_Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_xEnd1, states);
	target.draw(m_xEnd2, states);
	target.draw(m_xCenter, states);
	target.draw(m_xTitle, states);
}