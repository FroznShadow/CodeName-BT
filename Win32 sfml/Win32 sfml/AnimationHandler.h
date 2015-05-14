#ifndef ANIMATIONHANDLER_H
#define ANIMATIONHANDLER_H

#include "sfml.h"
#include <vector>
#include <string>
#include <iostream>
class Animation
{
public:
	Animation(std::string name, int startFrame, unsigned int endFrame, float duration, sf::IntRect frameSize)
	{
		this->startFrame = startFrame;
		this->endFrame = endFrame;
		this->duration = duration;
		this->frameSize = frameSize;
	}
	~Animation(){}
	unsigned int getLength() { return endFrame - startFrame + 1; }
	sf::IntRect frameSize;
	unsigned int startFrame;
	unsigned int endFrame;
	float duration;

};

class AnimationHandler
	{

public:
	AnimationHandler()
	{
		this->t = 0.0f;
		this->currentAnim = -1;
	}

	~AnimationHandler() {}

	
	void addAnim(Animation& anim);
	void update(const float dt);
	void changeAnim(unsigned int animNum);
	std::string getName(unsigned int animID);
	sf::IntRect bounds;
	
		int currentAnim;

private:
	std::string name;
	std::vector<Animation> animations;
	float t;
	


};

#endif // !ANIMATIONHANDLER_H
