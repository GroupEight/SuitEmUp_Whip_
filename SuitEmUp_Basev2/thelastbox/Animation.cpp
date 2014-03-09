#include "Animation.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>


Animation::Animation()
: mFrameSize()
, mNumFrames(0)
, mCurrentFrame(0)
, mDuration(sf::Time::Zero)
, mElapsedTime(sf::Time::Zero)
, mRepeat(false){

}

Animation::Animation(sf::Texture *p_xpTex)
: mFrameSize()
, mNumFrames(0)
, mCurrentFrame(0)
, mDuration(sf::Time::Zero)
, mElapsedTime(sf::Time::Zero)
, mRepeat(false){
	m_xpSprite = new sf::Sprite(*p_xpTex);
}

void Animation::setTexture(sf::Texture *p_xpTex){
	m_xpSprite->setTexture(*p_xpTex);
}

const sf::Texture* Animation::getTexture() const {
	return m_xpSprite->getTexture();
}

void Animation::setFrameSize(sf::Vector2i frameSize){
	mFrameSize = frameSize;
}

sf::Vector2i Animation::getFrameSize() const{
	return mFrameSize;
}

void Animation::setNumFrames(std::size_t numFrames){
	mNumFrames = numFrames;
}

std::size_t Animation::getNumFrames() const{
	return mNumFrames;
}

void Animation::setDuration(sf::Time duration){
	mDuration = duration;
}

sf::Time Animation::getDuration() const{
	return mDuration;
}

void Animation::setRepeating(bool flag){
	mRepeat = flag;
}

bool Animation::isRepeating() const{
	return mRepeat;
}

void Animation::setReversed(bool flag){
	mReversed = flag;
}

bool Animation::isReversed() const{
	return mReversed;
}

void Animation::restart(){
	mCurrentFrame = 0;
}

bool Animation::isFinished() const{
	return mCurrentFrame >= mNumFrames;
}

sf::FloatRect Animation::getLocalBounds() const{
	return sf::FloatRect(getOrigin(), static_cast<sf::Vector2f>(getFrameSize()));
}

sf::FloatRect Animation::getGlobalBounds() const{
	return getTransform().transformRect(getLocalBounds());
}

void Animation::update(sf::Time dt){
	sf::Time timePerFrame = mDuration / static_cast<float>(mNumFrames);
	mElapsedTime += dt;

	sf::Vector2i textureBounds(m_xpSprite->getTexture()->getSize());
	sf::IntRect textureRect = m_xpSprite->getTextureRect();

	if (mCurrentFrame == 0){
		if(!mReversed){
			textureRect = sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y);
		}else{
			textureRect = sf::IntRect(textureBounds.x - mFrameSize.x, textureBounds.y - mFrameSize.y, mFrameSize.x, mFrameSize.y);
		}
	}
	
	// While we have a frame to process
	while (mElapsedTime >= timePerFrame && (mCurrentFrame <= mNumFrames || mRepeat))
	{
		if(!mReversed)
		{
			// Move the texture rect left
			textureRect.left += textureRect.width;

			// If we reach the end of the texture
			if (textureRect.left + textureRect.width > textureBounds.x)
			{
				// Move it down one line
				textureRect.left = 0;
				textureRect.top += textureRect.height;
			}

			// And progress to next frame
			mElapsedTime -= timePerFrame;
			if (mRepeat)
			{
				mCurrentFrame = (mCurrentFrame + 1) % mNumFrames;

				if (mCurrentFrame == 0)
					textureRect = sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y);
			}
			else
			{
				mCurrentFrame++;
			}
		}
		else{
			// Move the texture rect left
			textureRect.left -= textureRect.width;

			// If we reach the end of the texture
			if (textureRect.left < 0)
			{
				// Move it down one line
				textureRect.left = textureBounds.x;
				textureRect.top -= textureRect.height;
			}

			// And progress to next frame
			mElapsedTime -= timePerFrame;
			if (mRepeat)
			{
				mCurrentFrame = (mCurrentFrame + 1) % mNumFrames;

				if (mCurrentFrame == 0)
					textureRect = sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y);
			}
			else
			{
				mCurrentFrame++;
			}
		}
	}

	m_xpSprite->setTextureRect(textureRect);
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(*m_xpSprite, states);
}
