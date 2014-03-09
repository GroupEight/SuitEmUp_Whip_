//Prompt.cpp//

#include "Prompt.hpp"

#include "Menu_Button.hpp"

#include "FontMan.h"
#include "TextureMan.h"

Prompt::Prompt(sf::RenderWindow *p_xpWindow, TextureMan *p_xpTextMan, FontMan *p_xpFontMan, sf::Text p_xText)
: m_eState(State::none){

	m_xpText = &p_xText;

	m_xpFrame->setTexture( *m_xpFrameTex );
	sf::FloatRect bounds = m_xpFrame->getLocalBounds();
	m_xpFrame->setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	m_xpText->setOrigin( m_xpText->getLocalBounds().width / 2.f, m_xpText->getLocalBounds().height / 2.f );
	m_xpText->setPosition( 0.f, -120.f );

	//m_xpBtn1 = new Menu_Button(p_xpTextMan, p_xBtn1Text, 3, "Resume", -170, 0.f);
	//m_xpBtn1->setPosition( -170, 0.f );

	//m_xpBtn2 = new Menu_Button(p_xpTextMan, p_xBtn2Text, 3, "Exit", 170, 0.f);
	//m_xpBtn2->setPosition( 170, 0.f );
}

void Prompt::handleInput(sf::Event event){
	sf::Vector2i cursorPos = sf::Vector2i(sf::Mouse::getPosition(*m_xpWindow));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
		//First button
		if (m_xpBtn1->isWithinLocalBounds()){
			if (m_xpBtn1->Click()){
				m_eState = Prompt::State::btn1;
			}
		}

		//Second button
		if (m_xpBtn2->isWithinLocalBounds()){
			if (m_xpBtn2->Click()){
				m_eState = Prompt::State::btn2;
			}
		}
	}

	else if ( event.MouseMoved){
		//First button
		if ( m_xpBtn1->isWithinLocalBounds()){
			m_xpBtn1->Hover();
		}
		else {
			m_xpBtn1->Out();
		}

		//Second button
		if (m_xpBtn2->isWithinLocalBounds()){
			m_xpBtn2->Hover();
		}
		else {
			m_xpBtn2->Out();
		}
	}
}

void Prompt::Update(sf::Time p_xDtime){

}

void Prompt::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*m_xpFrame, states);
	target.draw(*m_xpText, states);
}