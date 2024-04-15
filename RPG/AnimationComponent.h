#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H


class AnimationComponent
{
private:
//A class to perform the functionality of performing animations based on a texture sheet
	class Animation {
	public:
		sf::Sprite& sprt;
		//the texture sheet containing the animation
		sf::Texture& textureSheet;
		//variable to act as the counter for implementing modifiable animation speed
		float timer = 0;
		//boolean to track if the animation has finished or not
		bool done;
		//variable to track when to switch textures (lower = sprite switches textures more often and animation plays faster)
		float animationTimer;
		//dimentions of each texture in the sheet (to work, each texture in the sheet must be side by side and uniformly sized)
		int width;
		int height;
		//rectangle in the texture sheet to start animation and end animation at, rectangle to track what texture we are currently on
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
		//function to switch from one texture to the next in the animation and update the "done" bool accordingly
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
		//need to rewatch section where this function made
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
	// A map to store all the animations associated with the entity containing this animation component
	std::map<std::string, Animation*> Animations;
	//Animation pointers to implement priority animation functionality
	//eg: we are running but want to attack. Run animation should finish the instant we push the mouse to attack and attack animation should begin
	Animation* last_animation;
	Animation* priority_Anim;
	//the sprite being animated
	sf::Sprite& sprite;
	//texture sheet containing the animation textures
	sf::Texture& texture_sheet;
public:
	virtual ~AnimationComponent();
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	//adds an animation to the map
	void addAnimation(const std::string key, float animT, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int w, int h);
	const bool& play(const std::string key, const float& dt, const bool priority = false);
	const bool& play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority = false);

	//Accessor for the done variable
	const bool& isDone(const std::string key);
};
#endif
