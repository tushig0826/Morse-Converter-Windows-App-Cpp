#include "Morse.h"
//Node function is making it possible to set aside the characters of the binary tree
BinaryTree* Morse::Node(char item, int key)
{
	BinaryTree* tmp = new BinaryTree[sizeof(BinaryTree)];

	tmp->characters = item;
	tmp->key = key;
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
}
//This function is for adding nodes
//It finds characters by if its key value goes right or left 
BinaryTree* Morse::AddNode(BinaryTree* start, char value, int key)
{
	if (start == NULL)
		return Node(value, key);
	if (key < start->key)
		start->left = AddNode(start->left, value, key);
	else if (key > start->key)
		start->right = AddNode(start->right, value, key);
	return start;
}
//Constructor has binary tree
Morse::Morse()
{
	char characters[61] = " tmo#09#8:gqz#,7nky()c#!dx/b=6-eawj1'p#@r#+.l#&iu#2#?fsv3h45";	//Available characters in order of their insertion
	int keys[61] = { 31, 15, 8, 4, 2, 1, 3, 5, 6, 7, 10, 9, 13, 12, 11, 14, 23, 19, 16, 18, 17, 22, 21, 20, 26, 24, 25, 28, 27, 30, 29, 47, 39, 35, 34, 32, 33, 38, 36, 37, 43, 40, 42, 41, 45, 44, 46, 54, 52, 49, 48, 50, 51, 53, 57, 56, 55, 59, 58, 60 }; /*key values of characters*/
	start = AddNode(start, characters[0], keys[0]);
	for (int i = 1; i < 61; i++)															//inserting all available characters to tree using AddNode
	{
		AddNode(start, characters[i], keys[i]);
	}
}
//Deconstructor
Morse::~Morse()
{
	deleteNode(start);
}
char Morse::GetText(const char* str)
{
	int size = strlen(str);						//getting length of the str
	BinaryTree* pointer = start;
	for (int i = 0; i < size; i++)
	{
		if (str[i] == ' ')						//| is space
		{
			break;
		}

		if (str[i] == '-')						//dash is left
		{
			pointer = pointer->left;
		}

		if (str[i] == '.')						//dot is right
		{
			pointer = pointer->right;
		}

		if (pointer == NULL)					//if start couldn't find anything it will return 0
		{
			printf("Invalid code!\n");
			return 0;
		}
	}
	return pointer->characters;
}

//Essential function to convert morse code input to text
const std::string Morse::MorseToText(const char* str1)
{
	char* str_token, * token1;
	std::string output = "";
	char* tmp = new char[strlen(str1)];
	for (int i = 0; i < strlen(str1); i++)
	{
		tmp[i] = str1[i];
	}
	str_token = strtok_s(tmp, " ", &token1);		//I had to make it return to a pointer to the first character
													//using strtok is splitting the string 
	while (str_token != NULL)
	{
		output = output + GetText(str_token);
		str_token = strtok_s(NULL, " ", &token1);	//getting spaces between morse codes
	}
	return output;									//Initializing it by non-void function will be easier to display its output in windows application
}

void Morse::statistics()
{

	for (int i = 0; i < 49; i++)					//print all statistics
	{
		printf("%c < -> %s\n", characters[i].letter, characters[i].MorseCode);
	}
}

//Deleting the node function
void Morse::deleteNode(BinaryTree* root)
{
	if (root == NULL)								//if already empty return
	{
		return;
	}

	delete[] root->left;
	delete[] root->right;
	delete[] root;
}


//Essential function to convert text input to Morse code
const std::string Morse::TextToMorse(const char* txt)
{
	int length = strlen(txt);
	std::string output = "";
	int StringLen = 0;
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < 49; j++)									//comparing the characters and morse code
		{
			if (txt[i] == characters[j].letter)
			{
				StringLen = +strlen(characters[j].MorseCode);

				const char* morseStr = new char[StringLen];
				morseStr = characters[j].MorseCode;
				output = output + " " + characters[j].MorseCode;		//it will return output with " " space

			}
		}
	}

	return output;														//The main reason of returning it will make it easier to display in the windows application
}