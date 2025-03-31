#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <filesystem>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>

using namespace std;
using namespace sf;
namespace fs = std::filesystem;

class Drive_explorer
{
private:
    Font font;
    Text found_files_text;
    Text drive_info_text;
    Text search_state_text;
    RectangleShape file_select_bar;
    vector<Text> found_files_text_vector;
    vector<Text> drive_letter_text;
    vector<RectangleShape> drive_select_box;
    vector<bool> disabled_drive;

public:
    vector<wstring> found_files_string_vector;
    wstring root_path;
    int iterations = 0;
    int counter = 0;
    int get_position = 0;
    int drive_offset = 0;
    bool begin_iteration = false;

    Drive_explorer();
    void get_available_drives();
    void select_drives(RectangleShape& cursor, bool& is_click_pressed);
    void found_file(RenderWindow& window, wstring& search_bar_string, bool& start_search);
    void execute_file(RectangleShape& cursor, bool& is_click_pressed);
    void draw(RenderWindow& window, RectangleShape& cursor, bool& start_search, int& scroll_value, RectangleShape& view_bounds);
};

