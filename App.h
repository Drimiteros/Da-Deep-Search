#pragma once
#include <iostream>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include "Input_events.h"
#include "Searchbar.h"
#include "Drive_explorer.h"

using namespace std;
using namespace sf;

class App
{
private:
	string version = "Da Deep Search v.2.1_2";
	RenderWindow window;
	Event event;
	wstring search_bar_string;
	bool start_search = false;
	bool is_click_pressed = false;
	int scroll_value = 0;

	RectangleShape cursor;
	RectangleShape view_bounds;

	HWND hwnd;
	Clock window_state_clock;

public:
	Input_events input_events;
	Searchbar searchbar;
	Drive_explorer drive_explorer;

	App();
	void events();
	void loop();
	void update();
	void draw();
};

