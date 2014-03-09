//NodeMan.cpp//

#include "NodeMan.h"

#include "GameObject.h"

NodeMan::NodeMan(){
	
}

NodeMan::~NodeMan(){
	for (int i = m_xpaNodes.size() - 1; i >= 0; i--){
		if (m_xpaNodes[i] != NULL){
			delete m_xpaNodes[i];
			m_xpaNodes[i] = NULL;
		}
	}
	m_xpaNodes.clear();
}

std::vector<SceneNode*> NodeMan::GetVector(){
	return m_xpaNodes;
}

void NodeMan::Add(SceneNode *p_xpNode){
	for (int i = m_xpaNodes.size() - 1; i >= 0; i--){
		if (m_xpaNodes[i] == p_xpNode){
			return;
		}
		if (m_xpaNodes[i] == NULL){
			m_xpaNodes[i] = p_xpNode;
			return;
		}
	}

	m_xpaNodes.push_back(p_xpNode);
}

void NodeMan::UpdateAll(sf::Time p_xDtime){
	for (int i = m_xpaNodes.size() - 1; i >= 0; i--){
		if (m_xpaNodes[i] != NULL){
			m_xpaNodes[i]->Update(p_xDtime);
		}
	}
}

void NodeMan::DrawAll(sf::RenderTarget *p_xpTarget){
	for (int i = m_xpaNodes.size() - 1; i >= 0; i--){
		if (m_xpaNodes[i] != NULL){
			m_xpaNodes[i]->draw(*p_xpTarget, sf::RenderStates::Default);
		}
	}
}

void NodeMan::UpdateOnScreen(sf::RenderWindow *p_xpWindow, sf::Time p_xDtime){
	for (int i = m_xpaNodes.size() - 1; i >= 0; i--){
		if (m_xpaNodes[i] != NULL){
			if (m_xpaNodes[i]->OnScreen(p_xpWindow)){
				m_xpaNodes[i]->Update(p_xDtime);
			}
		}
	}
}

void NodeMan::DrawOnScreen(sf::RenderWindow *p_xpWindow){
	for (int i = m_xpaNodes.size() - 1; i >= 0; i--){
		if (m_xpaNodes[i] != NULL){
			if (m_xpaNodes[i]->OnScreen(p_xpWindow)){
				m_xpaNodes[i]->draw(*p_xpWindow, sf::RenderStates::Default);
			}
		}
	}
}

void NodeMan::DeleteAll(){
	for (int i = m_xpaNodes.size() - 1; i >= 0; i--){
		if (m_xpaNodes[i] != NULL){
			delete m_xpaNodes[i];
			m_xpaNodes[i] = NULL;
		}
	}
	m_xpaNodes.clear();
}

void NodeMan::DeleteOffScreen(sf::RenderWindow *p_xpWindow){
	for (int i = m_xpaNodes.size() - 1; i >= 0; i--){
		if (m_xpaNodes[i] != NULL){
			if (!m_xpaNodes[i]->OnScreen(p_xpWindow)){
				std::cout << i;
				delete m_xpaNodes[i];
				m_xpaNodes[i] = NULL;
			}
		}
	}
}

void NodeMan::CopyFrom(NodeMan *p_xpNodeMan){
	for (int i = p_xpNodeMan->GetVector().size() - 1; i >= 0; i--){
		Add(p_xpNodeMan->GetVector()[i]);
	}
}

void NodeMan::Clear(){
	for (int i = 0; i < m_xpaNodes.size(); i++){
		if (m_xpaNodes[i] != NULL){
			m_xpaNodes[i] = NULL;
		}
	}
	m_xpaNodes.clear();
}