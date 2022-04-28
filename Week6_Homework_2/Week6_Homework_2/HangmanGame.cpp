#include "Hangman.h"
#include "MyDic.h"
#include <random>
void main()
{
	Hangman	game;
	MyDic	dic;

	
	srand((unsigned int)time(NULL));
	dic.load("tmp.dic");
	int i = rand() % (dic.count()+1); 
	game.play(dic.getEng(i), dic.getKor(i));

	
}