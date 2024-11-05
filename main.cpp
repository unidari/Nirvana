#include <SFML/Graphics.hpp>
int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Massive");
	const int n = 10;  // размерность матрицы
	const int cellSize = 50;  // размер одной €чейки
	sf::RectangleShape cells[n][n];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cells[i][j].setSize(sf::Vector2f(cellSize - 2, cellSize - 2));
			cells[i][j].setPosition(i * cellSize, j * cellSize);
			cells[i][j].setFillColor(sf::Color::White);
			cells[i][j].setOutlineColor(sf::Color::Black);
			cells[i][j].setOutlineThickness(1);
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i > j) {
				cells[i][j].setFillColor(sf::Color::Green);
			}
		}
	}
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::White);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				window.draw(cells[i][j]);

			}
		}
		window.display();
	}
	return 0;
}