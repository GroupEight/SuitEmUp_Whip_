//Morker.cpp//

#include "Morker.h"

#include "Animation.hpp"


#include "CollisionMan.h"
#include "NodeMan.h"
#include "TextureMan.h"

#include "PlayerObject.h"
#include "EnemyBullet.h"



Morker::Morker(CollisionMan *p_xpCollisionMan, TextureMan *p_xpTexMan, float p_fAggroRange, float p_fAttackRange, sf::Vector2f p_xStartpos, PlayerObject *p_xpPlayer, NodeMan *p_xpEBulletMan, sf::Texture *p_xpTex){
	m_xPos = p_xStartpos;
	

	m_fAggroRange = p_fAggroRange;
	m_fAttackRange = p_fAttackRange;

	m_xpEBulletMan = p_xpEBulletMan;
	
	m_xpPlayer = p_xpPlayer;

	

	m_fSpd = 5.f;

	m_xpTex = p_xpTex;



	//std::map<sf::CircleShape*, sf::Vector2f> ebullets;
	
	m_xpTextureMan = p_xpTexMan;

		


	m_fFirerate = 0.f;

	m_xpBody = p_xpCollisionMan->GetNewBody(m_xPos, 1.0f, 1);
	
	

	m_xpIdleTex = p_xpTexMan->Get("Warrior_Idle");
	m_xpRunTex = p_xpTexMan->Get("Warrior_Run");
	m_xpAtkTex = p_xpTexMan->Get("Warrior_Atk");

	m_xpIdleAnim = new Animation(m_xpIdleTex);
	m_xpIdleAnim->setReversed( false );
	m_xpIdleAnim->setFrameSize( sf::Vector2i( 293, 320 ) );
	m_xpIdleAnim->setDuration( sf::seconds( 0.6f ) );
	m_xpIdleAnim->setNumFrames( 8 );
	m_xpIdleAnim->setRepeating( true );
	m_xpIdleAnim->restart();
	m_xpIdleAnim->setScale( 1.f, 1.f );
	m_xpIdleAnim->setOrigin( m_xpIdleAnim->getFrameSize().x/2, m_xpIdleAnim->getFrameSize().y/2 );

	m_xpRunAnim = new Animation(m_xpRunTex);
	m_xpRunAnim->setReversed( false );
	m_xpRunAnim->setFrameSize( sf::Vector2i( 267, 436 ) );
	m_xpRunAnim->setDuration( sf::seconds( 0.6f ) );
	m_xpRunAnim->setNumFrames( 16 );
	m_xpRunAnim->setRepeating( true );
	m_xpRunAnim->restart();
	m_xpRunAnim->setScale( 1.f, 1.f );
	m_xpRunAnim->setOrigin( m_xpRunAnim->getFrameSize().x/2, m_xpRunAnim->getFrameSize().y/2 );

	m_xpAtkAnim = new Animation(m_xpAtkTex);
	m_xpAtkAnim->setReversed( false );
	m_xpAtkAnim->setFrameSize( sf::Vector2i( 293, 321 ) );
	m_xpAtkAnim->setDuration( sf::seconds( 0.6f ) );
	m_xpAtkAnim->setNumFrames( 18 );
	m_xpAtkAnim->setRepeating( true );
	m_xpAtkAnim->restart();
	m_xpAtkAnim->setScale( 1.f, 1.f );
	m_xpAtkAnim->setOrigin( m_xpAtkAnim->getFrameSize().x/2, m_xpAtkAnim->getFrameSize().y/2 );

	/*m_xRunAnim.setSmooth(true);
	m_xAttackAnim.setSmooth(true);
	m_xIdleAnim.setSmooth(true);*/

	/*m_xpAnimSprite->setTexture( m_xpRunAnim );
	m_xpAnimSprite->setOrigin( m_xpAnimSprite->getFrameSize().x/2, m_xpAnimSprite->getFrameSize().y/2 );
	m_xpAnimSprite->setRotation( -90.f );*/

	SetState(AIState::Passive);
}

