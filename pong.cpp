#include <SFML/Graphics.hpp>
#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include "BrickArr.h"
#include <random>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong!", Style::Fullscreen);

    Bat bat(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT - 20.f);
    Ball ball(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT - 200.f);
    BrickArr brickArr;

    Font fontDSDIGI;
    fontDSDIGI.loadFromFile("fonts/DS-DIGI.ttf");

    Text textMessage;
    textMessage.setFont(fontDSDIGI);
    textMessage.setFillColor(Color::Magenta);
    textMessage.setCharacterSize(75);

    Text textScore;
    textScore.setFont(fontDSDIGI);
    textScore.setString("Score = 0");
    textScore.setFillColor(Color::Magenta);
    textScore.setCharacterSize(80);
    textScore.setPosition(1920.f * 0.8f, 20.f);

    Text textLife;
    textLife.setFont(fontDSDIGI);
    textLife.setString("Life = 3");
    textLife.setFillColor(Color::Magenta);
    textLife.setCharacterSize(80);
    textLife.setPosition(1920.f * 0.8f, 80.f);

    Clock clock;

    bool prevColSide = false;
    bool prevColTop = false;
    bool prevColBat = false;

    bool isPause = false;
    int life = 3;
    int score = 0;

    while (window.isOpen())
    {
        Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (isPause) {
            if (Keyboard::isKeyPressed(Keyboard::Return)) {
                if (brickArr.IsBrickCountZero()) {
                    break;
                }
                if (life <= 0) {
                    break;
                }
                isPause = false;
            }
            continue;
        }

        Sides dir = Sides::NONE;

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            dir = Sides::LEFT;
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            dir = Sides::RIGHT;
        }

        bat.SetMoveDir(dir);

        FloatRect ballbound = ball.GetGlobalBounds();
        Vector2u windowSize = window.getSize();

        switch (brickArr.HanddleCollison(ballbound)) {
        case BRICK_COL_TYPE::TOP_OR_BOTTOM:
            ball.ReboundBatorTop();
            ++score;
            break;

        case BRICK_COL_TYPE::SIDE:
            ball.ReboundsSides();
            ++score;
            break;

        default :
            break;
        }

        bool colSide = ballbound.left < 0.f || ballbound.left + ballbound.width > windowSize.x;
        bool colTop = ballbound.top < 0.f;
        bool colBat = ballbound.intersects(bat.GetGlobalBounds());

        if (!prevColSide && colSide) {
            ball.ReboundsSides();
        }

        if (!prevColTop && colTop) {
            ball.ReboundBatorTop();
        }

        if (!prevColBat && colBat) {
            ball.ReboundBatorTop();
        }

        if (ballbound.top + ballbound.height > windowSize.y) {
            ball.Init();
            bat.InitPos();
            --life;
            textMessage.setString("Press Enter To Start");
            isPause = true;
        }

        prevColSide = colSide;
        prevColTop = colTop;
        prevColBat = colBat;

        bat.Update(deltaTime);
        ball.Update(deltaTime);

        stringstream ss;
        ss << "Score = " << score;
        textScore.setString(ss.str());

        stringstream ss2;
        ss2 << "Life = " << life;
        textLife.setString(ss2.str());

        if (brickArr.IsBrickCountZero()) {
            textMessage.setString("YOU WON!!\n Press Enter To Terminate.");
            isPause = true;
        }
        if (life <= 0) {
            textMessage.setString("YOU LOOSE!!\n Press Enter To Terminate.");
            isPause = true;
        }

        window.clear();

        brickArr.Render(window);
        window.draw(bat.GetShape());
        window.draw(ball.GetShape());
        window.draw(textScore);
        window.draw(textLife);

        if (isPause) {
            FloatRect textRect = textMessage.getLocalBounds();
            textMessage.setOrigin(
                textRect.left + textRect.width * 0.5f,
                textRect.top + textRect.height * 0.5f
            );
            textMessage.setPosition(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f);
            window.draw(textMessage);
        }

        window.display();
    }

    return 0;
}