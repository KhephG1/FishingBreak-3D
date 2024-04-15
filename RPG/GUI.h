#ifndef GUI_H
#define  GUI_H


enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED};

namespace GUI
{
	const float p2pX(const float percent, const sf::VideoMode& vm);
	const float p2pY(const float percent, const sf::VideoMode& vm);
	class Button
	{
	private:
		short unsigned buttonState;
		short unsigned id; 

		sf::Color text_idle, text_hover, text_active;
		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color idlecolour;
		sf::Color hovercolour;
		sf::Color activecolour;

		sf::Color Outlineidlecolour;
		sf::Color Outlinehovercolour;
		sf::Color Outlineactivecolour;



	public:
		Button(float x, float y, float width, float height, std::string text, sf::Font* font, 
			sf::Color Outline_idle, sf::Color Outline_hover, sf::Color Outline_active, 
			sf::Color text_idle, sf::Color text_hover, sf::Color text_active, 
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, short unsigned id =0);
		virtual ~Button();
		//Accessors
		const bool isPressed();
		const short unsigned& getID() const;
		const std::string getText() const;
		//Modifiers
		void setText(const std::string text);
		void setID(const short unsigned eyedee);
		//Functions
		void update(sf::Vector2i& mousePos);
		void render(sf::RenderTarget* target);
		const unsigned calccharsize() const;
	};

	class DropDownList {
	private:
		float keyTime;
		float keyTimeMax;
		sf::Font& font;
		Button* activeElement;
		std::vector<Button*> list;

		bool show_list;
	public:
		DropDownList(float x, float y, float width, float height, sf::Font& fnt, std::vector<std::string> a_list, unsigned default_idx);
		virtual ~DropDownList();
		const bool getkeyTime();
		void updateKeyTime(const float& dt);
		const unsigned short getlistID();
		void update(sf::Vector2i& mousePos, const float& dt);
		void render(sf::RenderTarget* target);
	};

	class textureSelector {
	private:
		float keytime;
		float keytimeMax;
		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::IntRect textureRect;
		bool active;
		bool hidden;
		float GridSize;
	public:
		sf::Vector2u mousePosGrid;
		textureSelector(float x, float y, float width, float height, float gridSize, const sf::Texture* texSheet, sf::Font& font);
		~textureSelector();


		//Accessors
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;
		bool& gethidden();
		//Functions
		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);
		void updateKeytime(const float& dt);
		const bool getKeytime();
		};
}
#endif
