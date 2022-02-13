#pragma once
#include <windows.h>
#include <string>
#include <fstream>

/**
	This class is using Beep() function windows.h external
	library to make it possible to initialize the audio
*/
class Audio
{
private:
	std::ofstream listenAudio;		//using ofstream to create and write information to the file
public:
	void dotAudio();
	void dashAudio();
	void pauseAudio();
	void MorseBeeper(std::string str);
	void listen(char* insertMorse);

};