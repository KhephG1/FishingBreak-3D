#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H


class AnimationComponent
{
private:
	class Animation {
	public:
		sf::Sprite& sprt;
		sf::Texture& textureSheet;
		float timer = 0;
		bool done;
		float animationTimer;
		int width;
		int height;
		sf::IntRect Startrect;
		sf::IntRect Currentrect;
		sf::IntRect Endrect;
		//Accessors
		const bool& isDone() const {
			return done;
		}
		Animation(sf::Texture& tex, sf::Sprite& s, float animT, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int w, int h) : done{ false },textureSheet { tex }, animationTimer{ animT }, sprt{ s } {
			animationTimer = animT;
			width = w;
			height = h;
			Startrect = sf::IntRect{ start_frame_x * width, start_frame_y * height, width, height};
			Currentrect = Startrect;
			Endrect = sf::IntRect{frames_x * width , frames_y * height, width, height };
			sprt.setTexture(textureSheet, true);
			sprt.setTextureRect(Startrect);
		}
		const bool& play(const float& dt) {
			done = false;
			timer += 100.f * dt;
			if (timer > animationTimer) {
				timer = 0.f;
				//Animate
				if (Currentrect.left != Endrect.left) {
					Currentrect.left += width;
				}
				else if (Currentrect.top != Endrect.top) {
					Currentrect.top += height;
				}
				//reset
				else {
					Currentrect.left = Startrect.left;
					Currentrect.top = Startrect.top;
					done = true;
				}
				sprt.setTextureRect(Currentrect);
			}
			return done;
		}
		const bool& play(const float& dt, float percentage) {
			if (percentage < 0.5f) {
				percentage = 0.5f;
			}
			done = false;
			timer += percentage * 100.f * dt;
			if (timer > animationTimer) {
				timer = 0.f;
				//Animate
				if (Currentrect.left != Endrect.left) {
					Currentrect.left += width;
					std::cout << "Animating" << std::endl;
				}
				else if (Currentrect.top != Endrect.top) {
					Currentrect.top += height;
				}
				//reset
				else {
					Currentrect.left = Startrect.left;
					Currentrect.top = Startrect.top;
					done = true;
				}
				sprt.setTextureRect(Currentrect);
			}
			return done;
		}
		void reset() {
			Currentrect = Startrect;
			timer = animationTimer;
		}
	};
	std::map<std::string, Animation*> Animations;
	Animation* last_animation;
	Animation* priority_Anim;
	sf::Sprite& sprite;
	sf::Texture& texture_sheet;
public:
	virtual ~AnimationComponent();
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	void addAnimation(const std::string key, float animT, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int w, int h);
	const bool& play(const std::string key, const float& dt, const bool priority = false);
	const bool& play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority = false);

	//Accessor
	const bool& isDone(const std::string key);
};
#endif
