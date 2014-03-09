//Level.cpp//

#include "Level_Wall.hpp"

#include <sstream>
#include <fstream>
#include <iostream>

#include <typeinfo>

#include "CollisionMan.h"
#include "NodeMan.h"
#include "TextureMan.h"

#include "EnemyObject.hpp"
#include "PlayerObject.h"

Wall::Wall(sf::Vector2f p_xPos, float p_fAng, float p_fHe){
	m_xPos = p_xPos;

	m_fAng = p_fAng;
	m_fHe = p_fHe;
}

Level::Level(std::string p_sDir, TextureMan *p_xpTextMan, CollisionMan *p_xpCMan, NodeMan *p_xpEnemyMan, PlayerObject *p_xpPlayer)
: mParallax( 0.2 ){
	m_xpPlayer = p_xpPlayer;
	m_sDir = p_sDir;

	m_xpCMan = p_xpCMan;
	m_xpEnemyMan = p_xpEnemyMan;
	m_xpTexMan = p_xpTextMan;

	m_xpTex = p_xpTextMan->Get("Wall");
	m_xpTex->setRepeated( true );
	m_xpTex->setSmooth( true );
}

Level::~Level(){
	ClearLevel();
}

bool Level::LoadLevel(std::string p_sFile){
    std::string l_sData = m_sDir + p_sFile;

    std::ifstream stream;
    stream.open(l_sData.c_str());

    if (!stream.is_open()){
        return false;
    }

    std::string row;
    stream >> row;

    while (!stream.eof()) {
        std::getline(stream, row);
        if (row.length() == 0){
            continue;
        }
        std::stringstream ss(row);

        std::string l_sType;

        ss >> l_sType;

        if (l_sType.compare("#") == 0){
            row = "";
            continue;
        }

		// Walls:
        if (l_sType.compare("Wall") == 0){

            float l_fPosx, l_fPosy, l_fAng = 0.f, l_fHe = 0.f;

            ss >> l_fPosx;
            ss >> l_fPosy;

            if (row.length() != 0){
                ss >> l_fAng;
            }

            if (row.length() != 0){
                ss >> l_fHe;
            }

			m_xaWalls.push_back(new Wall(sf::Vector2f(l_fPosx, l_fPosy), l_fAng, l_fHe));

            row = "";

            continue;
        }

        // Enemy:
        if (l_sType.compare("Enemy") == 0){
            float l_fPosx, l_fPosy, l_fAggro, l_fAtk;

            int l_iType;
			
			ss >> l_fPosx;
			ss >> l_fPosy;
			ss >> l_fAggro;
			ss >> l_fAtk;
			ss >> l_iType;

            m_xpEnemyMan->Add(new EnemyObject(m_xpCMan, m_xpTexMan, 40.f, 10.f, sf::Vector2f(l_fPosx, l_fPosy), m_xpPlayer));

            row = "";

            continue;
        }

		// Morker:
        if (l_sType.compare("Morker") == 0){
            float l_fPosx, l_fPosy, l_fAggro, l_fAtk;

            int l_iType;
			
			ss >> l_fPosx;
			ss >> l_fPosy;
			ss >> l_fAggro;
			ss >> l_fAtk;
			ss >> l_iType;

            m_xpEnemyMan->Add(new EnemyObject(m_xpCMan, m_xpTexMan, 40.f, 10.f, sf::Vector2f(l_fPosx, l_fPosy), m_xpPlayer));

            row = "";

            continue;
        }

        if (l_sType.compare("Player") == 0){
			float l_fPosx, l_fPosy;

			ss >> l_fPosx;
            ss >> l_fPosy;
           
			m_xpPlayer->SetPosition(sf::Vector2f(l_fPosx, l_fPosy));

            row = "";

            continue;
        }
    }

    stream.close();
	
	MakeWalls();

	placeWallVertices();

    //Collision:

	vs = new b2Vec2 [m_xaWalls.size()];
	for (int i = 0; i < m_xaWalls.size(); i++){
		vs[i].Set(m_xaWalls[i]->m_xPos.x / 32, m_xaWalls[i]->m_xPos.y / 32);
	}

	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;

	//b2Body* staticbody = mBWorld->CreateBody(&groundBodyDef);
	m_xpLevelBody = m_xpCMan->GetWorld()->CreateBody(&groundBodyDef);

	b2ChainShape chain;

	chain.CreateLoop(vs, m_xCVertices.getVertexCount() - 1);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &chain;
	fixtureDef.density = 0.0f;
	b2Fixture* myFixture = m_xpLevelBody->CreateFixture(&fixtureDef);

    return true;
}

void Level::ClearLevel(){
	m_xpEnemyMan->DeleteAll();

	m_xCVertices.clear();
	m_xCVertexSpec.clear();
	
	m_xRoof.clear();
	m_xWalls.clear();

	m_xpCMan->GetWorld()->DestroyBody(m_xpLevelBody);

	for (int i = m_xaWalls.size() - 1; i >= 0; i--){
		delete m_xaWalls[i];
		m_xaWalls[i] = NULL;
	}

	m_xaWalls.clear();
}

void Level::MakeWalls(){
	m_xCVertices.setPrimitiveType(sf::Points);  m_xCVertices.resize(m_xaWalls.size());
	m_xCVertexSpec.setPrimitiveType(sf::Points); m_xCVertexSpec.resize(m_xaWalls.size());
	m_xWalls.setPrimitiveType(sf::TrianglesStrip); m_xWalls.resize(m_xaWalls.size() * 2);
	m_xRoof.setPrimitiveType(sf::TrianglesStrip); m_xRoof.resize(m_xaWalls.size() * 2);

	for (int i = 0; i < m_xaWalls.size(); i++){
		m_xCVertices[i].position = m_xaWalls[i]->m_xPos;
		m_xCVertexSpec[i].position = sf::Vector2f(m_xaWalls[i]->m_fAng, m_xaWalls[i]->m_fHe);
	}
}

