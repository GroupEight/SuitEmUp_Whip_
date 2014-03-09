//PlayerObject.cpp//

#include "PlayerObject.h"

#include "PlayerBullet.hpp"

#include "Animation.hpp"
#include "Player_Arms.hpp"
#include "Tool_Whip.hpp"

#include "CollisionMan.h"
#include "NodeMan.h"
#include "TextureMan.h"
#include "EnemyObject.hpp"

PlayerObject::PlayerObject(sf::RenderWindow *p_xpWindow, CollisionMan *p_xpCollisionMan, NodeMan *p_xpBulletMan, NodeMan *p_xpEnemyMan, TextureMan *p_xpTextureMan){

	m_xPos = sf::Vector2f(0, 0);

	m_xpWindow = p_xpWindow;
	m_xpBulletMan = p_xpBulletMan;
	m_xpEnemyMan = p_xpEnemyMan;
	m_xpCollisionMan = p_xpCollisionMan;
	m_xpTextureMan = p_xpTextureMan;

	m_xpBody = p_xpCollisionMan->GetNewBody(sf::Vector2f(m_xPos.x, m_xPos.y), 2.0f, 1);

	m_xpIdleTex = m_xpTextureMan->Get("Player_Idle");
	m_xpRunTex = m_xpTextureMan->Get("Player_Run");
	m_xpSStepTex = m_xpTextureMan->Get("Player_Side_Step");
	m_xpCrossbowTex = m_xpTextureMan->Get("Crossbow");
	m_xpBulletTex = m_xpTextureMan->Get("Player_Bullet");

	//m_xpAnimation = new Animation;

	m_xpIdleAnim = new Animation(m_xpIdleTex);
	m_xpIdleAnim->setReversed( false );
	m_xpIdleAnim->restart();
	m_xpIdleAnim->setFrameSize( sf::Vector2i( 177, 291 ) );
	m_xpIdleAnim->setDuration( sf::seconds( 0.8f ) );
	m_xpIdleAnim->setNumFrames( 12 );
	m_xpIdleAnim->setRepeating( true );
	m_xpIdleAnim->setScale( 1.f, 1.f );

	m_xpRunAnim = new Animation(m_xpRunTex);
	m_xpRunAnim->setReversed( false );
	m_xpRunAnim->restart();
	m_xpRunAnim->setFrameSize( sf::Vector2i( 177, 291 ) );
	m_xpRunAnim->setDuration( sf::seconds( 0.7f ) );
	m_xpRunAnim->setNumFrames( 16 );
	m_xpRunAnim->setRepeating( true );
	m_xpRunAnim->setScale( 0.9f, 0.9f );

	m_xpStepAnim = new Animation(m_xpSStepTex);
	m_xpStepAnim->setReversed( false );
	m_xpStepAnim->restart();
	m_xpStepAnim->setFrameSize( sf::Vector2i( 356, 291 ) );
	m_xpStepAnim->setDuration( sf::seconds( 0.7f ) );
	m_xpStepAnim->setNumFrames( 12 );
	m_xpStepAnim->setRepeating( true );
	m_xpStepAnim->setScale( 1.f, 1.f );

	m_xpCrossbow = new Animation(m_xpCrossbowTex);
	m_xpCrossbow->setRotation( 90 );
	m_xpCrossbow->setReversed( false );
	m_xpCrossbow->setFrameSize( sf::Vector2i( 178, 291 ) );
	m_xpCrossbow->setDuration( sf::seconds( 0.4f ) );
	m_xpCrossbow->setNumFrames( 7 );
	m_xpCrossbow->setRepeating( true );
	m_xpCrossbow->setScale( 1.f, 1.f );
	m_xpCrossbow->setOrigin( m_xpCrossbow->getFrameSize().x/2, m_xpCrossbow->getFrameSize().y );

	

	setState( State::Idle );
	setTool( Tool::Crossbow ); // Start tool

	m_xpPlayerArms[0] = new Player_Arms(m_xpTextureMan, 0);
	m_xpPlayerArms[1] = new Player_Arms(m_xpTextureMan, 0);

	//Whip
	m_xpWhip = new Tool_Whip( m_xpTextureMan );
	m_xpWhip->setOrigin( 50.f, 0.f );

	m_fPlayerspd = 1720.0f; // Players movement speed
	m_fBulletspd = 5.0f; // The speed that the players bullets fly in

	m_fFrate = 1.5f; // How many bullets the player can shoot every second
	m_fMaxrate = 1.0f; // How much a "second" is in the above statement
	m_fFiretime = 0.0f; // How long ago the player fired his weapon

	m_fHeat = 0.0f; // The currrent weapon-heat
	m_fHeatup = 4.0f; // How much the heat increases with every shot
	m_fCooldown = 4.0f; // How much the heat decreases with each passing second
	m_fMaxheat = 25.0f; // When m_fHeat is greater than this the player is rendered unable to shoot
	m_fMinheat = 15.0f; // If the player's weapon is overheated then it has to coll down to this much

	m_xWhipPos = sf::Vector2f( 0.f, 0.f );

	m_bOverheat = false; // Wether the weapon is overheated or not
}

