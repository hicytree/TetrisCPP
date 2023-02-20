#include <SFML/Graphics.hpp>

#ifndef _IO_
#define _IO_
enum color {BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE}; // Colors

class IO
{
    public:
        IO();
        void DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC);
        void ClearScreen();
        int GetScreenHeight();
		void InitGraph();
		sf::RenderWindow window;
};
#endif
