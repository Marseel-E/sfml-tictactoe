#include "grid.h"

using sf::Event, sf::Keyboard, sf::Vector2f;


namespace ui {
	// variables
	inline RectangleShape container(Vector2f(478, 40));
	inline Text turn;
	inline RectangleShape resetBtn(Vector2f(100, 30));
	inline Text btnText;
	inline Vector2i mousePos;
	inline Vector2f mousePosF;
	inline bool resetClicked = false;

	// functions
	void Init() {
		// container
		container.setPosition(0, 0);
		container.setFillColor(Color::Black);
		// turn text
		turn.setFont(grid::FONT);
		turn.setString("Turn: X");
		turn.setPosition(10.f, 7.f);
		turn.setCharacterSize(20.f);
		turn.setFillColor(Color::White);
		// reset button
		resetBtn.setPosition(368.f, 5.f);
		resetBtn.setFillColor(Color::Red);
		// reset button text
		btnText.setFont(grid::FONT);
		btnText.setString("Reset");
		btnText.setPosition(377.f, 1.25f);
		btnText.setCharacterSize(30.f);
		btnText.setFillColor(Color::Black);
	}

	void Render(RenderTarget& target) {
		target.draw(container);
		target.draw(turn);
		target.draw(resetBtn);
		target.draw(btnText);
	}

	void hoverCheck(const RenderWindow& target) {
		ui::mousePos = Mouse::getPosition(target);
		ui::mousePosF = Vector2f(static_cast<float>(ui::mousePos.x), static_cast<float>(ui::mousePos.y));

		if (resetBtn.getGlobalBounds().contains(ui::mousePosF)) {
			resetBtn.setFillColor(Color(139.f, 0.f, 0.f));
		} else {
			resetBtn.setFillColor(Color::Red);
		}
	}

	void resetClick() {
		grid::turn = "X";

		for (auto& cell: grid::cells) {
			cell.reset();
		}

		grid::finished = false;
	}

	void clickCheck(const RenderWindow& target) {
		ui::mousePos = Mouse::getPosition(target);
		ui::mousePosF = Vector2f(static_cast<float>(ui::mousePos.x), static_cast<float>(ui::mousePos.y));

		if (resetBtn.getGlobalBounds().contains(ui::mousePosF)) {
			resetClick();
		}
	}
};


int main() {
	// game objects
	const int screenSize = 478;
	RenderWindow window(sf::VideoMode(screenSize, screenSize + 38), "TicTacToe", sf::Style::Titlebar | sf::Style::Close);
	Event EVENT;

	grid::Init();
	ui::Init();

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
					ui::hoverCheck(window);
					break;

				case Event::MouseButtonPressed:
					grid::clickCheck(window);
					ui::clickCheck(window);
					break;
			}
		}
		if (!grid::finished) {
			ui::turn.setString("Turn: " + grid::turn);
		}

		// renderer
		window.clear();

		// game grid
		grid::Render(window);
		ui::Render(window);

		window.display();
	}

	return 0;
}