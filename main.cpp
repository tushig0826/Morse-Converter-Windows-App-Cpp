/**
	I am using <windows.h> library for making it windows application.
	<tchar.h> is for defining the char which resolves ultimately
	to wchar_t. If it is built with UNICODE enabled we do not need to
	use tchar.
*/
#define _CRT_SECURE_NO_WARNINGS		// Remove secure warnings 

#include "Morse.h"
#include <windows.h>
#include "Audio.h"
#include "History.h"
#include <tchar.h>
#include <stdio.h>

//My program has 4 buttons and I defined them:
#define LISTEN_BUTTON 2
#define HISTORY_BUTTON 3
#define CONVERT_BUTTON 4
#define NEWCONVERT_BUTTON 5

const char g_szClassName[] = "Tushig's Morse Converter";				//Title of the program

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AddButtons(HWND);
HWND hEdit, hText, hMorse, hOutput, textFile;							//Declarations of the textbox windows

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
	HWND hwnd;			//Handle for the window
	MSG messages;		//Messages to the saved application
	WNDCLASSEX winclass;	//Data struct for the windows class

	//Window stucture:
	winclass.hInstance = hInstance;
	winclass.lpszClassName = g_szClassName;
	winclass.lpfnWndProc = WndProc;			//function called by windows
	winclass.style = CS_DBLCLKS;				//catch double clicks
	winclass.cbSize = sizeof(WNDCLASSEX);

	//Default icon and mouse pointers:
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.lpszMenuName = NULL;				//no menu
	winclass.cbClsExtra = 0;					//no extra bytes after the window class
	winclass.cbWndExtra = 0;					//windows instance structure

	//Using windows's default color as the background color of the window
	winclass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);	//COLOR_BACKGROUND;

	//Registering the window class, and it quits if fail
	if (!RegisterClassEx(&winclass))
		return 0;

	//Creating the application

	hwnd = CreateWindowEx(
		0,									//extendend possibilities for variation
		g_szClassName,						//class name
		"Tushig's Morse Converter",			//Title of the top
		WS_SYSMENU | WS_MINIMIZEBOX,		//default window
		CW_USEDEFAULT,						//windows's position
		CW_USEDEFAULT,						//where windows ends up on display
		800,								//width
		500,								//height
		HWND_DESKTOP,						//app is child window to the display
		NULL,								//no menu
		hInstance,							//Instance handler
		NULL);								//No window creatiom data

	//Making the window visible on display
	ShowWindow(hwnd, nCmdShow);

	//run the message loop until GetMessage() returns 0
	while (GetMessage(&messages, NULL, 0, 0))
	{
		while (GetMessage(&messages, NULL, 0, 0))
		{
			TranslateMessage(&messages);		//translate virtual key to character
			DispatchMessage(&messages);			//send message to WndProc
		}
		return messages.wParam;
	}

}


