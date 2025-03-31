#include "Drive_explorer.h"

Drive_explorer::Drive_explorer() {

    font.loadFromFile("src/Fonts/LTSuperior-Medium.otf");
    found_files_text.setFont(font);
    found_files_text.setFillColor(Color(255, 210, 190));
    found_files_text.setCharacterSize(15);

    drive_info_text.setFont(font);
    drive_info_text.setCharacterSize(15);
    drive_info_text.setFillColor(Color(225, 180, 160));
    drive_info_text.setString("Drives to search: ");
    drive_info_text.setPosition(5, 180);

    search_state_text.setFont(font);
    search_state_text.setCharacterSize(15);
    search_state_text.setFillColor(Color(225, 180, 160));
    search_state_text.setString("Searching...");
    search_state_text.setOrigin(search_state_text.getLocalBounds().width / 2, search_state_text.getLocalBounds().height / 2);

    file_select_bar.setSize(Vector2f(1000, 20));
    file_select_bar.setFillColor(Color(255, 210, 190));
    file_select_bar.setPosition(9999, 9999);
}

void Drive_explorer::get_available_drives() {

    DWORD driveMask = GetLogicalDrives();
    for (char drive = 'A'; drive <= 'Z'; drive++) {
        // If drive exists
        if (driveMask & (1 << (drive - 'A'))) {
            drive_letter_text.push_back(Text());
            drive_letter_text.back().setFont(font);
            drive_letter_text.back().setCharacterSize(15);
            drive_letter_text.back().setFillColor(Color(105, 60, 40));
            drive_letter_text.back().setPosition(10, 180);
            drive_letter_text.back().setString(wstring(1, drive));

            drive_select_box.push_back(RectangleShape());
            drive_select_box.back().setSize(Vector2f(15, 15));
            drive_select_box.back().setFillColor(Color(255, 255, 150));

            disabled_drive.push_back(0);
        }
    }

    for (int i = 0; i < drive_letter_text.size(); i++) {
        drive_select_box[i].setPosition(90 + (i * 20), 183);
        drive_letter_text[i].setPosition(90 + (i * 20), 180);
    }
    drive_info_text.setString("Scan drives: ");
}

void Drive_explorer::select_drives(RectangleShape& cursor, bool& is_click_pressed) {

    if (is_click_pressed) {
        for (int i = 0; i < drive_letter_text.size(); i++) {
            if (cursor.getGlobalBounds().intersects(drive_select_box[i].getGlobalBounds()) && disabled_drive[i] == false) {
                disabled_drive[i] = true;
                is_click_pressed = false;
                break;
            }
            if (cursor.getGlobalBounds().intersects(drive_select_box[i].getGlobalBounds()) && disabled_drive[i] == true) {
                disabled_drive[i] = false;
                is_click_pressed = false;
                break;
            }
        }
    }
}

void Drive_explorer::found_file(RenderWindow& window, wstring& search_bar_string, bool& start_search) {

    if (begin_iteration) {
        found_files_text_vector.clear();
        found_files_string_vector.clear();
        try { 
            if ((drive_letter_text.size() - 1) + drive_offset < drive_letter_text.size()) {
                for (int i = (drive_letter_text.size() - 1) + drive_offset; i >= 0; i--) {
                    if (disabled_drive[i] == false) {
                        wstring current_drive = drive_letter_text[i].getString();
                        root_path = current_drive + ":\\";
                        wcout << "Searching path:" << root_path << endl;
                        for (const auto& entry : fs::recursive_directory_iterator(root_path, fs::directory_options::skip_permission_denied)) {
                            iterations++;
                            wstring ex = entry.path().filename().wstring();
                            if (ex.find(search_bar_string) != wstring::npos) {
                                found_files_text.setString(entry.path().wstring());
                                found_files_text_vector.push_back(found_files_text);
                                found_files_string_vector.push_back(entry.path().wstring());
                            }
                        }
                    }
                }
                wcout << "No more results found." << endl;
                wcout << "Directory iterations: " << iterations << endl;
                wcout << "Files found: " << found_files_text_vector.size() << "\n" << endl;
                start_search = false;
                begin_iteration = false;
                drive_offset = 0;
            }
        }
        catch (const fs::filesystem_error& e) {
            wcerr << "Error: " << e.what() << endl;
            wcout << "No more results found." << endl;
            wcout << "Directory iterations: " << iterations << endl;
            wcout << "Files found: " << found_files_text_vector.size() << "\n" << endl;
            drive_offset++;
            start_search = false;
            begin_iteration = false;
            drive_offset = 0;
        }
    }
}

void Drive_explorer::execute_file(RectangleShape& cursor, bool& is_click_pressed) {

    if (is_click_pressed) {
        for (int i = 0; i < found_files_text_vector.size(); i++) {
            if (cursor.getGlobalBounds().intersects(found_files_text_vector[i].getGlobalBounds())) {

                // Convert wstring to const wchar_t* for CreateProcessW
                const wchar_t* program = found_files_string_vector[i].c_str();

                // Execute and wait for process to finish
                if (ShellExecuteW(NULL, L"open", program, NULL, NULL, SW_SHOWNORMAL) <= (HINSTANCE)32)
                    wcerr << L"Failed to open file. Error: " << GetLastError() << endl;
                else
                    wcerr << L"Failed to start process. Error: " << GetLastError() << endl;

                is_click_pressed = false;
            }
        }
    }
}

void Drive_explorer::draw(RenderWindow& window, RectangleShape& cursor, bool& start_search, int& scroll_value, RectangleShape& view_bounds) {

    for (int i = 0; i < drive_letter_text.size(); i++) {
        if (!disabled_drive[i])
            window.draw(drive_select_box[i]);
        window.draw(drive_letter_text[i]);
    }

    window.draw(drive_info_text);
    if (start_search) {
        search_state_text.setPosition(window.getSize().x / 2, window.getSize().y / 2 - 250);
        window.draw(search_state_text);
        begin_iteration = true;
    }

    for (int i = 0;i < found_files_text_vector.size();i++) {
        if (cursor.getGlobalBounds().intersects(found_files_text_vector[i].getGlobalBounds())) {
            file_select_bar.setPosition(found_files_text_vector[i].getPosition());
            found_files_text_vector[i].setFillColor(Color::Black);
        }
        if (!cursor.getGlobalBounds().intersects(found_files_text_vector[i].getGlobalBounds())) {
            found_files_text_vector[i].setFillColor(Color(255, 210, 190));
            file_select_bar.setPosition(9999, 9999);
        }
        window.draw(file_select_bar);
        found_files_text_vector[i].setPosition(10, 210 + (i * 25) + (scroll_value * 25));
        if (found_files_text_vector[i].getGlobalBounds().intersects(view_bounds.getGlobalBounds()))
            window.draw(found_files_text_vector[i]);
    }
}