//Game.cpp//

#include "Game.hpp"

#include <windows.h>

#include "CollisionMan.h"
#include "FontMan.h"
#include "NodeMan.h"
#include "SoundPlayer.hpp"
#include "Stateman.h"
#include "TextureMan.h"

#include "CursorObject.h"
#include "Ground.hpp"
#include "PlayerObject.h"

#include "Gamestate.hpp"
#include "Menustate.h"

Game::Game(){
	m_xpStateman = NULL;
	m_xpCollisionMan = NULL;
	m_xpTextMan = NULL;

	m_xpPBulletman = NULL;
	m_xpEBulletman = NULL;
	m_xpEnemyMan = NULL;

	m_xpGround = NULL;
	m_xpPlayer = NULL;

	m_xpGamestate = NULL;
	m_xpMenustate = NULL;

	//m_xpWorld = NULL;
}

/*Game::Game( sf::ContextSettings settings )
	: mWindow(sf::VideoMode(1280, 720), "World", sf::Style::Close, settings)
, mStateMan( StateManager::States::InGame )
, mWorld(mWindow)
, mPMenu(mWindow, mStateMan)
, mMPlayer()
, mFont()
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
, mGrain( mWindow){
	mFont.loadFromFile("../rec/Fonts/LITTLELO.TTF");
	/*mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setColor( sf::Color::White );
	mStatisticsText.setCharacterSize(40);

	mCursorTex.loadFromFile( "../rec/Graphics/Mouse_Cursor.png" );
	mCursor.setTexture( mCursorTex );
	mCursor.setOrigin( mCursor.getLocalBounds().width / 2.f, mCursor.getLocalBounds().height / 2.f );

	mHealthBarTex.loadFromFile( "../rec/Graphics/Health_Bar.png" );
	mHealthBarTex.setSmooth( true );
	mHealthBar.setTexture( mHealthBarTex );
}*/

bool Game::Init(){
	m_iWi = 1920;
	m_iHe = 1080;

	m_xDtime = sf::Time::Zero;
	m_xFps = sf::seconds(1.f / 60.f);

	INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

	int q = MessageBox(NULL, L"Play game in Fullscreen?", L"Suit Em Up (Name not final)", MB_YESNO | MB_ICONQUESTION);

	if (q == 6){
		m_xpWindow = new sf::RenderWindow(sf::VideoMode(m_iWi, m_iHe, 32), "Suit Em Up (Name not final)", sf::Style::Fullscreen);
		m_xpWindow->setPosition(sf::Vector2i(0, 0));
	}
	else if (q == 7){
		m_xpWindow = new sf::RenderWindow(sf::VideoMode(m_iWi, m_iHe, 32), "Suit Em Up (Name not final)", sf::Style::Resize | sf::Style::Close);
	}
	else {
		return false;
	}

	if (m_xpWindow == NULL){
		return false;
	}

	m_xpStateman = new Stateman;
	if (m_xpStateman == NULL){
		return false;
	}
	
	m_xpCollisionMan = new CollisionMan();
	if (m_xpCollisionMan == NULL){
		return false;
	}

	m_xpTextMan = new TextureMan("../rec/");
	if (m_xpTextMan == NULL){
		return false;
	}
	LoadTexts(m_xpTextMan);

	m_xpFontMan = new FontMan("../rec/Fonts/");
	if (m_xpFontMan == NULL){
		return false;
	}
	m_xpFontMan->Load("LITTLELO.TTF", "Standard");

	m_xpSPlayer = new SoundPlayer("../rec/Sounds/");
	if (m_xpSPlayer == NULL){
		return false;
	}
	LoadSounds();

	m_xpPBulletman = new NodeMan;
	if (m_xpPBulletman == NULL){
		return false;
	}

		m_xpEBulletman = new NodeMan;
	if (m_xpEBulletman == NULL) {
		return false;
	}

	m_xpEnemyMan = new NodeMan;
	if (m_xpEnemyMan == NULL) {
		return false;
	}

	m_xpPlayer = new PlayerObject(m_xpWindow, m_xpCollisionMan, m_xpPBulletman, m_xpEnemyMan, m_xpTextMan);
	if (m_xpPlayer == NULL){
		return false;
	}

	m_xpGround = new Ground(m_xpTextMan, sf::Vector2f(1024, 720), m_xpPlayer, m_xpWindow);
	if (m_xpGround == NULL){
		return false;
	}

	m_xpCursor = new CursorObject(m_xpTextMan, m_xpWindow);
	if (m_xpCursor == NULL){
		return false;
	}

	m_xpGamestate = new Gamestate(m_xpWindow, m_xpCollisionMan, m_xpTextMan, m_xpPBulletman, m_xpEBulletman, m_xpEnemyMan, m_xpPlayer, m_xpCursor, m_xpGround);
	if (m_xpGamestate == NULL){
		return false;
	}

	m_xpMenustate = new Menustate(m_xpWindow, m_xpTextMan, m_xpFontMan, m_xpSPlayer);
	if (m_xpMenustate == NULL){
		return false;
	}

	m_xpStateman->Add(m_xpGamestate);
	m_xpStateman->Add(m_xpMenustate);

	m_xpStateman->Setstate("Menustate");

	return true;
}

