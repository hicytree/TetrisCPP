#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
	IO mIO;
	int mScreenHeight = mIO.GetScreenHeight();
	
	Pieces mPieces;
	Board mBoard(&mPieces, mScreenHeight);
	Game mGame(&mBoard, &mPieces, &mIO, mScreenHeight);
	
	sf::Clock clock;
	while (mIO.window.isOpen()) {
		mIO.ClearScreen();
		mGame.DrawScene();

		sf::Event event;
		while (mIO.window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					mIO.window.close();
					break;
				
				case sf::Event::KeyPressed:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
						if (mBoard.IsPossibleMovement(mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation)) {
							mGame.mPosX++;
						}			
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
						if (mBoard.IsPossibleMovement(mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation)) {
							mGame.mPosX--;
						}
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
						if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation)) {
							mGame.mPosY++;
						}
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
						while (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation)) {
							mGame.mPosY++;
						}
						mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);
						mBoard.DeletePossibleLines();
						mGame.CreateNewPiece();
					}
				break;

				case sf::Event::KeyReleased:
					if (event.key.code == sf::Keyboard::Up) {
						int rotation = (mGame.mRotation + 1) % 4;
						if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, rotation)) {
							mGame.mRotation = rotation;
						}
					}
					break;
			}
			
			if (mBoard.IsGameOver()) {
				break;
			}
		}
		
		sf::Time elapsedTime = clock.getElapsedTime();
		if (int(elapsedTime.asSeconds()) == 1) {
			if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation)) {
				mGame.mPosY++;	
			}
			else {
				mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);
				mBoard.DeletePossibleLines();
				mGame.CreateNewPiece();
			}
			clock.restart();
		}

		if (mBoard.IsGameOver()) {
			break;
		}
	
		mIO.window.display();
	}	
	if (mBoard.IsGameOver()) {
		std::cout << "game over." << std::endl;
	}
	return 0;
}
