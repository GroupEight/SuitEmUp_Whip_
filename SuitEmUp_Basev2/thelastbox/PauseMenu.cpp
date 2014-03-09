//PauseMenu.cpp//

/*#include "PauseMenu.hpp"
#include <Windows.h>
#include <sstream>
#include <typeinfo>

#include <SFML/Graphics/RenderWindow.hpp>

PauseMenu::PauseMenu(sf::RenderWindow *p_xpWindow)
: m_xTextures() 
, m_xSceneGraph() 
, m_xSceneLayers() 
, m_xBG(){
	m_xpWindow = p_xpWindow;

	LoadResources();
	BuildScene();

	m_xBG.setTexture( m_xpTextures->get( Textures::Pause_BG ) );
	m_xBG.setOrigin( m_xBG.getLocalBounds().width / 2.f, m_xBG.getLocalBounds().height / 2.f );
	m_xBG.setPosition( p_xpWindow->getSize().x / 2.f, p_xpWindow->getSize().y / 2.f + 50.f );
}

void PauseMenu::Update(sf::Time dt){
	// Apply movements
	/*mSceneGraph.update(dt);

	if (mQuitPrompt->mState == Prompt::State::btn1) //If "yes" button has been pressed{
		mStateMan->State = StateManager::States::Quit; //Quit application
		mQuitPrompt->mState = Prompt::State::none; //Reset the state
	}
	else if(mQuitPrompt->mState == Prompt::State::btn2){ //If "cancel" button has been presse{
		HideQuitPromp(); //Return to pause screen
		mQuitPrompt->mState = Prompt::State::none; //Reset the state
	}
}

void PauseMenu::draw(){
	m_xpWindow->setView(m_xpWindow->getView());
	m_xpWindow->draw( m_xBG );
	m_xpWindow->draw(m_xSceneGraph);
}

void PauseMenu::LoadResources(){
	//TEXTURES
	
}

void PauseMenu::BuildScene(){
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i){
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	// Add Resume button
	std::unique_ptr<Menu_Button> resumeBtn(new Menu_Button( mTextures, sf::Text( "RESUME", mFonts.get( Fonts::LITTLELO ), 70 ), 4 ) );
	mResumeBtn = resumeBtn.get();
	mResumeBtn->setPosition( mWindow.getSize().x / 2.f, mWindow.getSize().y / 2.f - 20.f );
	mSceneLayers[Main]->attachChild(std::move(resumeBtn));

	// Add Quit button
	std::unique_ptr<Menu_Button> quitBtn(new Menu_Button( mTextures, sf::Text( "QUIT", mFonts.get( Fonts::LITTLELO ), 70 ), 3 ) );
	mQuitBtn = quitBtn.get();
	mQuitBtn->setPosition( mWindow.getSize().x / 2.f, mWindow.getSize().y / 2.f + 110.f );
	mSceneLayers[Main]->attachChild(std::move(quitBtn));

	// Add Quit-prompt
	std::unique_ptr<Prompt> backgroundSprite(new Prompt(mWindow, mTextures, sf::Text( "Are you sure you want to quit?", mFonts.get( Fonts::LITTLELO ), 50 ), sf::Text( "YES", mFonts.get( Fonts::LITTLELO ), 70 ), sf::Text( "CANCEL", mFonts.get( Fonts::LITTLELO ), 70 ) ) );
	mQuitPrompt = backgroundSprite.get();
	mQuitPrompt->setPosition( mWindow.getSize().x / 2.f, mWindow.getSize().y / 2.f + 20.f );
	mSceneLayers[Main]->attachChild(std::move(backgroundSprite));
	mQuitPrompt->hide();
}

void PauseMenu::HandleInput(sf::Event event){
	sf::Vector2i cursorPos = sf::Vector2i( sf::Mouse::getPosition( mWindow ) );

	if( mQuitPrompt->getIsShowing()){
		mQuitPrompt->handleInput(event);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
		if (!mQuitPrompt->getIsShowing() ) //As long as the quit prompt isn't showing{
			if (mResumeBtn->isWithinLocalBounds(cursorPos)){
				if (mResumeBtn->Click()){
					mStateMan->State = StateManager::States::InGame;
					mQuitPrompt->hide();
				}
			}

			if( mQuitBtn->isWithinLocalBounds( cursorPos ) ){
				if( mQuitBtn->Click()){
					showQuitPrompt();
				}
			}
		}
	}

	else if( event.MouseMoved){
		if( !mQuitPrompt->getIsShowing()){ //As long as the quit prompt isn't showing
			//Resume button
			if( mResumeBtn->isWithinLocalBounds(cursorPos)){
				mResumeBtn->Hover();
			}
			else {
				mResumeBtn->Out();
			}

			//Quit button
			if (mQuitBtn->isWithinLocalBounds(cursorPos)){
				mQuitBtn->Hover();
			}
			else {
				mQuitBtn->Out();
			}
		}
	}
}

void PauseMenu::ShowQuitPrompt(){
	mQuitPrompt->show();
	mResumeBtn->hide();
	mQuitBtn->hide();
	mBG.setColor( sf::Color::Transparent );
}

void PauseMenu::HideQuitPromp(){
	mQuitPrompt->hide();
	mResumeBtn->show();
	mQuitBtn->show();
	mBG.setColor(sf::Color::White);
}*/