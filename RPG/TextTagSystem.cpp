#include "stdafx.h"
#include "TextTagSystem.h"

TextTagSystem::TextTagSystem(std::string font_file)
{
	if (font.loadFromFile(font_file)) {
		std::cout << "ERROR::TEXTTAGSYSTEM::CONSTRUCTOR::Failed to load font" << font_file << std::endl;
	}
}

TextTagSystem::~TextTagSystem()
{
}

void TextTagSystem::createTextTag(unsigned tagType)
{
}

void TextTagSystem::removetextTag()
{
}

void TextTagSystem::update(const float& dt)
{
}

void TextTagSystem::render(sf::RenderTarget* target)
{
}


