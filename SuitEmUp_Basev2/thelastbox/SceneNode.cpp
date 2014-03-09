//SceneNode.cpp//

#include "SceneNode.hpp"
#include "EnemyObject.hpp"
#include "PlayerBullet.hpp"


SceneNode::SceneNode(){
	m_bShowing = true;
}

SceneNode::~SceneNode(){

}

void SceneNode::Update(sf::Time dt){
	// Empty...
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	// Apply transform of current node
	states.transform *= getTransform();

	// If showing, draw node and children with changed transform
	/*if(bShowing){
		drawCurrent(target, states);
		drawChildren(target, states);
	}*/
}

void SceneNode::Overlap(PlayerBullet *p_xpPBullet, EnemyObject *p_xpEnemy) {

	m_xpPBullet = p_xpPBullet;
	m_xpEnemy = p_xpEnemy;

	/*if (sqrt(pow(m_xpEnemy->getPosition().x - m_xpPBullet->getPosition().x, 2) + pow(m_xpEnemy->getPosition().y - m_xpPBullet->getPosition().y, 2)) <= m_xpEnemy->getRadius() + m_xpPBullet->getRadius())
	{
}*/
}

sf::Vector2f SceneNode::getWorldPosition() const {
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const {
	sf::Transform transform = sf::Transform::Identity;

	/*for (const SceneNode* node = this; node != nullptr; node = node->mParent)
		transform = node->getTransform() * transform;*/

	return transform;
}

bool SceneNode::Show(){
	m_bShowing = true;
	return m_bShowing;
}

bool SceneNode::Hide(){
	m_bShowing = false;
	return m_bShowing;
}

bool SceneNode::GetIsShowing(){
	return m_bShowing;
}

bool SceneNode::OnScreen(sf::RenderWindow *p_xpWindow){
	if (m_xPos.x > p_xpWindow->getView().getCenter().x - p_xpWindow->getView().getSize().x / 2 && m_xPos.x < p_xpWindow->getView().getCenter().x + p_xpWindow->getView().getSize().x / 2){
		return true;
	}
	else if (m_xPos.y > p_xpWindow->getView().getCenter().y -p_xpWindow->getView().getSize().y / 2 && m_xPos.y < p_xpWindow->getView().getCenter().y + p_xpWindow->getView().getSize().y / 2){
		return true;
	}
	return false;
}