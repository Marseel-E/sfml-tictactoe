#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include <SFML/Graphics.hpp>

using sf::RenderTarget, std::vector, sf::RectangleShape, sf::Color, sf::Vector2f, sf::Mouse, sf::Vector2i, sf::RenderWindow, std::string, sf::Font, sf::Text;


namespace grid {
	// classes
	class Cell {
		// attributes
		RectangleShape shape;
		bool clicked;
		Text text;

		public:
			// constructor - destructor
			Cell(int size, float xPos, float yPos, Color color);
			virtual ~Cell();

			// accessors
			RectangleShape getShape();
			bool isClicked();
			Text getText();
			bool check(string symbol);

			// modifiers
			void setSize(int size);
			void setPosition(float xPos, float yPos);
			void setColor(Color color);
			void click(string symbol);
	};

	// variables
	inline vector<Cell> cells;
	inline Vector2i mousePos;
	inline Vector2f mousePosF;
	inline Font FONT;
	inline string turn;
	inline bool finished;

	// functions
	void Init();
	void Render(sf::RenderTarget& target);
	void hoverCheck(const RenderWindow& target);
	void clickCheck(const RenderWindow& target);
	void switchTurn();
	bool winCheck(); //
	bool drawCheck();
};


#endif // #ifndef TILE_H