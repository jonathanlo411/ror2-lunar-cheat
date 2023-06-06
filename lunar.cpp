#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main() {
    // Init
    string saveInformation;
    string saveFilePath = "fa826dc2-99e3-4ccb-9c5e-b7f5ec737491.xml";
    string tempSaveFilePath = "./temp_" + saveFilePath;
    string relativeSaveFilePath = "./" + saveFilePath;
    ofstream tempFile (tempSaveFilePath);
    ifstream saveFile (relativeSaveFilePath);

    // Load file
    if (saveFile.is_open()) {
        getline(saveFile, saveInformation);
        saveFile.close();
    } else {
        cout << "Unable to load save file." << endl;
        return 1;
    }
    
    // Regex Replace Coins
    regex coins ("<coins>[0-9]+<\\/coins>");
    string replaced = "";
    if (regex_search(saveInformation, coins)) {
        replaced = regex_replace(saveInformation, coins, "<coins>99999999</coins>");
        cout << "Replacement successful." << endl;
    } else {
        cout << "<coins> not detected. Are you sure this is the correct save XML?" << endl;
        return 1;
    }

    // Saving Files
    if (tempFile.is_open()) {
        tempFile << replaced;
        tempFile.close();
    } else {
        cout << "Unable to load temp file," << endl;
        return 1;
    }
    remove(relativeSaveFilePath.c_str());
    if (rename(tempSaveFilePath.c_str(), relativeSaveFilePath.c_str()) != 0) {
        cout << "Saving file went wrong." << endl;
        return 1;
    }

    return 0;
}
