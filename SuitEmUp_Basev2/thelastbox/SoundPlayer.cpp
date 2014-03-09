//SoundPlayer.cpp//

#include "SoundPlayer.hpp"

#include <cmath>

/*namespace
{
	// Sound coordinate system, point of view of a player in front of the screen:
	// X = left; Y = up; Z = back (out of the screen)
	const float ListenerZ = 300.f;
	const float Attenuation = 8.f;
	const float MinDistance2D = 200.f;
	const float MinDistance3D = std::sqrt(MinDistance2D*MinDistance2D + ListenerZ*ListenerZ);
}*/

/*SoundPlayer::SoundPlayer()
: mSoundBuffers()
, mSounds(){
	mSoundBuffers.load(SFX::Cymbal_Hit_01,	"../rec/Sounds/Cymbal_Hit_01.wav");
	mSoundBuffers.load(SFX::Cymbal_Hit_02,	"../rec/Sounds/Cymbal_Hit_02.wav");
	mSoundBuffers.load(SFX::Cymbal_Hit_03,	"../rec/Sounds/Cymbal_Hit_03.wav");
	mSoundBuffers.load(SFX::Button_Hover,	"../rec/Sounds/Button_Hover.wav");
	mSoundBuffers.load(SFX::Button_Click,	"../rec/Sounds/Button_Click.wav");

	// Listener points towards the screen (default in SFML)
	sf::Listener::setDirection(0.f, 0.f, -1.f);
}*/

SoundPlayer::SoundPlayer(std::string p_sDir){
	m_sDir = p_sDir;

	m_xpSoundBuffers = new sf::SoundBuffer;

	m_fListenerZ = 300.f;
	m_fAttenuation = 8.f;
	m_fMinDistance2D = 200.f;
	m_fMinDistance3D = std::sqrt(m_fMinDistance2D*m_fMinDistance2D + m_fListenerZ*m_fListenerZ);
}

std::vector<SPair*> SoundPlayer::GetVector(){
	return m_xpaSfx;
}

sf::Sound *SoundPlayer::Load(std::string p_sFname, std::string p_sCname){
	sf::SoundBuffer l_xSoundBuffer;
	SPair *l_xpPair = new SPair;

	if (!l_xSoundBuffer.loadFromFile(m_sDir + p_sFname)){
		return NULL;
	}

	l_xpPair->Param0 = new sf::Sound;
	l_xpPair->Param0->setBuffer(l_xSoundBuffer);

	l_xpPair->Param1 = p_sCname;
	
	m_xpaSfx.push_back(l_xpPair);

	return l_xpPair->Param0;
}

void SoundPlayer::Play(std::string p_sCname){
	RemoveStoppedSounds();
	Play(p_sCname, GetListenerPosition());
}

void SoundPlayer::Play(std::string p_sCname, sf::Vector2f p_xPos){
	for (int i = 0; i < m_xpaSfx.size(); i++){
		if (m_xpaSfx[i]->Param1.compare(p_sCname) == 0){
			m_xpaSfx[i]->Param0->setPosition(p_xPos.x, -p_xPos.y, 0.f);
			m_xpaSfx[i]->Param0->setAttenuation(m_fAttenuation);
			m_xpaSfx[i]->Param0->setMinDistance(m_fMinDistance3D);
			m_xpaSfx[i]->Param0->play();
			return;
		}
	}
}

void SoundPlayer::RemoveStoppedSounds(){
	/*m_xpaSfx[0]->Param0->remove_if([] (const sf::Sound& s)
	{
		return s.getStatus() == sf::Sound::Stopped;
	});*/
}

void SoundPlayer::SetListenerPosition(sf::Vector2f p_xPos){
	sf::Listener::setPosition(p_xPos.x, -p_xPos.y, m_fListenerZ);
}

sf::Vector2f SoundPlayer::GetListenerPosition() const{
	sf::Vector3f l_xPos = sf::Listener::getPosition();
	return sf::Vector2f(l_xPos.x, -l_xPos.y);
}
