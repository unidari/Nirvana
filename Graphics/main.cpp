#include <SFML/Graphics.hpp>
#include <windows.h>
#include <functional> 
#include <cmath>
#include <locale.h>
// Ôóíêöèÿ äëÿ îòðèñîâêè ãðàôèêà
void drawGraph(sf::RenderWindow& window, std::function<float(float)> func, float xMin, float xMax, float scaleX, float scaleY, sf::Color color) {
    sf::VertexArray graph(sf::LinesStrip);

    for (float x = xMin; x <= xMax; x += 0.1f) {
        float y = func(x); // Âû÷èñëåíèå çíà÷åíèÿ ôóíêöèè

        // Ïðåîáðàçîâàíèå êîîðäèíàò â ýêðàííûå
        float screenX = 400 + x * scaleX;
        float screenY = 300 - y * scaleY;

        // Äîáàâëåíèå òî÷êè â ìàññèâ âåðøèí
        graph.append(sf::Vertex(sf::Vector2f(screenX, screenY), color));
    }

    window.draw(graph);
}

int main() {
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Console app to display graphs");
    setlocale(LC_ALL, "Russian");
    // Ïåðåìåííàÿ äëÿ õðàíåíèÿ ïîëüçîâàòåëüñêîé òî÷êè
    sf::CircleShape userPoint(5); // Ðàäèóñ 5 ïèêñåëåé
    userPoint.setFillColor(sf::Color::Red);
    bool userPointExists = false; // Ïåðåìåííàÿ äëÿ ïðîâåðêè ñóùåñòâîâàíèÿ ïîëüçîâàòåëüñêîé òî÷êè

    // 1 _ Çàãðóçêà øðèôòà 
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }
    // 2 _ Òåêñò äëÿ îòîáðàæåíèÿ êîîðäèíàò òî÷êè 
    // Ðàçìåð òåêñòà 20, ïîëîæåíèå òåêñòà (10,10), öâåò áåëûé. Òåêñò õðàíèòå â ïåðåìåííîé coordinatesText
    sf::Text coordinatesText;
    coordinatesText.setFont(font);
    coordinatesText.setCharacterSize(20);
    coordinatesText.setFillColor(sf::Color::White);
    coordinatesText.setPosition(10, 10);
    sf::Text numberZone;
    numberZone.setFont(font);
    numberZone.setCharacterSize(20);
    numberZone.setFillColor(sf::Color::White);
    numberZone.setPosition(10, 100);

    // Îñè X è Y
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(50, 300); // Íà÷àëî îñè X
    xAxis[0].color = sf::Color::White; // Öâåò îñè
    xAxis[1].position = sf::Vector2f(750, 300); // Êîíåö îñè X
    xAxis[1].color = sf::Color::White;

    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(400, 50); // Íà÷àëî îñè Y
    yAxis[0].color = sf::Color::White; // Öâåò îñè
    yAxis[1].position = sf::Vector2f(400, 550); // Êîíåö îñè Y
    yAxis[1].color = sf::Color::White;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Ïðîâåðêà êëèêà ìûøüþ
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Ïîëó÷åíèå ïîçèöèè êëèêà
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Ïðåîáðàçîâàíèå ýêðàííûõ êîîðäèíàò â "ìàòåìàòè÷åñêèå"
                    float mathX = (mousePos.x - 400) / 20.0f; // Ìàñøòàá 30 ïî X
                    float mathY = -(mousePos.y - 300) / 20.0f; // Ìàñøòàá 100 ïî Y

                    // Óñòàíîâêà íîâîé ïîëüçîâàòåëüñêîé òî÷êè
                    userPoint.setPosition(mousePos.x - userPoint.getRadius(), mousePos.y - userPoint.getRadius());
                    userPointExists = true; // Ïîìå÷àåì, ÷òî òî÷êà ñóùåñòâóåò

                    // 3 _ Äîïèøèòå ëîãèêó ïðîâåðêè òî÷êè ïî ïåðåìåííûì mathX è mathY !
                    if (mathY == 2 && mathY == mathX * mathX - 2 * mathX - 6) {
                        numberZone.setString("Boderline");
                    }
                    else {
                        if (mathY > mathX * mathX - 2 * mathX - 6) {
                            if (mathY < 2) {
                                numberZone.setString("Zone 3");
                            }
                            else {
                                numberZone.setString("Zone 5");
                            }
                        }
                        else {
                            if (mathY < 2) {
                                numberZone.setString("Zone 2");
                            }
                            else {
                                if (mathX > 2) {
                                    numberZone.setString("Zone 4");
                                }
                                else {
                                    numberZone.setString("Zone 1");
                                }
                            }
                        }
                    }
                    // Îáíîâëåíèå òåêñòà ñ êîîðäèíàòàìè òî÷êè 
                    coordinatesText.setString("Coordinations: (" + std::to_string(mathX) + ", " + std::to_string(mathY) + ")");
                }
            }
        }


        // 4 _ Î÷èñòêà ýêðàíà 
        window.clear();

        // Îòðèñîâêà îñåé
        window.draw(xAxis);
        window.draw(yAxis);



        // 5 _  Îòðèñîâêà ãðàôèêà y1 = x*x-2*x-6
        drawGraph(window, [](float x) { return x * x - 2 * x - 6; }, -12, 12, 20, 20, sf::Color::Blue);

        // 5 _   Îòðèñîâêà ãðàôèêà y2 = 2
        drawGraph(window, [](float x) { return 2; }, -12, 12, 20, 20, sf::Color::Red);

        // Îòðèñîâêà ïîëüçîâàòåëüñêîé òî÷êè, åñëè îíà ñóùåñòâóåò
        if (userPointExists) {
            window.draw(userPoint);
            window.draw(coordinatesText);
            window.draw(numberZone);
        }

        // Îòîáðàæåíèå íîâîãî êàäðà
        window.display();
    }
    return 0;
}

