#ifndef TEXTTAGSYSTEM_H
#define TEXTTAGSYSTEM_H
enum TagTypes {DEFAULT_TYPE, NEGATIVE, POSITIVE};
class TextTagSystem
{
private:
	class TextTag {
	private:
		sf::Text txt;
		float dirY;
		float dirX;
		float lifeTime;
		float speed;


	public:
		TextTag(sf::Font& font, std::string text, float pos_x, float pos_y,
			sf::Color color, unsigned char_size, float life_t, float spd, float dir_x, float dir_y) {
			txt.setFont(font);
			txt.setPosition(pos_x, pos_y);
			dirX = dir_x;
			dirY = dir_y;
			lifeTime = life_t;
			speed = spd;
			txt.setFillColor(color);
			txt.setCharacterSize(char_size);


			
		}
		~TextTag();
		const bool isactive() const{
			return lifeTime <= 0;
		}
		//Functions

		void update(const float& dt) {
			if (lifeTime > 0.f) {
				lifeTime -= 100 * dt;
				txt.move(dirX * speed * dt, dirY * speed * dt);

			}
			
		}
		void render(sf::RenderTarget* target) {
			target->draw(txt);
		}

	};
	std::vector<TextTag*> Tags;
	sf::Font font;
public:
	TextTagSystem(std::string font_file);
	virtual ~TextTagSystem();
	void createTextTag(unsigned tagType);
	void removetextTag();
	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

#endif