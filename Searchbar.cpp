#include "Searchbar.h"

Searchbar::Searchbar() {

	font.loadFromFile("src/Fonts/LTSuperior-Medium.otf");
	search_bar_text.setFont(font);
	search_bar_text.setFillColor(Color(255, 180, 150));
	search_bar_text.setString("Start typing...");
}

void Searchbar::update(RenderWindow& window, wstring& search_bar_string) {
	search_bar_text.setOrigin(search_bar_text.getLocalBounds().width / 2, 0);
	search_bar_text.setPosition(window.getSize().x / 2, window.getSize().y / 2 - 400);

	if (search_bar_string.size() == 0)
		search_bar_text.setString("Start typing...");
	else
		search_bar_text.setString(search_bar_string);
}

void Searchbar::draw(RenderWindow& window) {

	window.draw(search_bar_text);
}