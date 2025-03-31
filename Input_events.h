#pragma once
#include <iostream>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Input_events
{
private:

public:
	Input_events();
	void keyboard_event(Event& event, wstring& search_bar_string, bool& start_search);
	void mouse_event(Event& event, bool& is_click_pressed, int& scroll_value, RenderWindow& window);
};