/*void Level::createControlVertex(sf::Vector2f _pos, float _ang, float _height){
	m_xCVertices.setPrimitiveType(sf::Points);  m_xCVertices.resize(47);
	m_xCVertexSpec.setPrimitiveType(sf::Points); m_xCVertices.resize(47);
	m_xWalls.setPrimitiveType(sf::TrianglesStrip); m_xCVertices.resize(100);
	m_xRoof( sf::TrianglesStrip, 100 );

	m_xCVertexSpec[v].position = sf::Vector2f( _ang, _height );
	m_xCVertices[v].position = _pos;

	//Collision
	vs[v].Set( _pos.x / 32.f, _pos.y / 32.f );

	v++;
}*/

void Level::placeWallVertices(){
	float angleBetweenPoints = 0;
	float distanceBetweenPoints = 0;
	float wallHeight = 50.f;
	int lastVertex = m_xCVertices.getVertexCount()-1;

	cPos = m_xpPlayer->getPosition();

	int q = 0;

	for(int i = 0; i < m_xaWalls.size(); i++){
		float offsetAngle = m_xCVertexSpec[i].position.x * 3.141592 / 180;
		float offsetHeight = m_xCVertexSpec[i].position.y;

		//float camDistance = sqrt( ( (m_xCVertices[i].position.x - cPos.x) * (m_xCVertices[i].position.x - cPos.x) ) + ( (m_xCVertices[i].position.y - cPos.y) * (m_xCVertices[i].position.y - cPos.y) ) );
		float camDistanceX = m_xCVertices[i].position.x - cPos.x;
		float camDistanceY = m_xCVertices[i].position.y - cPos.y;
		
		//ANGLE
		if(i>0 && i<lastVertex){
			angleBetweenPoints = (90.f * 3.141592 / 180) + atan2f( ( m_xCVertices[i+1].position.y - m_xCVertices[i-1].position.y ), ( m_xCVertices[i+1].position.x - m_xCVertices[i-1].position.x ) );
		}else{
			angleBetweenPoints = (90.f * 3.141592 / 180);
		}
		

		//POSITION
		m_xWalls[q].position = sf::Vector2f( m_xCVertices[i].position.x, m_xCVertices[i].position.y );
		m_xWalls[q+1].position = sf::Vector2f( mParallax * camDistanceX + m_xCVertices[i].position.x + cosf( angleBetweenPoints + offsetAngle ) * (wallHeight + offsetHeight), mParallax * camDistanceY + m_xCVertices[i].position.y + sinf( angleBetweenPoints + offsetAngle ) * (wallHeight + offsetHeight) );

		m_xRoof[q].position = sf::Vector2f( m_xWalls[q+1].position.x + cosf( angleBetweenPoints + offsetAngle ) * -1, m_xWalls[q+1].position.y + sinf( angleBetweenPoints + offsetAngle ) * -1 );
		m_xRoof[q+1].position = sf::Vector2f( m_xWalls[q+1].position.x + cosf( angleBetweenPoints + offsetAngle ) * ( 800.f ), m_xWalls[q+1].position.y + sinf( angleBetweenPoints + offsetAngle ) * ( 800.f ) );

		//ROOF COLOR
		m_xRoof[q].color = sf::Color::Black;
		m_xRoof[q+1].color = sf::Color::Black;

		
		//TEX-COORDS
		if(i>0){
			float _x = m_xCVertices[i-1].position.x - m_xCVertices[i].position.x;
			float _y = m_xCVertices[i-1].position.y - m_xCVertices[i].position.y;
			distanceBetweenPoints = sqrtf( ( _x * _x ) + ( _y * _y ) );

			//Add the length of the new quad to the last texCoords to make sure that the textures isn't stretched/squashed.
			m_xWalls[q].texCoords = sf::Vector2f( m_xWalls[q-1].texCoords.x + distanceBetweenPoints, m_xpTex->getSize().y );
			m_xWalls[q+1].texCoords = sf::Vector2f( m_xWalls[q-1].texCoords.x + distanceBetweenPoints, 0 );
		}else{
			m_xWalls[q].texCoords = sf::Vector2f( 0, m_xpTex->getSize().y );
			m_xWalls[q+1].texCoords = sf::Vector2f( 0, 0 );
		}
		

		q+=2;
	}

	//Fix for weird extra vertex added
	/*m_xWalls[q-1].position = m_xWalls[q-2].position;
	m_xWalls[q-1].texCoords = m_xWalls[q-2].texCoords;
	m_xRoof[q-1].position = m_xRoof[q-2].position;
	m_xRoof[q-1].color = sf::Color::Black;*/
	
}

sf::Vector2f Level::getControlVertexPos( int index ){
	return m_xCVertices[index].position;
}

void Level::Update(sf::Time dt){
	placeWallVertices();
}

void Level::setCameraPos( sf::Vector2f pos ){
	cPos = pos;
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	glEnable( GL_CULL_FACE );

	states.texture = m_xpTex;
	target.draw( m_xWalls, states );

	glDisable( GL_CULL_FACE );

	states.texture = nullptr;
	target.draw( m_xRoof, states );
}