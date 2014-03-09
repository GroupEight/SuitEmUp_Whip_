//FontMan.cpp//

#include "FontMan.h"

FontMan::FontMan(std::string p_sDir){
	m_sDir = p_sDir;
}

FontMan::~FontMan(){

}

std::vector<FPair*> FontMan::GetVector(){
	return m_xpaFonts;
}

sf::Font *FontMan::Load(std::string p_sFname, std::string p_sCname){
	FPair *l_xpPair = new FPair;

	l_xpPair->Param0 = new sf::Font;
	if (!l_xpPair->Param0->loadFromFile(m_sDir + p_sFname)){
		return NULL;
	}

	l_xpPair->Param1 = p_sCname;
	
	m_xpaFonts.push_back(l_xpPair);

	return l_xpPair->Param0;
}

sf::Font *FontMan::Get(std::string p_sCname){
	for (int i = 0; i < m_xpaFonts.size(); i++){
		if (m_xpaFonts[i]->Param1.compare(p_sCname) == 0){
			return m_xpaFonts[i]->Param0;
		}
	}
	return NULL;
}

void FontMan::DeleteAll(){

}