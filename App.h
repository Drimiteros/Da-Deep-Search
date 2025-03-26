#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Input_events.h"
#include "Searchbar.h"
#include "Fetch_file.h"

using namespace std;
using namespace sf;

class App
{
private:
	string version = "Da Deep Search v.2.0";
	RenderWindow window;
	Event event;
	wstring search_bar_string;
	bool start_search = false;
	bool is_click_pressed = false;
	int drive_offset = 0;

	RectangleShape cursor;
	RectangleShape view_bounds;

public:
	Input_events input_events;
	Searchbar searchbar;
	Fetch_file fetch_file;

	App();
	void events();
	void loop();
	void update();
	void draw();
};

