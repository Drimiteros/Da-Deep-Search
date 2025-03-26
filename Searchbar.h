#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Searchbar
{
private:	
	Font font;
	Text search_bar_text;
	RectangleShape background;

public:
	Searchbar();
	void update(RenderWindow& window, wstring& search_bar_string);
	void draw(RenderWindow& window);
};

