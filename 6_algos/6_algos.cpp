#include <SFML/Graphics.hpp>
#include <set>
#include <functional>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <random>

using namespace std;
using namespace sf;

const int GRID_SIZE = 10; // Размер поля NxN
const int CELL_SIZE = 25;  // Размер одной ячейки в пикселях
const int WINDOW_SIZE = GRID_SIZE * CELL_SIZE;
// доп цвета для smfl
Color Orange(229, 135, 34, 255);
Color Purple(90, 34, 139, 255);

// Типы ячеек
enum CellType {
    EMPTY,
    OBSTACLE,
    START,
    END,
    PATH,
    VISITED,
    QUEUED
};

// Структура для представления ячейки
struct Cell {
    int x, y;
    CellType type;
    int f, g, h; // Для алгоритма A*
    Cell* parent; // адрес для родителя

    Cell(int x, int y) : x(x), y(y), type(EMPTY), f(0), g(0), h(0), parent(nullptr) {}

    // Перезагрузка оператора == для сравнения ячеек
    bool operator==(const Cell& other) const {
        return x == other.x && y == other.y;
    }
    // для высчитывания полной стоимости пути
    void F() {
        f = g + h;
    }
};

// Функция для вычисления эвристики (манхэттенское расстояние)
int heuristic(const Cell& a, const Cell& b) {
    return (abs(a.x - b.x) + abs(a.y - b.y));
}

// Функция для проверки, находится ли ячейка в пределах сетки
bool isValid(int x, int y) {
    return (GRID_SIZE > x) and ( x >= 0) and (GRID_SIZE > y) and ( y >= 0);
}
// для отрисовки
//в целом и в общем - проходимся по всем клеткам и заполняем соответствующими типам цветом
void draw_grid(RenderWindow& window, vector<vector<Cell>>& grid) {
    for (int x = 0; x < grid.size(); x++) {
        for (int y = 0; y < grid.size(); y++) {
            RectangleShape cell(Vector2f(CELL_SIZE, CELL_SIZE));
            cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
            switch (grid[x][y].type) {
            case EMPTY: cell.setFillColor(Color::White); break;
            case OBSTACLE: cell.setFillColor(Color::Black); break;
            case START: cell.setFillColor(Orange); break;
            case END: cell.setFillColor(Color::Cyan); break;
            case PATH: cell.setFillColor(Purple); break;
            case VISITED: cell.setFillColor(Color::Red); break;
            case QUEUED: cell.setFillColor(Color::Green); break;
            }
            cell.setOutlineColor(Color::Black);
            cell.setOutlineThickness(1);
            window.draw(cell);

        }
    }
}

//создаём сетку
vector<vector<Cell>> make_grid() {
    //создаем клетку
    vector<vector<Cell>> grid;
    //координаты начала
    int startX = 0;
    int startY = 7;
    int endX = 9;
    int endY = 9;
    //карта с препятствиями
    vector<vector<int>> gridObstacle = {
        {1, 0, 1, 0, 0, 1, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 1, 0, 1, 1, 1, 0},
        {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 1, 0, 0}
    };
    for (int x = 0; x < GRID_SIZE; x++) {

        vector<Cell> row;

        for (int y = 0; y < GRID_SIZE; y++) {
            Cell cell(x, y);
            cell.h = abs(x - endX) + abs(y - endY);
            cell.F();


            if (gridObstacle[y][x]) cell.type = OBSTACLE;
            row.push_back(cell);
        }
        grid.push_back(row);
    }
    Cell* start = &grid[startX][startY];
    Cell* end = &grid[endX][endY];

    start->type = START;
    start->g = 0;
    end->type = END;
    pair<Cell*, Cell*> p(start, end);

    return grid;
}


