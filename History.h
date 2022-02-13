#pragma once
#include <string>
#include <iostream>
#include <fstream>

//This class is using file management to create, append, and close files
class History {
private:
    std::ofstream historyFile; //using ofstream to create and write information to the file
public:
    void createHistory();
    void addToHistory(char* Add);
    void lineBreak();
    void closeFile();
};