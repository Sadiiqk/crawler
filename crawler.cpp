#include <iostream>
#include <string>
#include <boost/filesystem.hpp>

using namespace std;
namespace fs = boost::filesystem;

void search_directory(const fs::path& directory, const string& search_term) {
    if (!fs::is_directory(directory)) {
        cerr << "Error: " << directory.string() << " is not a valid directory." << endl;
        return;
    }

    for (fs::directory_entry& entry : fs::directory_iterator(directory)) {
        try {
            if (fs::is_directory(entry.path())) {
                search_directory(entry.path(), search_term);
            } else if (fs::is_regular_file(entry.path())) {
                ifstream file(entry.path().string());
                string line;
                while (getline(file, line)) {
                    if (line.find(search_term) != string::npos) {
                        cout << entry.path().string() << endl;
                        break;
                    }
                }
                file.close();
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << " when processing " << entry.path().string() << endl;
        }
    }
}

int main() {
    string search_term;
    cout << "Enter search term: ";
    getline(cin, search_term);

    search_directory(fs::current_path(), search_term);

    return 0;
}