vector<pair<int, int>> A_Star(vector<vector<Cell>>& grid, Cell* start, Cell* goal) {
    // создаём приоритетную очередь для открытого списка, для того чтобы элемент с наименьшим показателем стоимости f всегда был на вершине
    priority_queue<Cell*, vector<Cell*>, function<bool(Cell*, Cell*)>> open_list(
        [](Cell* a, Cell* b) { return a->f > b->f; }
    );
    // создаем закрытый список для рассмотренных точек
    set<pair<int, int>> closed_list;
    // начальная точка
    start->g = 0;// стоимость до финиша с начальной точки
    start->h = heuristic(*start, *goal); //  эвристическая оценка пути до финиша от начала
    start->F(); // высчитываем полную стоимость
    open_list.push(start);// и добавляем в открытый список
    // пока соответственно открытый список не пуст, происходит обновление данных о всех вершинах
    while (!open_list.empty()) {
        // на вход вершина с min F, и удалется из списка
        Cell* current = open_list.top();
        open_list.pop();
        // если достигли цели, "создаем" путь и восстанавливаем этот путь 
        if (current->x == goal->x && current->y == goal->y) {
            vector<pair<int, int>> path;
            while (current != nullptr) {
                path.emplace_back(current->x, current->y);
                // и меняем тип ячейки на PATH (кроме START и END)
                if (current->type != START && current->type != END) {
                    grid[current->x][current->y].type = PATH;
                }
                //указатель current переназначается на родительский объект
                current = current->parent;;
            }
            // делаем ревёрсинг пути также для восстановления пути
            reverse(path.begin(), path.end());
            return path;
        }
        // и текущая посещённая вершина направляется в закрытый список, помечаем, что уже посещённая
        closed_list.insert({ current->x, current->y });
        if (grid[current->x][current->y].type != START && grid[current->x][current->y].type != END) {
            grid[current->x][current->y].type = VISITED; 
        }
        // выводим все значения для текущей клетки
        cout << " " << current->x
            << " " << current->y
            << " F " << current->f << " "
            << "g -  " << current->g << "  "
            << "h -  " << current->h << endl;
        // проверка соседей клетки
        for (auto [dx, dy] : vector<pair<int, int>>{ {-1, 0}, {1, 0}, {0, -1}, {0, 1} }) {
            int nx = current->x + dx;
            int ny = current->y + dy;
            // проверка, что сосед вообще находится в матрице
            if (!isValid(nx, ny)) continue;
            Cell* neighbor = &grid[nx][ny];
            // continue, если препятствие и если клетка уже посещенная
            if (neighbor->type == OBSTACLE || closed_list.count({ nx, ny })) {
                continue;
            }
            // расчет g для клетки
            int next_g = current->g + 1;
            // соседняя клетка находится в открытом списке, тогда сравниваем её значение g и у текущей проверяемой клетки
            // если прежнее значение g меньше нового, то ничего не делаем
            // а вот если новое значение g меньше, то обновляем переменную, меняем родителя на текущую клетку
            if (next_g < neighbor->g || neighbor->g == 0) {
                neighbor->parent = current;
                neighbor->g = next_g;
                neighbor->h = heuristic(*neighbor, *goal);
                neighbor->F();
                // добавление клетки в открытый список для посещения
                open_list.push(neighbor);
                if (neighbor->type != END) neighbor->type = QUEUED;
            }
        }
    }
    return {}; // иной путь - если пути не нашлось
}
int main() {
    // загрузка шрифта для вывода текста
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {  
        return EXIT_FAILURE;
    }

    // настройка текста для вывода статуса
    sf::Text statusText;
    statusText.setFont(font);


    vector<vector<Cell>> grid;
    grid = make_grid();
    Cell* start = &grid[0][7];
    Cell* goal = &grid[9][9];

    //создание окна и работа алгоритма
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), L" ");
    bool pathFound = false;
    vector<pair<int, int>> path;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                if (event.key.scancode == Keyboard::Scan::Space) { //  A* 
                    auto path = A_Star(grid, start, goal);
                }
            }
        }
        window.clear();
        draw_grid(window, grid);
        window.display();
    }
    return 0;
}
