#pragma once
#include "scenenode.hpp"
#include "Particle.hpp"

#include <deque>

class TextureMan;

class ParticleEmitter : public SceneNode {
public:
	enum ParticleType{
		Star,
	};

public:
	ParticleEmitter(TextureMan *p_xpTextMan, ParticleEmitter::ParticleType type, int spawnRate);

	virtual void Update(sf::Time dt);

private:

	int mSpawnRate;
	int mSpawnTimer;

	sf::Texture pTex;
	sf::Vector2f pVeloc;
	int pDir, pSpread;
	float pRot, pRotRate;
	sf::Vector2f pScale, pScaleRate;
	float pLifespan;
};