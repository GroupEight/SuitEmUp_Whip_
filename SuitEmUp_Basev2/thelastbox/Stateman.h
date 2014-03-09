//Stateman.h//

#pragma once

#include <vector>

class State;

class Stateman {
public:
	Stateman();
	~Stateman();

	void Add(State *p_cpState); // Parameter_ClassPointerState
	void Update(sf::Time p_xDtime); // Parameter_FloatingDtime

	void Setstate(const std::string &p_skrState); // Parameter_StringKonstantReferenceState
	void ChangeState();
	void Draw();

	void Quit();
	bool IsRunning();

private:
	std::vector<State*> m_States; // Member_ClassVectorStates
	State *m_Current; // Member_ClassPointerCurrent
};