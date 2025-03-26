#include "Input_events.h"

Input_events::Input_events() {

}

void Input_events::type_event(Event& event, wstring& search_bar_string, bool& start_search, int& drive_offset) {
	if (event.type == Event::TextEntered && !Keyboard::isKeyPressed(Keyboard::Enter) && !Keyboard::isKeyPressed(Keyboard::Backspace))
		search_bar_string += event.text.unicode;
	if (event.type == Event::TextEntered && !Keyboard::isKeyPressed(Keyboard::Enter) && Keyboard::isKeyPressed(Keyboard::Backspace))
		search_bar_string = search_bar_string.substr(0, search_bar_string.size() - 1);
	if (event.type == Event::TextEntered && !Keyboard::isKeyPressed(Keyboard::Enter) && Keyboard::isKeyPressed(Keyboard::Backspace) && Keyboard::isKeyPressed(Keyboard::LShift))
		search_bar_string.clear();
	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		start_search = true;
		drive_offset = 0;
	}
}

void Input_events::click_event(Event& event, bool& is_click_pressed) {
	if (event.type == Event::MouseButtonPressed) {
		if (Mouse::isButtonPressed(Mouse::Left))
			is_click_pressed = true;
	}
	else
		is_click_pressed = false;
}