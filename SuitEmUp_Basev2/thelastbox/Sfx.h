//Sfx.h//

#include <vector>

struct Pair {
	sf::Texture *Param0;
	std::string Param1;
};

class TextureMan {
public:
	TextureMan(std::string p_sDir);
	~TextureMan();

	std::vector<Pair> GetVector();

	sf::Texture *Load(std::string p_sFname, std::string p_sCname = "");

	sf: *Get(std::string p_sCname);

	void DeleteAll();

private:
	std::vector<Pair> m_xpaTexts;

	std::string m_sDir;
};