PlayerObject::~PlayerObject(){
	if (m_xpCurrentAnim != NULL){
		delete m_xpCurrentAnim;
		m_xpCurrentAnim = NULL;
	}
	if (m_xpCurrentAnim != NULL){
		delete m_xpCurrentAnim;
		m_xpCurrentAnim = NULL;
	}
	if (m_xpCurrentAnim != NULL){
		delete m_xpCurrentAnim;
		m_xpCurrentAnim = NULL;
	}
	if (m_xpCurrentAnim != NULL){
		delete m_xpCurrentAnim;
		m_xpCurrentAnim = NULL;
	}
	if (m_xpCrossbow != NULL){
		delete m_xpCrossbow;
		m_xpCrossbow = NULL;
	}
}

/*PlayerObject::PlayerObject(const TextureHolder& textures)
	: mSprite ()
	, mRunAnim ( textures.get( Textures::PlayerRun ) )
	, mIdleAnim ( textures.get( Textures::PlayerIdle ) )
	, mSStepAnim ( textures.get( Textures::PlayerSStep ) )
	, mAnimSprite ()
	, mCrossbowTex ( textures.get( Textures::Ranged_Crossbow ) )
	, punchArm (false) //Start with left arm
	, bPunching ( false ){
	mRunAnim.setSmooth( true );
	mIdleAnim.setSmooth( true );
	mSStepAnim.setSmooth( true );
	mCrossbowTex.setSmooth( true );

	setState( State::Idle );
	setTool( Tool::Crossbow ); // Start tool

	m_xpAnimation->setRotation( -90 );
	m_xpAnimation->setOrigin( m_xpAnimation->getFrameSize().x/2, m_xpAnimation->getFrameSize().y/2 );

	mCrossbow.setTexture( mCrossbowTex );
	mCrossbow.setRotation( 90 );
	mCrossbow.setOrigin( mCrossbow.getFrameSize().x/10, mCrossbow.getFrameSize().y/2 );
	mCrossbow.setPosition( 280.f, -90.f );
	mCrossbow.setReversed( false );
	mCrossbow.setFrameSize( sf::Vector2i( 178, 291 ) );
	mCrossbow.setDuration( sf::seconds( 0.4f ) );
	mCrossbow.setNumFrames( 7 );
	mCrossbow.setRepeating( true );
	mCrossbow.setScale( 1.f, 1.f );

	//Add arms
	std::unique_ptr<Player_Arms> _larm( new Player_Arms( textures, 1 ) );
	mLArm = _larm.get();
	_larm->setPosition( sf::Vector2f( -10.f, -30.f ) );
	this->attachChild( std::move( _larm ) );

	std::unique_ptr<Player_Arms> _rarm( new Player_Arms( textures, -1 ) );
	mRArm = _rarm.get();
	_rarm->setPosition( sf::Vector2f( -10.f, 30.f ) );
	this->attachChild( std::move( _rarm ) );
}*/

void PlayerObject::setTool(PlayerObject::Tool tool){
	if(m_eTool != tool){
		m_eTool = tool;
	}
}

void PlayerObject::setState(PlayerObject::State state){
	if( m_eState != state ){

		m_eState = state;

		switch (m_eState){
		case PlayerObject::Idle:
			m_xpIdleAnim->setReversed( false );
			m_xpIdleAnim->restart();
			m_xpCurrentAnim = m_xpIdleAnim;
			break;
		case PlayerObject::Run_F:
			m_xpRunAnim->setReversed( false );
			m_xpRunAnim->restart();
			m_xpCurrentAnim = m_xpRunAnim;
			break;
		case PlayerObject::Run_B:
			m_xpRunAnim->setReversed( false );
			m_xpRunAnim->restart();
			m_xpCurrentAnim = m_xpRunAnim;
			break;
		case PlayerObject::Run_L:
			m_xpStepAnim->setReversed( false );
			m_xpStepAnim->restart();
			m_xpCurrentAnim = m_xpStepAnim;
			break;
		case PlayerObject::Run_R:
			m_xpStepAnim->setReversed( true );
			m_xpStepAnim->restart();
			m_xpCurrentAnim = m_xpStepAnim;
			break;
		default:
			break;
		}
	}
}

