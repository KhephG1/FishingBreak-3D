#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::~AnimationComponent() {
	for (auto& i : Animations) {
		delete i.second;
	}
}

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet) : sprite{ sprite }, texture_sheet{ texture_sheet }
{
	last_animation = nullptr;
	priority_Anim = nullptr;
}


void AnimationComponent::addAnimation(const std::string key, float animT, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int w, int h){
	Animations[key] = new Animation{texture_sheet,sprite, animT,start_frame_x, start_frame_y,frames_x,frames_y,w,h};
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const bool priority)
{
	//if we have set a priority animation
	if (priority_Anim) {
		if (priority_Anim == Animations[key]) {
			if (last_animation != Animations[key]) {
				if (last_animation == nullptr) {
					last_animation = Animations[key];
				}
				else {
					last_animation->reset();
					last_animation = Animations[key];
				}
			}
			//if the priority animation is done, remove it
			if (Animations[key]->play(dt)) {
				priority_Anim = nullptr;
			}
		}
	}
	else { //keep playing the regular animation if a priority animation is not set
		if (priority) {
			priority_Anim = Animations[key];
		}
		if (last_animation != Animations[key]) {
			if (last_animation == nullptr) {
				last_animation = Animations[key];
			}
			else {
				last_animation->reset();
				last_animation = Animations[key];
			}
		}
		Animations[key]->play(dt);
	}
	return Animations[key]->isDone();
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority)
{

	if (priority_Anim) {
		if (priority_Anim == Animations[key]) {
			if (last_animation != Animations[key]) {
				if (last_animation == nullptr) {
					last_animation = Animations[key];
				}
				else {
					last_animation->reset();
					last_animation = Animations[key];
				}
			}
			//if the priority animation is done, remove it
			if (Animations[key]->play(dt, modifier / modifier_max)) {
				priority_Anim = nullptr;
			}
		}
	}
	else {
		//if this is a priority animation, set our priority animation variable to this one
		if (priority) {
			priority_Anim = Animations[key];
		}
		if (last_animation != Animations[key]) {
			if (last_animation == nullptr) {
				last_animation = Animations[key];
			}
			else {
				last_animation->reset();
				last_animation = Animations[key];
			}
		}
		Animations[key]->play(dt, modifier / modifier_max);
	}
	return Animations[key]->isDone();
}

const bool& AnimationComponent::isDone(const std::string key)
{
	return Animations[key]->isDone();
}

