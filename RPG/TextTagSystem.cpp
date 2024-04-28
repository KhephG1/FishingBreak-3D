#include "stdafx.h"
#include "TextTagSystem.h"

void TextTagSystem::initVariables()
{
}

void TextTagSystem::initTagTemplates()
{
	tagTemplates[DEFAULT_TYPE] = new TextTag{font, "text", 200,200,sf::Color::White,50,60.f,100.f,0,-1};
	tagTemplates[EXPERIENCE] = new TextTag{ font,"text",200,200,sf::Color::Cyan,50,60.f,100.f,0,1 };
	tagTemplates[POSITIVE] = new TextTag{ font,"text",200,200,sf::Color::Green,50,60.f,100.f,0,-1 };
	tagTemplates[NEGATIVE] = new TextTag{ font,"text",200,200,sf::Color::Red,50,60.f,100.f,0,-1 };
}

void TextTagSystem::initFonts(std::string font_file)
{
	if (!font.loadFromFile(font_file)) {
		std::cout << "ERROR::TEXTTAGSYSTEM::CONSTRUCTOR::Failed to load font" << font_file << std::endl;
	}
	
}

TextTagSystem::TextTagSystem(std::string font_file)
{
	initFonts(font_file);
	initTagTemplates();
	initVariables();
	
}

TextTagSystem::~TextTagSystem()
{
	//free tags
	for (auto* tag : Tags) {
		delete tag;
	}
	//free templates
	for (auto& pair : tagTemplates) {
		delete pair.second;
	}
}

void TextTagSystem::createTextTagString(unsigned tagType, const float pos_x, const float pos_y, const std::string str, const std::string prefix = "", const std::string postfix = "")
{
	std::stringstream ss;
	ss << prefix<<" "<<str<<" "<<postfix;
	Tags.push_back(new TextTag{ tagTemplates[tagType],pos_x,pos_y,ss.str()});
}

void TextTagSystem::createTextTagString(unsigned tagType, const float pos_x, const float pos_y, const int val, const std::string prefix = "", const std::string postfix = "")
{
	std::stringstream ss;
	ss <<prefix<<" "<< val<<" "<<postfix;
	Tags.push_back(new TextTag{ tagTemplates[tagType],pos_x,pos_y,ss.str()});
}
void TextTagSystem::createTextTagString(unsigned tagType, const float pos_x, const float pos_y, const double d, const std::string prefix = "", const std::string postfix = "")
{
	std::stringstream ss;
	ss <<prefix<<" "<< d<<" "<<postfix;
	Tags.push_back(new TextTag{ tagTemplates[tagType],pos_x,pos_y,ss.str() });
}
void TextTagSystem::removetextTag()
{
}

void TextTagSystem::update(const float& dt)
{
	for (size_t i{}; i < Tags.size(); i++) {
		Tags.at(i)->update(dt);
		std::cout << Tags.at(i)->lifeTime << std::endl;
		if (Tags.at(i)->isactive()) {
			delete Tags.at(i);
			Tags.erase(Tags.begin() + i);
		}
	}
	
}

void TextTagSystem::render(sf::RenderTarget* target)
{
	int count{};
	for (auto& tag : Tags) {
		tag->render(target); 
	}
}


