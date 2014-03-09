//CollisionMan.cpp//

#include "CollisionMan.h"

CollisionMan::CollisionMan(){
	m_xpThisWorld = new b2World(b2Vec2(0.0f, 0.0f));
}

CollisionMan::~CollisionMan(){

}

void CollisionMan::Update(sf::Time p_xDtime){
	m_xpThisWorld->Step(1.f/60.f, 10, 8);
}

b2Body *CollisionMan::GetNewBody(sf::Vector2f p_xPos, float p_fRadius, int p_iDensity){
	b2BodyDef *l_xpBDef = new b2BodyDef;
	l_xpBDef->type = b2_dynamicBody;
	l_xpBDef->position.Set(p_xPos.x, p_xPos.y);

	b2Body *l_xpBody = m_xpThisWorld->CreateBody(l_xpBDef);

	b2CircleShape l_xCiShape;
	l_xCiShape.m_radius = p_fRadius;
	
	b2FixtureDef playerFixtureDef;
	playerFixtureDef.shape = &l_xCiShape;
	playerFixtureDef.density = p_iDensity;
	l_xpBody->CreateFixture(&playerFixtureDef);
	l_xpBody->SetAwake(true);

	m_xaDefs.push_back(l_xpBody);

	

	return l_xpBody;
}

b2World *CollisionMan::GetWorld(){
	return m_xpThisWorld;
}

/*void CollisionMan::MakeNewDynamicDef(){
	b2BodyDef *l_xpBDef;
	l_xpBDef->position.Set(p_xPos.x, p_xPos.y);
	m_xaDefs.push_back(l_xpBDef);
}*/