void PlayerObject::doWhip(sf::Vector2f _pos){
	m_xpBody->GetFixtureList()->SetDensity(10.f);
	m_xpBody->ResetMassData();
	m_xWhipPos = _pos;
	setState( State::Whipping );
	m_xpWhip->setState( Tool_Whip::Whipping );
}

PlayerObject::State PlayerObject::GetState(){
	return m_eState;
}

PlayerObject::Tool PlayerObject::GetTool(){
	return m_eTool;
}

void PlayerObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*m_xpCurrentAnim, states);
	
	if( m_eTool == Tool::Crossbow){
		target.draw(*m_xpCrossbow, states);
	}

	target.draw(*m_xpWhip, states);
}

void PlayerObject::Update(sf::Time p_xDtime){
	m_xVel = sf::Vector2f(sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A), sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W));
	m_xVel.x = (m_xVel.x * m_fPlayerspd * (float)p_xDtime.asSeconds());
	m_xVel.y = (m_xVel.y * m_fPlayerspd * (float)p_xDtime.asSeconds());

	setRotation( -90.f + atan2f( (sf::Mouse::getPosition(*m_xpWindow).y - m_xpWindow->getViewport( m_xpWindow->getView() ).height / 2), (sf::Mouse::getPosition(*m_xpWindow).x - m_xpWindow->getViewport( m_xpWindow->getView() ).width / 2) ) * 180.f / 3.141592f );

	sf::Vector2f cursorPos = sf::Vector2f( getPosition().x + ( (float)sf::Mouse::getPosition(*m_xpWindow).x - m_xpWindow->getViewport( m_xpWindow->getView() ).width/2 )*1.8, getPosition().y + ( (float)sf::Mouse::getPosition(*m_xpWindow).y - m_xpWindow->getViewport( m_xpWindow->getView() ).height/2 )*1.8 );

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::LShift ) ){
		setTool( Tool::Whip ); 
		
		if( m_xpWhip->getState() == Tool_Whip::Inactive || m_xpWhip->getState() == Tool_Whip::Passive ){
			m_xpWhip->setState( Tool_Whip::Swinging );
		}else if( m_xpWhip->getState() == Tool_Whip::Swinging ){
			if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) ){
				for ( SceneNode* e : m_xpEnemyMan->GetVector() ){
					EnemyObject *_e = dynamic_cast<EnemyObject*>(e);

					if( sqrtf( pow( _e->getPosition().x - cursorPos.x , 2 ) + pow( _e->getPosition().y - cursorPos.y , 2 ) ) < 50.f ){
						doWhip( cursorPos );
					}
				}
			}
		}
	}else{

		if( m_xpWhip->getState() == Tool_Whip::Passive ){
			m_xpWhip->Update(p_xDtime);
		}
		if( m_xpWhip->getState() == Tool_Whip::Swinging ){
			m_xpWhip->setState( Tool_Whip::Passive );
		}
	}

	m_xpCurrentAnim->setOrigin(m_xpCurrentAnim->getFrameSize().x/2, m_xpCurrentAnim->getFrameSize().y/2);
	
	//m_xpAnimation[0]->setOrigin(m_xpAnimation[0]->getFrameSize().x/2, m_xpAnimation[0]->getFrameSize().y/2);
	//m_xpAnimation[1]->setOrigin(m_xpAnimation[1]->getFrameSize().x/2, m_xpAnimation[1]->getFrameSize().y/2);
	m_xpCrossbow->update(p_xDtime);
	m_xpWhip->Update(p_xDtime);

	if( m_eState == State::Whipping ){
		sf::Vector2f _dir = sf::Vector2f( m_xWhipPos.x - getPosition().x, m_xWhipPos.y - getPosition().y );
		float _dist = sqrtf( pow( _dir.x, 2 ) + pow( _dir.y, 2 ) );

		m_xpWhip->setWhipDistance( _dist );

		if( m_xpWhip->getState() == Tool_Whip::Dragging ){
			m_xVel = _dir / 2.f;
			setRotation( -90.f + atan2f( m_xVel.y, m_xVel.x ) * 180 / 3.141592 );

			if( _dist < 50.f ){
				m_xpBody->GetFixtureList()->SetDensity(1.f);
				m_xpBody->ResetMassData();

				setState( State::Idle );
				setTool( Tool::Crossbow );
				m_xpWhip->setState( Tool_Whip::Inactive );
			}
		}
	}else{
		if (m_xVel != sf::Vector2f(0, 0)){ //As long as the player is pressing at least one of the movement-keys, 
			// this is to prevent the character from returning to original position/rotation.
			if (((atan2f( m_xVel.y, m_xVel.x ) * 180 / 3.141592) < getRotation() + 45.f) && ((atan2f( m_xVel.y, m_xVel.x) * 180 / 3.141592) > getRotation() - 45.f)){
				setState(State::Run_F); //Set state for animations etc
			}
			else if (((atan2f(m_xVel.y, m_xVel.x) * 180 / 3.141592) >= getRotation() + 45.f) && ((atan2f( m_xVel.y, m_xVel.x) * 180 / 3.141592) <= getRotation() + 135.f)){
				setState(State::Run_R);
			}
			else if (((atan2f(m_xVel.y, m_xVel.x) * 180 / 3.141592) <= getRotation() - 45.f) && ((atan2f( m_xVel.y, m_xVel.x) * 180 / 3.141592) >= getRotation() - 135.f)){
				setState(State::Run_L);
			}
			else {
				setState(State::Run_B);
			}
			//m_xpBody->SetLinearVelocity(b2Vec2(cosf(getRotation()) * 50.f / 32.f * (float)p_xDtime.asMilliseconds() , sin(getRotation())  * 50.f / 32.f * (float)p_xDtime.asMilliseconds()));
			//setPosition(m_xpBody->GetPosition().x * 32.f, m_xpBody->GetPosition().y * 32.f);
			//m_xPos = sf::Vector2f(m_xpBody->GetPosition().x * 32.f, m_xpBody->GetPosition().y * 32.f);
		}
		else {
			setState(State::Idle);
			m_xpBody->SetLinearVelocity( b2Vec2(0.f, 0.f));
		
			//setPosition(m_xpBody->GetPosition().x * 32.f, m_xpBody->GetPosition().y * 32.f);
		}
	}

	m_xpBody->SetLinearVelocity(b2Vec2(m_xVel.x, m_xVel.y));
	setPosition(m_xpBody->GetPosition().x * 32.f, m_xpBody->GetPosition().y * 32.f);
	m_xpCurrentAnim->setPosition(getPosition());
	m_xpCurrentAnim->setRotation(getRotation());
	m_xpCrossbow->setPosition(getPosition());
	m_xpCrossbow->setRotation(getRotation() + 180.f);
	m_xpWhip->setPosition(getPosition());
	m_xpWhip->setRotation(getRotation());

	switch (m_eState){
	case PlayerObject::Idle:
		m_xpIdleAnim->update(p_xDtime);
		break;
	case PlayerObject::Run_F:
		m_xpRunAnim->update(p_xDtime);
		break;
	case PlayerObject::Run_B:
		m_xpRunAnim->update(p_xDtime);
		break;
	case PlayerObject::Run_L:
		m_xpStepAnim->update(p_xDtime);
		break;
	case PlayerObject::Run_R:
		m_xpStepAnim->update(p_xDtime);
		break;
	default:
		break;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_fFiretime <= 0 ){ //&& m_fFiretime > (m_fMaxrate / m_fFrate) && m_bOverheat == false
		if (GetTool() == Tool::Crossbow){

			m_fFiretime = 0.2f;
			m_xpBulletMan->Add(new PlayerBullet(m_xpTextureMan, getPosition(), getRotation()));
		}
		else {
			setTool(Tool::Crossbow);
		}
	}else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ){
		setTool(Tool::Whip);
	}

	m_fFiretime-=p_xDtime.asSeconds();
	/*switch (punchArm){ // 0 = Left Arm, 1 = Right Arm
	case 0:
		if( sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !m_xpPlayerArms[0]->bPunching){
			if( m_eTool == Tool::Melee ){
				int s = rand() % 3;

				m_xpPlayerArms[0]->Punch();
				playSound( s );
				punchArm = 1;
			}
			else {
				setTool( Tool::Melee );
			}
		}
		break;
	case 1:
		if ( sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !m_xpPlayerArms[1]->bPunching){
			if( mTool == Tool::Melee ){
				int s = rand() % 3;

				m_xpPlayerArms[1]->Punch();
				playSound(s);
				punchArm = 0;
			}
			else {
				setTool( Tool::Melee );
			}
		}
		break;
	}*/
}