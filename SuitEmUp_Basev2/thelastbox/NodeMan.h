//NodeMan.h//

#include <vector>

class SceneNode;

class NodeMan {
public:
	NodeMan();
	~NodeMan();

	std::vector<SceneNode*> GetVector();

	void Add(SceneNode *p_xpNode);

	void UpdateAll(sf::Time p_xDtime);
	void UpdateOnScreen(sf::RenderWindow *p_xpWindow, sf::Time p_xDtime);
	
	void DrawAll(sf::RenderTarget *p_xpTarget);
	void DrawOnScreen(sf::RenderWindow *p_xpWindow);

	void DeleteAll();
	void DeleteOffScreen(sf::RenderWindow *p_xpWindow);

	void CopyFrom(NodeMan *p_xpNodeMan);

	void Clear();

private:
	std::vector<SceneNode*> m_xpaNodes;
};