//It is called by the DispatchMessage() function
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)			//handling message
	{
	case WM_CREATE:				//Window will be initialized in this case

		AddButtons(hwnd);		//AddButtons function has my program's buttons and textboxes (I initialized it in the end of this file)
		break;
	case WM_COMMAND:			//Operations and functionalities of buttons will be initialized in this case
		switch (LOWORD(wParam))
		{
		case CONVERT_BUTTON: //It is for converting text to morse
		{
			Morse Morse1;
			History history;
			Audio aud;

			history.createHistory();
			char text[50], outText[50];

			GetWindowText(hText, text, 50);			//Getting user input from hText textbox
			try
			{
				if (strlen(text) == 0)
				{
					throw 0;
				}
				else
				{
					history.addToHistory(text);
					strcpy_s(outText, Morse1.TextToMorse(text).c_str());		//Converting text to morse and copying it into the outText

					SetWindowText(hOutput, outText);							//Displaying outText in the hOutput textbox
					history.addToHistory(outText);								//adding to history
					history.lineBreak();
					history.closeFile();
					aud.listen(outText);										//Storing converted morse to the listen.txt file
				}
			}
			catch (int num)
			{
				std::string tmp = "Invalid! The text box is empty!";
				SetWindowText(hOutput, tmp.c_str());
			}
			break;
		}

		case NEWCONVERT_BUTTON:						//It is for converting morse into the text it has same functionality with the previous case 
		{

			Morse Morse2;
			History history;

			char  morse[50], outMorse[50];

			GetWindowText(hMorse, morse, 50);
			try
			{
				if (strlen(morse) == 0)
				{
					throw 0;

				}
				else
				{
					history.addToHistory(morse);

					strcpy_s(outMorse, Morse2.MorseToText(morse).c_str());
					SetWindowText(hOutput, outMorse);
					history.addToHistory(outMorse);
					history.lineBreak();

					history.closeFile();
				}
			}
			catch (int num)
			{
				std::string tmp = "Invalid! The text box is empty!";
				SetWindowText(hOutput, tmp.c_str());

			}
			break;
		}
		case HISTORY_BUTTON:									//Show message box if the user tap history button
		{
			::MessageBox(hwnd, "History saved automatically in the file directory", "Alert!", MB_OK);
			break;
		}
		case LISTEN_BUTTON:										//It is for listening the converted morse code
		{
			std::string audioL;
			std::ifstream file;
			Audio sound;
			file.open("listen.txt");							//opening and reading from listen.txt file
			getline(file, audioL);
			sound.MorseBeeper(audioL);							//MorseBeeper function will play the sound by finding dot and dashes

			break;
		}
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);          // Exit from the program
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

//I initialized buttons and textbox windows in this function
void AddButtons(HWND hWnd)
{

	CreateWindow("Static", "Enter Text Here:", WS_VISIBLE | WS_CHILD, 100, 50, 100, 40, hWnd, (HMENU)1, NULL, NULL);
	hText = CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 50, 180, 40, hWnd, (HMENU)1, NULL, NULL);

	CreateWindow("Static", "Enter Morse Code Here:", WS_VISIBLE | WS_CHILD, 100, 90, 100, 40, hWnd, (HMENU)1, NULL, NULL);
	hMorse = CreateWindow("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 90, 180, 40, hWnd, (HMENU)1, NULL, NULL);

	CreateWindow("Button", "Convert to Morse", WS_VISIBLE | WS_CHILD, 100, 140, 120, 40, hWnd, (HMENU)CONVERT_BUTTON, NULL, NULL);

	CreateWindow("Button", "Convert to Text", WS_VISIBLE | WS_CHILD, 260, 140, 120, 40, hWnd, (HMENU)NEWCONVERT_BUTTON, NULL, NULL);

	hOutput = CreateWindow("Edit", "Result:", WS_VISIBLE | WS_CHILD | WS_BORDER, 450, 50, 250, 80, hWnd, (HMENU)1, NULL, NULL);

	textFile = CreateWindow("STATIC", "\nStatistics:"
		"\na .-, b -..., c -.-., d -.., e ., f ..-., g --., h ...., i .., j .---, k -.-, l .-.., m --, n -., o ---, p .--."
		"q --.-, r .-., s ...,  t -, u ..-, v ...-, w .--, x -..-, y -.--, z --..\n"
		"\nNumbers:"
		"\n0 - - - - -, 1 .- - - -, 2 ..- - -, 3 ...- -, 4 ....-, 5 ....., 6 -...., 7 - -..., 8 - - -.., 9 - - - -.\n"
		"\nCharacters:"
		"\n: --..., , --..--, ( -.--., ) -.--.-, ! -.-.--, / -..-., = -...-, - -....-, @ .--.-., + .-.-., . .-.-.-, '' .-..-.\n", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 200, 600, 200, hWnd, NULL, NULL, NULL);

	CreateWindow("Button", "History", WS_VISIBLE | WS_CHILD, 450, 140, 110, 40, hWnd, (HMENU)HISTORY_BUTTON, NULL, NULL);

	CreateWindow("Button", "Listen", WS_VISIBLE | WS_CHILD, 590, 140, 110, 40, hWnd, (HMENU)LISTEN_BUTTON, NULL, NULL);

}


//References:
/**
	http://eik.bme.hu/~csurgai/Mswin_en/Mswin_en.htm
	https://www.cplusplus.com/reference/string/string/c_str/
	https://www.dropbox.com/s/k7fb15c3f1o4yf8/forgers-win32-tutorial.pdf?dl=0
	https://docs.microsoft.com/en-us/windows/win32/learnwin32/winmain--the-application-entry-point
	http://www.winprog.org/tutorial/controls.html
	https://www.youtube.com/watch?v=FXrulJXMiU8
	https://www.youtube.com/c/ThePentamollisProject/videos
*/