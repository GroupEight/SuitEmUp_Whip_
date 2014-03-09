//Animation.h//

#pragma once

#include "SceneNode.hpp"



class Animation : public sf::Drawable, public sf::Transformable {
public:
	Animation();
	explicit Animation(sf::Texture *p_xpTex);

	void setTexture(sf::Texture *p_xpTex);
	const sf::Texture* getTexture() const;

	void setFrameSize(sf::Vector2i mFrameSize);
	sf::Vector2i getFrameSize() const;

	void setNumFrames(std::size_t numFrames);
	std::size_t getNumFrames() const;

	void setDuration(sf::Time duration);
	sf::Time getDuration() const;

	void setRepeating(bool flag);
	bool isRepeating() const;

	void setReversed(bool flag);
	bool isReversed() const;

	void restart();
	bool isFinished() const;

	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;

	void update(sf::Time dt);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite *m_xpSprite;
	sf::Vector2i mFrameSize;

	std::size_t mNumFrames,
		mCurrentFrame;

	sf::Time mDuration,
		mElapsedTime;

	bool mRepeat,
		mReversed;
};