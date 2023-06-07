#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

string loadData(string userDataPath) {
    ifstream userData (userDataPath);
    string userLocal;
    if (userData.is_open()) {
        // User data detected
        getline(userData, userLocal);
        return userLocal;
    } else {
        // No User Data
        cout << "Insert Your User Local. This can be found under C:/'Program Files (x86)'/Steam/userdata" << endl;
        cin >> userLocal;

        // Confirm User data
        regex validIDRegex ("[0-9]+");
        while (regex_search(userLocal, validIDRegex) == 0) {
            cout << "Inproper User Local format. Expecting number like: 275745052. Try again:" << endl;
            cin >> userLocal;
        }

        // Save User data
        ofstream saveUserData (userDataPath);
        if (saveUserData.is_open()) {
            saveUserData << userLocal;
            saveUserData.close();
            cout << "User Data Saved" << endl;
        }
        
        return userLocal;
    }
}

int main() {
    // Init
    string saveInformation;

    // Load local user data
    string localUserSave = loadData("cache");

    fs::path rootPath("C:\\Program Files (x86)\\Steam\\userdata\\");
    fs::path rorBase("632360\\remote\\UserProfiles");
    fs::path saveXML("fa826dc2-99e3-4ccb-9c5e-b7f5ec737491.xml");

    fs::path fullPath = rootPath / localUserSave / rorBase / saveXML;
    fs::path tempFullPath = rootPath / localUserSave / rorBase / "temp" / saveXML;

    ofstream tempFile (tempFullPath);
    ifstream saveFile (fullPath);

    // Load file
    cout << "Using save data: " << fullPath << endl;
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
        replaced = regex_replace(saveInformation, coins, "<coins>2147483640</coins>");
    } else {
        cout << "<coins> not detected. Are you sure this is the correct save XML?" << endl;
        return 1;
    }

    // Saving Files
    if (tempFile.is_open()) {
        tempFile << replaced;
        tempFile.close();
    } else {
        perror("Unable to save file");
        return 1;
    }
    remove(fullPath);
    if (rename(tempFullPath.string().c_str(), fullPath.string().c_str()) != 0) {
        perror("Saving file went wrong");
        return 1;
    }

    cout << "Replacement successful." << endl;
    return 0;
}
