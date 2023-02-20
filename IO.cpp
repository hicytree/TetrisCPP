#include "IO.h"
#include <SFML/Graphics.hpp>

static sf::Color mColors [8] = {sf::Color::Black, sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Cyan, sf::Color::Magenta, sf::Color::Yellow, sf::Color::White};

/* 
======================================									
Init
====================================== 
*/
IO::IO() 
{
	InitGraph ();
}


/* 
======================================									
Clear the screen to black
====================================== 
*/
void IO::ClearScreen() 
{
	window.clear();
}


/* 
======================================									
Draw a rectangle of a given color

Parameters:
>> pX1, pY1: 		Upper left corner of the rectangle
>> pX2, pY2: 		Lower right corner of the rectangle
>> pC				Rectangle color
====================================== 
*/
void IO::DrawRectangle (int pX1, int pY1, int pX2, int pY2, enum color pC)
{
	sf::RectangleShape piece(sf::Vector2f(pX2 - pX1, pY2 - pY1));
	piece.setOrigin(-pX1, -pY1);
	piece.setFillColor(mColors[pC]);	
	window.draw(piece);
}


/* 
======================================									
Return the screen height
====================================== 
*/
int IO::GetScreenHeight()
{
	return 700;
}


void IO::InitGraph() {
	window.create(sf::VideoMode(550, 700), "Tetris");
}
