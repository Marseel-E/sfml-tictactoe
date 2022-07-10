#include "grid.h"


// functions
void grid::Init() {
	if (!grid::FONT.loadFromFile("lucida-sans.ttf")) {
		std::cout << "couldn't load FONT" << std::endl;
	}

	int cellSize = (500 / 3) - (10 * 2);
	float xPos = 0;
	float yPos = 40;

	for (int i = 0; i < 9; i++) {
		if (i > 0) {
			xPos += (500 / 3);

			if (i % 3 == 0) {
				xPos = 0;
				yPos += (500 / 3);
			}
		}

		grid::Cell newCell(cellSize, xPos, yPos, Color::White);
		grid::cells.push_back(newCell);

	}

	grid::turn = "X";
}

void grid::Render(sf::RenderTarget& target) {
	for (auto cell: grid::cells) {
		target.draw(cell.getShape());
		target.draw(cell.getText());
	}
}

void grid::hoverCheck(const RenderWindow& target) {
	grid::mousePos = Mouse::getPosition(target);
	grid::mousePosF = Vector2f(static_cast<float>(grid::mousePos.x), static_cast<float>(grid::mousePos.y));
	
	for (auto& cell: grid::cells) {
		if (cell.isClicked()) {
			continue;
		}

		if (cell.getShape().getGlobalBounds().contains(grid::mousePosF)) {
			cell.setColor(Color::Green);
		} else {
			cell.setColor(Color::White);
		}
	}
}

void grid::clickCheck(const RenderWindow& target) {
	grid::mousePos = Mouse::getPosition(target);
	grid::mousePosF = Vector2f(static_cast<float>(grid::mousePos.x), static_cast<float>(grid::mousePos.y));

	for (auto& cell: grid::cells) {
		if (!cell.isClicked() && cell.getShape().getGlobalBounds().contains(grid::mousePosF)) {
			cell.click(grid::turn);
		}
	}
}


void grid::switchTurn() {
	if (grid::turn == "X") {
		grid::turn = "O";
	} else {
		grid::turn = "X";
	}
}


bool grid::winCheck() {
	vector<grid::Cell>& cells = grid::cells;
	string& turn = grid::turn;

	for (int i = 0; i < 2; i++) {
		if (
			(cells.at(0).check(turn)
				&& (
					(cells.at(1).check(turn) && cells.at(2).check(turn))
					|| (cells.at(3).check(turn) && cells.at(6).check(turn))
					|| (cells.at(4).check(turn) && cells.at(8).check(turn))
				)
			)
			|| (cells.at(6).check(turn) && cells.at(7).check(turn) && cells.at(8).check(turn))
			|| (cells.at(1).check(turn) && cells.at(4).check(turn) && cells.at(7).check(turn))
			|| (cells.at(2).check(turn) && cells.at(5).check(turn) && cells.at(8).check(turn))
			|| (cells.at(2).check(turn) && cells.at(4).check(turn) && cells.at(6).check(turn))
			|| (cells.at(3).check(turn) && cells.at(4).check(turn) && cells.at(5).check(turn))
		) {
			return true;
		}

		grid::switchTurn();
	}

	return false;
}


bool grid::drawCheck() {
	for (auto& cell: grid::cells) {
		if (!cell.isClicked()) {
			return false;
		}
	}

	return true;
}


// constrictor - destructor
grid::Cell::Cell(int size, float xPos, float yPos, Color color) {
	this->clicked = false;
	this->text.setFont(grid::FONT);
	this->setSize(size);
	this->setPosition(xPos, yPos);
	this->setColor(color);
}

grid::Cell::~Cell() {}


// accessors
RectangleShape grid::Cell::getShape() {
	return this->shape;
}

bool grid::Cell::isClicked() {
	return this->clicked;
}

Text grid::Cell::getText() {
	return this->text;
}

bool grid::Cell::check(string symbol) {
	return this->text.getString() == symbol;
}


// modifiers
void grid::Cell::setSize(int size) {
	this->shape.setSize(Vector2f(size, size));
}

void grid::Cell::setPosition(float xPos, float yPos) {
	this->shape.setPosition(Vector2f(xPos, yPos));
}

void grid::Cell::setColor(Color color) {
	this->shape.setFillColor(color);
}

void grid::Cell::click(string symbol) {
	auto [xPos, yPos] = this->shape.getPosition();

	if (symbol == "X") {
		xPos += 25.f;
		yPos -= 22.5f;
	} else {
		xPos += 15.f;
		yPos -= 22.f;
	}

	this->clicked = true;
	this->text.setString(symbol);
	this->text.setPosition(xPos, yPos);
	this->text.setCharacterSize(150);
	this->text.setFillColor(Color::Black);
	this->setColor(Color::White);

	if (!grid::finished) {
		if (grid::winCheck()) {
			std::cout << "win: " << grid::turn << std::endl;
			grid::finished = true;

			for (auto& cell: grid::cells) {
				cell.click(grid::turn);
				cell.setColor(Color::Green);
			}

		} else if (grid::drawCheck()) {
			std::cout << "draw" << std::endl;
			grid::finished = true;

			for (auto& cell: grid::cells) {
				cell.setColor(Color::Yellow);
			}
		}

		grid::switchTurn();
	}
}

void grid::Cell::reset() {
	this->clicked = false;
	this->text.setString("");
	this->setColor(Color::White);
}