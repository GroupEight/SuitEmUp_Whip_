//Stateman.cpp//

#include "stdafx.h"

#include "Stateman.h"

#include "State.h"

Stateman::Stateman(){
	m_Current = NULL;
}

Stateman::~Stateman(){
	for (int i = 0; i < m_States.size(); i++){
		if (m_States[i] != NULL){
			delete m_States[i];
			m_States[i] = NULL;
		}
	}
	m_States.clear();
}

void Stateman::Add(State *p_cpState){
	m_States.push_back(p_cpState);
}

void Stateman::Update(sf::Time p_xDtime){
	if (m_States.empty()){
		return;
	}

	if (m_Current != NULL){
		if (!m_Current->Update(p_xDtime)){
			ChangeState();
		}
	}
}

void Stateman::Setstate(const std::string &p_skrState){
	for (unsigned int i = 0; i < m_States.size(); i++){
		if (m_States[i]->IsType(p_skrState)){
			m_Current = m_States[i];
			m_Current->Enter();
			return;
		}
	}
}

void Stateman::ChangeState(){
	std::string l_vNext = m_Current->Next();
	if (m_Current != NULL){
		m_Current->Exit();
		m_Current = NULL;
	}

	for (unsigned int i = 0; i < m_States.size(); i++){
		if (m_States[i]->IsType(l_vNext)){
			m_Current = m_States[i];
			m_Current->Enter();
			return;
		}
	}
}

void Stateman::Draw(){
	if (m_Current == NULL){
		return;
	}

	m_Current->Draw();
}

void Stateman::Quit(){
	m_Current = NULL;
}

bool Stateman::IsRunning(){
	return m_Current != NULL;
};