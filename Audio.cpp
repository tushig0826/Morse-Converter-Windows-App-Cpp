#include "Audio.h"

//This function is initializing a sound for dot
void Audio::dotAudio()
{
	Beep(900, 300);
}
//This function is initializing a sound for dash
void Audio::dashAudio()
{
	Beep(900, 500);
}
//This function is for pausing or seperating the sound between dot and dash
void Audio::pauseAudio()
{
	Sleep(500);
}
//Main function that is making it possible to make sound from the string by finding dot and dash
void Audio::MorseBeeper(std::string str)
{
	int length = str.length();
	for (int i = 0; i < length; i++)
	{
		if (str[i] == '.')					//if it finds dot it will play dotAudio()
		{
			dotAudio();
		}
		else if (str[i] == '-')				//if it finds dot it will play dashAudio()
		{
			dashAudio();
		}
		else
		{
			pauseAudio();					//if it didn't find - or . it will pause the sound
		}
	}
}
/**
	This function is initializing listen text file to store morse code
	because of windows application cannot get the previously converted
	morse code by passing it within the cases. The comment will be
	detailed in the main.cpp
*/
void Audio::listen(char* insertMorse)
{
	listenAudio.open("listen.txt");
	listenAudio << insertMorse;
	listenAudio.close();

}