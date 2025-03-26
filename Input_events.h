#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Input_events
{
private:

public:
	Input_events();
	void type_event(Event& event, wstring& search_bar_string, bool& start_search, int& drive_offset);
	void click_event(Event& event, bool& is_click_pressed);
};

