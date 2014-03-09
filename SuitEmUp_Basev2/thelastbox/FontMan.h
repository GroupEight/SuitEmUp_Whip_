//FontMan.h//

#pragma once

struct FPair {
	sf::Font *Param0;
	std::string Param1;
};

class FontMan {
public:
	FontMan(std::string p_sDir);
	~FontMan();

	std::vector<FPair*> GetVector();

	sf::Font *Load(std::string p_sFname, std::string p_sCname = "");

	sf::Font *Get(std::string p_sCname);

	void DeleteAll();

private:
	std::vector<FPair*> m_xpaFonts;

	std::string m_sDir;
};