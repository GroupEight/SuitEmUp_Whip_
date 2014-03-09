#include "ParticleEmitter.hpp"

ParticleEmitter::ParticleEmitter(TextureMan *p_xpTextMan, ParticleEmitter::ParticleType type, int spawnRate)
	: mSpawnRate(spawnRate)
	, mSpawnTimer()
	, pTex()
	, pVeloc( 0.f, 0.f )
	, pDir( 0 )
	, pSpread( 0 )
	, pRot( 0.f )
	, pRotRate( 0.f )
	, pScale( 1.f, 1.f )
	, pScaleRate( 0.f, 0.f )
	, pLifespan( 1.f ){

	pTex.setSmooth( true );

	switch (type){
	case ParticleEmitter::Star:
		//pTex = textures.get( Textures::Part_Star_01 );
		pVeloc = sf::Vector2f( 3.f, 3.f );
		pRot = rand() % 360;
		pSpread = 360;
		pLifespan = 5.f;
		break;
	}
}

void ParticleEmitter::Update(sf::Time dt){
	mSpawnTimer++;

	if( mSpawnTimer >= mSpawnRate ){
		mSpawnTimer = 0; //Reset timer

		// Add particle
	}

	/*for (auto &child : mChildren)
	{
		Particle _p = dynamic_cast<Particle&>(*child);
		if( _p.mLifeTimer >= _p.mLifespan )
		{
			this->detachChild( _p );
		}
	}*/
}