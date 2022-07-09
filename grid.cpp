#include "grid.h"


// functions
void grid::Init() {
	if (!grid::FONT.loadFromFile("lucida-sans.ttf")) {
		std::cout << "couldn't load FONT" << std::endl;
	}

	int cellSize = (500 / 3) - (10 * 2);
	float xPos = 0;
	float yPos = 0;

	for (int i = 0; i < 9; i++) {
		if (i > 0) {
			xPos += (500 / 3);

			if (i % 3 == 0) {
				xPos = 0;
				yPos += (500 / 3);
			}
		}

		grid::Cell newCell(cellSize, xPos, yPos, Color::White);
		// debug
		newCell.click(std::to_string(grid::getIndex(newCell)));

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


int grid::getIndex(grid::Cell& cell) {
	vector<grid::Cell>& cells = grid::cells;

	vector<grid::Cell>::iterator itr = std::find(cells.begin(), cells.end(), cell);

	return std::distance(cells.begin(), itr);
}


bool grid::winCheck() {
	return true;
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

	grid::switchTurn();
}