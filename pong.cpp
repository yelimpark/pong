#include <SFML/Graphics.hpp>
#include "Bat.h"
#include "Ball.h"
#include "BrickArr.h"
#include <random>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Pong!", Style::Fullscreen);

    Bat bat(1920.f * 0.5f, 1080.f - 20.f);
    Ball ball(1920.f * 0.5f, 1080.f - 300.f);
    BrickArr brickArr;

    Font fontKOMIKAP;
    fontKOMIKAP.loadFromFile("fonts/DS-DIGI.TTF.ttf");

    Text textMessage;
    textMessage.setFont(fontKOMIKAP);
    textMessage.setFillColor(Color::White);
    textMessage.setCharacterSize(75);

    FloatRect textRect = textMessage.getLocalBounds();
    textMessage.setOrigin(
        textRect.left + textRect.width * 0.5f,
        textRect.top + textRect.height * 0.5f
    );
    textMessage.setPosition(1920 * 0.5f, 1080 * 0.5f);

    Clock clock;

    bool prevColSide = false;
    bool prevColTop = false;
    bool prevColBat = false;

    bool isPause = false;
    // life와 score 화면에 띄워주는 것 구현해야 함
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
            if (brickArr.IsBrickCountZero()) {
                break;
            }
            if (life <= 0) {
                break;
            }
            if (Keyboard::isKeyPressed(Keyboard::Return)) {
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

        // 원래는 벽돌의 가로면, 세로면 별로 계산해서 해주어야 함.
        if (brickArr.HanddleCollison(ballbound)) {
            ball.ReboundBatorTop();
            ++score;
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

        if (brickArr.IsBrickCountZero()) {
            textMessage.setString("YOU WON!!");
            isPause = true;
        }
        if (life <= 0) {
            textMessage.setString("YOU LOOSE!!");
            isPause = true;
        }

        window.clear();

        if (isPause) {
            window.draw(textMessage);
        }

        brickArr.Render(window);
        window.draw(bat.GetShape());
        window.draw(ball.GetShape());
        window.display();
    }

    return 0;
}