void Game::Run(){
	//Start inital music
	//mMPlayer.play( Music::InGameTheme );

	//totalTime = 0;

	//Hide default mouse cursor
	/*

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (m_xpWindow->isOpen()){
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame){
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);

		}

		updateStatistics(elapsedTime);
		render();
	}*/
	m_xpClock = new sf::Clock;
	m_xpClock->restart();

	//m_xpWindow->setMouseCursorVisible(false);

	while (m_xpStateman->IsRunning()){
		UpdEvents();

		if (UpdateDeltaTime()){
			m_xpWindow->clear(sf::Color::White);
			
			m_xpStateman->Update(m_xDtime);
			m_xpStateman->Draw();

			m_xpWindow->display();

			m_xDtime = sf::Time::Zero;
		}
	}
}

void Game::Cleanup(){
	if (m_xpWindow != NULL){
		delete m_xpWindow;
		m_xpWindow = NULL;
	}
	if (m_xpClock != NULL){
		delete m_xpClock;
		m_xpClock = NULL;
	}
	if (m_xpStateman != NULL){
		delete m_xpStateman;
		m_xpStateman = NULL;
	}
	if (m_xpCollisionMan != NULL){
		delete m_xpCollisionMan;
		m_xpCollisionMan = NULL;
	}
	if (m_xpTextMan != NULL){
		delete m_xpTextMan;
		m_xpTextMan = NULL;
	}
}

bool Game::UpdateDeltaTime(){
	m_xDtime += m_xpClock->restart();

	//std::cout << (float)m_xDtime.asMilliseconds() << std::endl;

	if (m_xDtime >= m_xFps){
		//m_xDtime = m_xFps;

		return true;
	}
	return false;
}

void Game::UpdEvents(){
	sf::Event event;
	while (m_xpWindow->pollEvent(event)){
		switch (event.type){
			case sf::Event::Closed:
				m_xpWindow->close();
				m_xpStateman->Quit();
				break;
		}
	}
}

void Game::LoadTexts(TextureMan *p_xpTextMan){
	//Player
	p_xpTextMan->Load("Graphics/Player_Anim/Player_Anim_Idle.png", "Player_Idle");
	p_xpTextMan->Load("Graphics/Player_Anim/Player_Anim_Run.png", "Player_Run");
	p_xpTextMan->Load("Graphics/Player_Anim/Player_Anim_Sidestep.png", "Player_Side_Step");
	p_xpTextMan->Load("Graphics/Player_Glove_Empty.png", "Player_Glove_Empty");

	//Warrior
	p_xpTextMan->Load("Graphics/Enemy/Warrior/Idle_Animation.png", "Warrior_Idle");
	p_xpTextMan->Load("Graphics/Enemy/Warrior/Run_Animation.png", "Warrior_Run");
	p_xpTextMan->Load("Graphics/Enemy/Warrior/Attack_Animation.png", "Warrior_Atk");

	//Tools
	p_xpTextMan->Load("Graphics/Bullet_Player.png", "Player_Bullet");
	p_xpTextMan->Load("Graphics/Ranged_Crossbow_Fire.png", "Crossbow");

	//Backgrounds
	p_xpTextMan->Load("Graphics/Ground.png", "Ground");
	p_xpTextMan->Load("Graphics/Wall_Test.png", "Wall");
	p_xpTextMan->Load("Graphics/Hidden_Wall.png", "Hidden_Wall");


	//Particles
	p_xpTextMan->Load("Graphics/Particles/Star_Part_01.png", "Star");

	//Extras
	p_xpTextMan->Load("Graphics/Shadow.png", "Shadow");
	p_xpTextMan->Load("Graphics/Shadow_Bump.png", "Shadow_Bump");
	p_xpTextMan->Load("Graphics/Rope_Tex.png", "Rope");
	p_xpTextMan->Load("Graphics/Rope_End.png", "Rope_End");

	//
	p_xpTextMan->Load("Graphics/GUI/Prompt_Frame.png", "Prompt_Frame");
	p_xpTextMan->Load("Graphics/GUI/Pause_BG.png", "Pause_Bg");
	p_xpTextMan->Load("Graphics/GUI/Button_1_Center.png", "Button1_Center");
	p_xpTextMan->Load("Graphics/GUI/Button_1_End.png", "Button1_End");
	p_xpTextMan->Load("Graphics/Mouse_Cursor.png", "Mouse_Cursor");
	p_xpTextMan->Load("Graphics/Health_Bar.png", "Health_Bar");
}

void Game::LoadSounds(){
	m_xpSPlayer->Load("Button_Click.wav", "Button_Click");
	m_xpSPlayer->Load("Button_Hover.wav", "Button_Hover");
	m_xpSPlayer->Load("Cymbal_Hit_01.wav", "Cymbal_Hit1");
	m_xpSPlayer->Load("Cymbal_Hit_02.wav", "Cymbal_Hit1");
	m_xpSPlayer->Load("Cymbal_Hit_03.wav", "Cymbal_Hit1");
}