void Morker::SetState(Morker::AIState state){
	if (m_eState != state){
		m_eState = state;

		switch (m_eState){
		case Morker::Passive:
			m_xpIdleAnim->setReversed( false );
			m_xpIdleAnim->restart();
			m_xpCurrentAnim = m_xpIdleAnim;
			break; 
		case Morker::Aggro:
			m_xpRunAnim->setReversed( false );
			m_xpRunAnim->restart();
			m_xpCurrentAnim = m_xpRunAnim;
			break;
		case Morker::Attacking:
			m_xpAtkAnim->setReversed( false );
			m_xpAtkAnim->restart();
			m_xpCurrentAnim = m_xpAtkAnim;
			break;
		default:
			break;
		}
	}
}

Morker::AIState Morker::GetState(){
	return m_eState;
}

float Morker::GetAggroRange(){
	return m_fAggroRange;
}

float Morker::GetAttackRange(){
	return m_fAttackRange;
}

void Morker::Update(sf::Time dt){
	float l_fEnemyDist = sqrtf( ( (m_xpPlayer->GetPosition().x - m_xpBody->GetPosition().x ) * ( m_xpPlayer->GetPosition().x - m_xpBody->GetPosition().x ) ) + ( ( m_xpPlayer->GetPosition().y - m_xpBody->GetPosition().y ) * (m_xpPlayer->GetPosition().y - m_xpBody->GetPosition().y) ) );
	float l_fXtrrot = -90.f;

	std::cout << l_fEnemyDist << std::endl;

	
	if ( l_fEnemyDist < m_fAggroRange && l_fEnemyDist > m_fAttackRange ){
			SetState( Morker::Aggro );
	}
	else if ( l_fEnemyDist > m_fAggroRange && GetState() == Morker::Aggro ){
		SetState( Morker::Passive );
	}
	else if ( l_fEnemyDist <= m_fAttackRange && GetState() == Morker::Aggro ){
		SetState( Morker::Attacking );
	}

	if (l_fEnemyDist > m_fAggroRange){
		SetState(Morker::AIState::Passive);
	} 
	else if (l_fEnemyDist <= m_fAggroRange && l_fEnemyDist > m_fAttackRange){
		




		SetState(Morker::AIState::Aggro);
	}
	else if (l_fEnemyDist <= m_fAttackRange && m_eState == Morker::AIState::Aggro){
		SetState(Morker::AIState::Attacking);
	}
	
	if ( m_iHp <= 0 ){
		//mSceneLayers[Main]->detachChild( *_e );
		//mRemovable.push_back(std::move(_b));
	}

	if (m_eState == Morker::AIState::Passive){
		m_xVel = sf::Vector2f(0, 0);
	}
	else if (m_eState == Morker::AIState::Aggro){		
		setRotation(atan2f( (m_xpPlayer->GetPosition().y - GetPosition().y), (m_xpPlayer->GetPosition().x - GetPosition().x) ) * 180.f / 3.141592f - 90.f);
		m_xVel = m_fSpd * sf::Vector2f(cosf(getRotation() * 3.141592 / 180 + 90.f), sinf(getRotation() * 3.141592 / 180 + 90.f));


		std::cout << GetPosition().x << " : " << GetPosition().y << " : " << getRotation() << std::endl;
	}
	else if (m_eState == Morker::AIState::Attacking){
		m_xVel = sf::Vector2f(0, 0);
		setRotation(atan2f( (m_xpPlayer->GetPosition().y - GetPosition().y), (m_xpPlayer->GetPosition().x - GetPosition().x) ) * 180.f / 3.141592f - 90.f);
		/*float _dirRot = atan2f( m_xpPlayer->getWorldPosition().y - getWorldPosition().y, m_xpPlayer->getWorldPosition().x - getWorldPosition().x );
		setRotation( _dirRot * 180 / 3.141592 );*/

		

		
		if( m_fFirerate <= 0) {

			m_fFirerate = 0.45;
		m_xpEBulletMan->Add(new EnemyBullet(m_xpTextureMan, getPosition(), getRotation(), m_xpPlayer));
		

		std::cout << "SPAWN!!";
		}
		//sf::Vector2f direction((m_xpPlayer->getPosition().x - ebullet->getPosition().x)/sqrt(pow((m_xpPlayer->getPosition().x - ebullet->getPosition().x), 2)+pow((m_xpPlayer->getPosition().y - ebullet->getPosition().y), 2)), (shape.getPosition().y - ebullet->getPosition().y)/sqrt(pow((shape.getPosition().x - ebullet->getPosition().x), 2)+pow((shape.getPosition().y - ebullet->getPosition().y), 2)));
		



	

		
	}

	if (m_eState == Morker::Aggro || m_eState == Morker::Attacking){
		
		if(GetPosition().x >= m_xpPlayer->GetPosition().x && GetPosition().y >= m_xpPlayer->GetPosition().y || GetPosition().x <= m_xpPlayer->GetPosition().x && GetPosition().y <= m_xpPlayer->GetPosition().y) {
		
		if(m_fzigzag <= 0.5 ) {
			m_fzigzag = 2;

		 if(m_fzigzag > 1.5)  { 
		  m_xVel = sf::Vector2f(12, -11); 
		  }
		}
		if (m_fzigzag > 1.0 && m_fzigzag < 1.5) {
			m_xVel = sf::Vector2f(-12, 11);  
		}
		if (m_fzigzag > 0.5 && m_fzigzag < 1.0) {
			m_xVel = sf::Vector2f(12, -11);
		}
		/*if (m_fzigzag > 1.0 && m_fzigzag < 1.5) {
			m_xVel = sf::Vector2f(5.5, 3);
		}
		if (m_fzigzag > 0.5 && m_fzigzag < 1.0) {
			m_xVel = sf::Vector2f(-4.5, -3);
		}
		if (m_fzigzag > 0.0 && m_fzigzag < 0.5) {
			m_xVel = sf::Vector2f(5.5, 3);
		}*/
	}
		
		
		
		if(GetPosition().x <= m_xpPlayer->GetPosition().x && GetPosition().y >= m_xpPlayer->GetPosition().y || GetPosition().x >= m_xpPlayer->GetPosition().x && GetPosition().y <= m_xpPlayer->GetPosition().y){
		if(m_fzigzag <= 0.5 ) {
			m_fzigzag = 2;

		 if(m_fzigzag > 1.5)  { 
		  m_xVel = sf::Vector2f(-12, -11); 
		  }
		}
		if (m_fzigzag > 1.0 && m_fzigzag < 1.5) {
			m_xVel = sf::Vector2f(12, 11);  
		}
		if (m_fzigzag > 0.5 && m_fzigzag < 1.0) {
			m_xVel = sf::Vector2f(-12, -11);
		}
		/*if (m_fzigzag > 1.0 && m_fzigzag < 1.5) {
			m_xVel = sf::Vector2f(3, 5.5);
		}
		if (m_fzigzag > 0.5 && m_fzigzag < 1.0) {
			m_xVel = sf::Vector2f(-3, -4.5);
		}
		if (m_fzigzag > 0.0 && m_fzigzag < 0.5) {
			m_xVel = sf::Vector2f(3, 5.5);
		}*/
	}
		
		
		}
	

	if (m_eState == Morker::Passive){
		std::cout << "Passive";
	}
	else if (m_eState == Morker::Aggro){
		std::cout << "Aggro";
	}
	else if (m_eState == Morker::Attacking){
		std::cout << "Attacking";
	}

	m_fFirerate-=dt.asSeconds();

	m_fzigzag-=dt.asSeconds();

	m_xpCurrentAnim->update(dt);

	m_xpBody->SetLinearVelocity(b2Vec2(m_xVel.x, m_xVel.y));
	setPosition(m_xpBody->GetPosition().x * 32.f, m_xpBody->GetPosition().y * 32.f);
	m_xpCurrentAnim->setPosition(getPosition());
	m_xpCurrentAnim->setRotation(getRotation());
}

void Morker::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw( *m_xpCurrentAnim, states );
}


	