
#include "stdafx.h"
#include <iostream>

#include "Box2D\Dynamics\b2World.h"

#include <stdio.h>
using namespace sf;



int _main(int argc, char** argv){
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	RenderWindow window(VideoMode(1024, 640), "Caption");

		CircleShape shape(10.0f);



	bool doSleep = true;
	b2Vec2 gravity(0.0f, 0.0f); 
	b2World *m_world =  new b2World(gravity);
	

	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	myBodyDef.position.Set(110, -10); //set the starting position
	myBodyDef.angle = 0; //set the starting angle
	
	b2Body* dynamicBody = m_world->CreateBody(&myBodyDef);

	//Chains
		b2BodyDef groundBodyDef;	
		groundBodyDef.type = b2_staticBody;

		b2Body* staticbody = m_world->CreateBody(&groundBodyDef);

		b2Vec2 vs[8];
		vs[0].Set(500.0f, 0.0f);
		vs[1].Set(300.0f, 0.0f);
		vs[2].Set(50.0f, -100.0f);
		vs[3].Set(100.7f, -300.0f);
		vs[4].Set(150.0, -400.0f);
		vs[5].Set(0.0f, -600.0f);
		vs[6].Set(400.0f, -500.0f);
		vs[7].Set(1000.7f, -200.0f);
		b2ChainShape chain;
		chain.CreateChain(vs, 8);
		
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &chain;
		fixtureDef.density = 0.0f;
		b2Fixture* myFixture = staticbody->CreateFixture(&fixtureDef);
	
	b2PolygonShape boxShape;
	boxShape.SetAsBox(1,1);
	
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	dynamicBody->CreateFixture(&boxFixtureDef);
	dynamicBody->SetAwake( true );

	dynamicBody->SetLinearVelocity( b2Vec2(0, 0 ));


	//b2BodyDef groundBodyDef;
	//groundBodyDef.position.Set(0.0f, -620.0f);
	//b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

	//b2PolygonShape groundBox;

	//groundBox.SetAsBox(320.0f, 0.01f);
	//groundBody->CreateFixture(&groundBox, 0.0f);
	//
	
		//
	while(window.isOpen()) {
		Event event;
		while(window.pollEvent(event)) {    
			if(event.type == Event::Closed) {
				window.close();
			}



		}
	
		b2Vec2 velocity( 0, 0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		velocity.x = 10;

		}
	
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		velocity.x = -10;
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		velocity.x = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		velocity.y = 10;
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		velocity.y = -10;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		velocity.y = 0;
		}

		dynamicBody->SetLinearVelocity(velocity);
		
		
	if(Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
	}


		window.clear(Color(0x05, 0x36, 0x57, 0xff));
		std::cout << dynamicBody->GetPosition().y << std::endl;


		float32 timeStep = 1.0f / 60.f; 
		int32 velocityIterations = 10; 
		int32 positionIterations = 8; 
		m_world->Step(timeStep, velocityIterations, positionIterations);
		shape.setPosition( dynamicBody->GetPosition().x, -dynamicBody->GetPosition().y );
		

		window.draw(shape);
		window.display();
	}



	


	return 0;
}









/*

// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace sf;

int _tmain(int argc, _TCHAR* argv[]) {
	RenderWindow window(VideoMode(1024, 640), "Caption");
	
	CircleShape shape(10.0f);
	
	while(window.isOpen()) {
		Event event;
		while(window.pollEvent(event)) {    
			if(event.type == Event::Closed) {
				window.close();
			}
		/*	else if(event.type == Event::KeyPressed) {
				InputManager::Onkeyboard(event.key, true);
			}														för pressed once
			else if(event.type == Event::KeyReleased) {
				InputManager::Onkeyboard(event.key, false);
			}*/
//		};



	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    shape.move(0.1, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    shape.move(-0.1, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    shape.move(0, -0.1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    shape.move(0, 0.1);
	}

		if(Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		if(Mouse::isButtonPressed(Mouse::Button::Left)) {
			window.close();
		}

		window.clear(Color(0x11, 0x22, 0x33, 0xff));
		window.draw(shape);
		window.display();
	};
	return 0;
	
};
*/











