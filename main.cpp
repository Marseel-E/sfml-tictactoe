#include "grid.h"

using sf::Event, sf::Keyboard;


int main() {
	// game objects
	const int screenSize = 480;
	RenderWindow window(sf::VideoMode(screenSize, screenSize), "TicTacToe", sf::Style::Titlebar | sf::Style::Close);
	Event EVENT;

	grid::Init();

	// main loop
	while (window.isOpen()) {
		
		// events handler
		while (window.pollEvent(EVENT)) {
			switch (EVENT.type) {
				// window closed
				case Event::Closed:
					window.close();
					break;

				// ESCAPE key pressed
				case Event::KeyPressed:
					if (Keyboard::isKeyPressed(Keyboard::Escape)) {
						window.close();
					}

					break;

				// button hover detection
				case Event::MouseMoved:
					grid::hoverCheck(window);
					break;

				case Event::MouseButtonPressed:
					grid::clickCheck(window);
					break;
			}
		}

		// renderer
		window.clear();

		// game grid
		grid::Render(window);

		window.display();
	}

	return 0;
}