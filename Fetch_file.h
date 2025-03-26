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

class Fetch_file
{
private:
    Font font;
    Text found_files_text;
    vector<Text> found_files_text_vector;
    vector<wchar_t> drive_letter;

public:
    vector<wstring> found_files_string_vector;
    wstring root_path;
    int iterations = 0;
    int counter = 0;
    int get_position = 0;

    Fetch_file();
    void get_available_drives();
    void found_file(wstring& search_bar_string, bool& start_search, int& drive_offset);
    void execute_file(RectangleShape& cursor, bool& is_click_pressed);
    void draw(RenderWindow& window);
};

