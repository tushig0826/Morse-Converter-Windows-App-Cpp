#ifndef MORSE_H
#define MORSE_H
//#pragma once

#include <iostream>
#include <string.h>

//Initializing binary tree using linked list
typedef struct BinaryTree {
	char characters;
	int key;
	struct BinaryTree* left;
	struct BinaryTree* right;
}
BinaryTree;

//Initializing the structure of library contains characters and strings
typedef struct MorseLibrary {
	char letter;
	const char* MorseCode;
}
MorseLibrary;




//Iinitializing essential class of this project
//It does main conversions
class Morse {
private:
	BinaryTree* start = NULL;
	//Initializing array with all characters and their translations in Morse code
	MorseLibrary characters[49] = {
		{'a', ".-"},
		{'b', "-..."},
		{'c', "-.-."},
		{'d', "-.."},
		{'e', "."},
		{'f', "..-."},
		{'g', "--."},
		{'h', "...."},
		{'i', ".."},
		{'j', ".---"},
		{'k', "-.-"},
		{'l', ".-.."},
		{'m', "--"},
		{'n', "-."},
		{'o', "---"},
		{'p', ".--."},
		{'q', "--.-"},
		{'r', ".-."},
		{'s', "..."},
		{'t', "-"},
		{'u', "..-"},
		{'v', "...-"},
		{'w', ".--"},
		{'x', "-..-"},
		{'y', "-.--"},
		{'z', "--.."},
		{'0', "-----"},
		{'1', ".----"},
		{'2', "..---"},
		{'3', "...--"},
		{'4', "....-"},
		{'5', "....."},
		{'6', "-...."},
		{'7', "--..."},
		{'8', "---.."},
		{'9', "----."},
		{':', "--..."},
		{',', "--..--"},
		{'(', "-.--."},
		{')', "-.--.-"},
		{'!', "-.-.--"},
		{'/', "-..-."},
		{'=', "-...-"},
		{'-', "-....-"},
		{'@', ".--.-."},
		{'+', ".-.-."},
		{'.', ".-.-.-"},
		{'"', ".-..-."},
	};
public:
	Morse();
	~Morse();
	BinaryTree* Node(char item, int key);
	BinaryTree* AddNode(BinaryTree* start, char value, int key);
	char GetText(const char* str);
	const std::string MorseToText(const char* str1);
	const std::string TextToMorse(const char* txt);
	void statistics();
	void deleteNode(BinaryTree* root);
};

#endif



