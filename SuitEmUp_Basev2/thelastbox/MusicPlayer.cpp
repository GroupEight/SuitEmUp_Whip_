#include "MusicPlayer.hpp"


MusicPlayer::MusicPlayer()
: mVolume(100.f){
	//mFilenames[Music::MenuTheme]    = "../rec/Music/Bennie_Motens_KC_Jazz_Band-South_1924.ogg";
	//mFilenames[Music::InGameTheme] = "../rec/Music/Bennie_Motens_KC_Jazz_Band-South_1924.ogg";
}

void MusicPlayer::Play(std::string p_sCname){
	/*std::map<Music::ID, std::string>	mFilenames;
	std::string filename = mFilenames[theme];
	
	if (!mMusic.openFromFile(filename))
		throw std::runtime_error("Music " + filename + " could not be loaded.");

	mMusic.setVolume(mVolume);
	mMusic.setLoop(true);
	mMusic.play();*/
}


void MusicPlayer::Stop(){
	m_xpCurrent->stop();
}

void MusicPlayer::SetVolume(float p_fVolume){
	mVolume = p_fVolume;
}

void MusicPlayer::SetPaused(bool p_bPaused){
	if (p_bPaused)
		m_xpCurrent->pause();
	else
		m_xpCurrent->play();
}