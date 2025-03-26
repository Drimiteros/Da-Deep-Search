#include "Fetch_file.h"

Fetch_file::Fetch_file() {

    font.loadFromFile("src/Fonts/LTSuperior-Medium.otf");
    found_files_text.setFont(font);
    found_files_text.setFillColor(Color(255, 210, 190));
    found_files_text.setCharacterSize(15);
}

void Fetch_file::get_available_drives() {
    DWORD driveMask = GetLogicalDrives();
    for (char drive = 'A'; drive <= 'Z'; drive++) {
        // If drive exists
        if (driveMask & (1 << (drive - 'A')))
            drive_letter.push_back(drive);
    }
}

void Fetch_file::found_file(wstring& search_bar_string, bool& start_search, int& drive_offset) {
    if (start_search) {
        try { 
            if ((drive_letter.size() - 1) + drive_offset < drive_letter.size()) {
                for (int i = (drive_letter.size() - 1) + drive_offset; i >= 0; i--) {
                    wstring convert_drive_wchar_t(1, drive_letter[i]);
                    root_path = convert_drive_wchar_t + ":\\";
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
                start_search = false;
                wcout << "No more results found." << endl;
                wcout << "Directory iterations: " << iterations << endl;
                wcout << "Files found: " << found_files_text_vector.size() << "\n" << endl;
            }
        }
        catch (const fs::filesystem_error& e) {
            wcerr << "Error: " << e.what() << endl;
            wcout << "No more results found." << endl;
            wcout << "Directory iterations: " << iterations << endl;
            wcout << "Files found: " << found_files_text_vector.size() << "\n" << endl;
            drive_offset++;
        }
    }
}

void Fetch_file::execute_file(RectangleShape& cursor, bool& is_click_pressed) {
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
            }
        }
        is_click_pressed = false;
    }
}

void Fetch_file::draw(RenderWindow& window) {

    for (int i = 0;i < found_files_text_vector.size();i++) {
        found_files_text_vector[i].setPosition(10, 210 + (i * 25));
        window.draw(found_files_text_vector[i]);
    }
}