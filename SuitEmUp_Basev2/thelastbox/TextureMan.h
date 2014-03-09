//TextureMan.h//

#include <vector>

struct TPair {
	sf::Texture *Param0;
	std::string Param1;
};

class TextureMan {
public:
	TextureMan(std::string p_sDir);
	~TextureMan();

	std::vector<TPair*> GetVector();

	sf::Texture *Load(std::string p_sFname, std::string p_sCname = "");

	sf::Texture *Get(std::string p_sCname);

	void DeleteAll();

private:
	std::vector<TPair*> m_xpaTexts;

	std::string m_sDir;
};