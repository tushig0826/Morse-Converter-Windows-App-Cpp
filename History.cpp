#include "History.h"


using namespace std;
//It is for Initializing history.txt file 
void History::createHistory()
{

	historyFile.open("history.txt");

}
//It is for appending string to the history.txt file 
void History::addToHistory(char* Add)
{
	historyFile << Add << endl;
}
//Appending lines into the history.txt file to display the results clean
void History::lineBreak()
{
	historyFile << "\n_________________________________________________\n";
}
//Closing the history.txt file
void History::closeFile()
{
	historyFile.close();
}
