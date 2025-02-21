#include <windows.h>
#include <iostream>
#include <fstream>
#include <shellapi.h>

void touchFile(const std::string& filename) {
    HANDLE hFile = CreateFile(
        filename.c_str(),
        FILE_WRITE_ATTRIBUTES,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    
    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Erreur : impossible d'ouvrir ou de créer le fichier." << std::endl;
        return;
    }
    
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    
    if (!SetFileTime(hFile, NULL, NULL, &ft)) {
        std::cerr << "Erreur : impossible de modifier l'horodatage." << std::endl;
    }
    
    CloseHandle(hFile);
}

void openFile(const std::string& filename) {
    ShellExecute(0, "open", filename.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage : " << argv[0] << " [-o] <nom_du_fichier>" << std::endl;
        return 1;
    }
    
    bool openFlag = false;
    std::string filename;
    
    if (argc == 3 && std::string(argv[1]) == "-o") {
        openFlag = true;
        filename = argv[2];
    } else {
        filename = argv[1];
    }
    
    touchFile(filename);
    
    if (openFlag) {
        openFile(filename);
    }
    
    return 0;
}
