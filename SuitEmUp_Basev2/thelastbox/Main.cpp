//Main.cpp//

#include "Game.hpp"

int main(){
	Game m_xGame;

	if (m_xGame.Init()){
		m_xGame.Run();
	}
	m_xGame.Cleanup();
}