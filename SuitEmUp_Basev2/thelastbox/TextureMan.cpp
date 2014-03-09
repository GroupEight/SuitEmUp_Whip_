//TextureMan.cpp//

#include "TextureMan.h"

TextureMan::TextureMan(std::string p_sDir){
	m_sDir = p_sDir;
}

TextureMan::~TextureMan(){
	for (int i = m_xpaTexts.size() - 1; i >= 0; i--){
		delete m_xpaTexts[i];
		m_xpaTexts[i] = NULL;
	}
}

std::vector<TPair*> TextureMan::GetVector(){
	return m_xpaTexts;
}

sf::Texture *TextureMan::Load(std::string p_sFname, std::string p_sCname){
	TPair *l_xpPair = new TPair;

	l_xpPair->Param0 = new sf::Texture();
	if (!l_xpPair->Param0->loadFromFile(m_sDir + p_sFname)){
		return NULL;
	}

	l_xpPair->Param1 = p_sCname;

	l_xpPair->Param0->setSmooth(true);
	
	m_xpaTexts.push_back(l_xpPair);

	return l_xpPair->Param0;
}

sf::Texture *TextureMan::Get(std::string p_sCname){
	for (int i = 0; i < m_xpaTexts.size(); i++){
		if (m_xpaTexts[i]->Param1.compare(p_sCname) == 0){
			return m_xpaTexts[i]->Param0;
		}
	}
	return NULL;
}

void TextureMan::DeleteAll(){

}