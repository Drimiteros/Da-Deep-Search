#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>

using namespace std;
namespace fs = std::filesystem;

int main() {
    _setmode(_fileno(stdout), _O_WTEXT);
    _setmode(_fileno(stdin), _O_WTEXT);

    wstring root_path = L"D:\\";
    wstring target_file;
    vector<wstring>files_found;
    int iterations = 0;
    int files_found_count = 0;

    wcout << L"Enter target file or directory: ";
    getline(wcin, target_file);
    system("cls");
    wcout << L"Searching for " <<  target_file << "..." << endl;
    
    try {
        for (const auto& entry : fs::recursive_directory_iterator(root_path, fs::directory_options::skip_permission_denied)) {
            iterations++;
            for (int i = 0;i < target_file.size(); i++) {
                if (entry.path().filename().wstring().find(target_file[i]))
            }
            if (entry.path().filename().wstring() == target_file) {
                files_found.push_back(entry.path().wstring());
                files_found_count++;
            }
        }
        system("cls");
        wcout << "No more results found." << endl;
    }
    catch (const fs::filesystem_error& e) {
        wcerr << "Error: " << e.what() << endl;
    }

    system("cls");
    wcout << "Directory iterations: " << iterations << endl;
    wcout << "Files found: "<< files_found_count << "\n" << endl;
    for (int i = 0;i < files_found.size();i++)
        wcout << "[*] " << files_found[i] << endl;

    return 0;
}
