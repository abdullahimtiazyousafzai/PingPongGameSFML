/*Developed by M.Abdullah on April 6,2023
Copyright belongs to M.Abdullah
This project is for presentation only.
This project is not for sale or any other commercial use.
*/
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
int main()
{
    // Set up the window
    int window_width = 1180;
    int window_height = 720;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML Ping Pong Game");

    sf::SoundBuffer hitbuffer;
    if (!hitbuffer.loadFromFile("F:/CLionProjects/PingPongGameSFML/hit.wav"))
        return -1;

    sf::Sound hitSound;
    hitSound.setBuffer(hitbuffer);

    sf::SoundBuffer missbuffer;
    if (!missbuffer.loadFromFile("F:/CLionProjects/PingPongGameSFML/miss.wav"))
        return -1;

    sf::Sound missSound;
    missSound.setBuffer(missbuffer);


    // Set up the paddles
    float paddle_width = 10.0f;
    float paddle_height = 150.0f;
    float paddle_speed = 500.0f;
    sf::RectangleShape paddle_left(sf::Vector2f(paddle_width, paddle_height));
    sf::RectangleShape paddle_right(sf::Vector2f(paddle_width, paddle_height));
    paddle_left.setPosition(0.0f, (window_height - paddle_height) / 2.0f);
    paddle_right.setPosition(window_width - paddle_width, (window_height - paddle_height) / 2.0f);



    // Set up the ball
    float ball_size = 10.0f;
    sf::CircleShape ball(ball_size);
    ball.setPosition((window_width - ball_size) / 2.0f, (window_height - ball_size) / 2.0f);
    float ball_speed_x = 1.0f;
    float ball_speed_y = 1.0f;

    // Set up the score
    int score_left = 0;
    int score_right = 0;
    sf::Font font;
    if (!font.loadFromFile("F:/CLionProjects/SnakeGameSFML/Roboto-Light.ttf"))
    {
        std::cout << "Error loading font" << std::endl;
        return -1;
    }
    sf::Text score_text_left;
    score_text_left.setFont(font);
    score_text_left.setCharacterSize(30);
    score_text_left.setPosition(10.f, 10.0f);
    sf::Text score_text_right;
    score_text_right.setFont(font);
    score_text_right.setCharacterSize(30);
    score_text_right.setPosition(850.f , 10.0f);

    sf::Text pressEsc;

    // Main game loop
    sf::Clock clock;
    while (window.isOpen())
    {
        float delta_time = clock.restart().asSeconds();

        // Handle input
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        // Move the paddles
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && paddle_left.getPosition().y > 0.0f)
        {
            paddle_left.move(0.0f, -paddle_speed * delta_time);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && paddle_left.getPosition().y + paddle_height < window_height)
        {
            paddle_left.move(0.0f, paddle_speed * delta_time);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && paddle_right.getPosition().y > 0.0f)
        {
            paddle_right.move(0.0f, -paddle_speed * delta_time);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && paddle_right.getPosition().y + paddle_height < window_height)
        {
            paddle_right.move(0.0f, paddle_speed * delta_time);
        }

        // Move the ball
        ball.move(ball_speed_x, ball_speed_y);

        // Check if the ball collides with the top or bottom of the window and change its vertical direction if it does
            if (ball.getPosition().y < 5.0f || ball.getPosition().y > window_height - ball_size - 5.0f)
            {
                ball_speed_y = -ball_speed_y;
            }
        // Check if the ball collides with the paddles and change its horizontal direction if it does
        if (ball.getGlobalBounds().intersects(paddle_left.getGlobalBounds()) || ball.getGlobalBounds().intersects(paddle_right.getGlobalBounds()))
        {
            hitSound.play();
            ball_speed_x = -ball_speed_x;
        }

        // Check if the ball goes out of bounds on the left or right and update the score
        if (ball.getPosition().x < 0.0f)
        {
            missSound.play();
            score_right++;
            ball.setPosition((window_width - ball_size) / 2.0f, (window_height - ball_size) / 2.0f);
            ball_speed_x = -ball_speed_x;
        }
        if (ball.getPosition().x + ball_size > window_width)
        {
            missSound.play();
            score_left++;
            ball.setPosition((window_width - ball_size) / 2.0f, (window_height - ball_size) / 2.0f);
            ball_speed_x = -ball_speed_x;
        }

        // Update the score text
        score_text_left.setString("Team 1:   " + std::to_string(score_left));
        score_text_right.setString("Team 2:  " + std::to_string(score_right));

        if(score_left == 5)
        {
            score_text_left.setPosition(300.f , 10.0f);
            score_text_right.setPosition(300.f , 50.0f);
            score_text_left.setString("Team 1 WINNER");
            score_text_right.setString("Team 2 LOSER");
            ball.setPosition((window_width - ball_size) / 2.0f, (window_height - ball_size) / 2.0f);
            pressEsc.setFont(font);
            pressEsc.setString("Game Over\nPress Esc to exit");
            pressEsc.setPosition(300.f , 100.0f);
        }
        if(score_right == 5)
        {
            score_text_left.setPosition(300.f , 10.0f);
            score_text_right.setPosition(300.f , 50.0f);
            score_text_left.setString("Team 1 LOSER");
            score_text_right.setString("Team 2 WINNER");
            ball.setPosition((window_width - ball_size) / 2.0f, (window_height - ball_size) / 2.0f);
            pressEsc.setFont(font);
            pressEsc.setString("Game Over\nPress Esc to exit");
            pressEsc.setPosition(300.f , 100.0f);
        }

        // Clear the window
        window.clear();

        // Draw the paddles, ball, and score text
        window.draw(paddle_left);
        window.draw(paddle_right);
        window.draw(ball);
        window.draw(score_text_left);
        window.draw(score_text_right);
        window.draw(pressEsc);


        // Display the window
        window.display();
    }

    return 0;
}
