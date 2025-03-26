#include "App.h"

App::App() {
	
	window.create(VideoMode(1000, 850), version, Style::Close);

	cursor.setSize(Vector2f(2, 2));
	view_bounds.setFillColor(Color(45, 45, 50));
	view_bounds.setPosition(0, 200);
	view_bounds.setSize(Vector2f(window.getSize().x, 800));

	fetch_file.get_available_drives();
}

void App::events() {
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed)
			window.close();

		input_events.type_event(event, search_bar_string, start_search, drive_offset);
		input_events.click_event(event, is_click_pressed);
	}
}

void App::loop() {

	while (window.isOpen()) {
		events();

		update();

		window.clear(Color(55, 55, 60));

		draw();

		window.display();
	}
}

void App::update() {

	cursor.setPosition(window.mapPixelToCoords(Mouse::getPosition(window)));
	searchbar.update(window, search_bar_string);
	fetch_file.found_file(search_bar_string, start_search, drive_offset);
	fetch_file.execute_file(cursor, is_click_pressed);
}

void App::draw() {
	window.draw(view_bounds);
	searchbar.draw(window);
	fetch_file.draw(window);
}