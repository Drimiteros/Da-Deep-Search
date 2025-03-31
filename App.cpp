#include "App.h"

App::App() {

	window.create(VideoMode(1000, 850), version, Style::Close);

	HWND hwnd = window.getSystemHandle();
	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_TOOLWINDOW);

	cursor.setSize(Vector2f(2, 2));
	view_bounds.setFillColor(Color(45, 45, 50));
	view_bounds.setPosition(0, 205);
	view_bounds.setSize(Vector2f(window.getSize().x, 800));

	drive_explorer.get_available_drives();
}

void App::events() {
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed)
			window.close();

		input_events.keyboard_event(event, search_bar_string, start_search);
		input_events.mouse_event(event, is_click_pressed, scroll_value, window);
	}
}

void App::loop() {

	while (window.isOpen()) {
		events();

		window.clear(Color(55, 55, 60));

		update();

		draw();

		window.display();
	}
}

void App::update() {

	// Update the window state
	HWND hwnd = window.getSystemHandle();
	if (Keyboard::isKeyPressed(Keyboard::Space) && Keyboard::isKeyPressed(Keyboard::LControl) && window_state_clock.getElapsedTime().asSeconds() > 0.4) {
		if (IsIconic(hwnd))
			ShowWindow(hwnd, SW_RESTORE);
		else
			ShowWindow(hwnd, SW_MINIMIZE);
		window_state_clock.restart();
	}

	cursor.setPosition(window.mapPixelToCoords(Mouse::getPosition(window)));
	searchbar.update(window, search_bar_string);
	drive_explorer.select_drives(cursor, is_click_pressed);
	drive_explorer.found_file(window, search_bar_string, start_search);
	drive_explorer.execute_file(cursor, is_click_pressed);
}

void App::draw() {
	window.draw(view_bounds);
	searchbar.draw(window);
	drive_explorer.draw(window, cursor, start_search, scroll_value, view_bounds);
}