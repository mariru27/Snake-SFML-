#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include<deque>
#include<stdlib.h>
#include<string>

enum Direction
{
    up = 1,
    down = 2,
    left = 3,
    right = 4
};

class Fruit
{
    int x, y;
    sf::Texture textureFruit;
public:
    sf::Sprite sprite;
    Fruit()
    {
        if (!textureFruit.loadFromFile("fruit.png"))
        {
            std::cout << "can not load fruit.png";
        }
        sprite.setTexture(textureFruit);
        x = 100;
        y = 100;
    }
    int getRandomX()
    {
        x = (rand() % 25) * 20;
        return x;
    }
    int getRandomY()
    {
        y = (rand() % 20) * 20;
        return y;
    }
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
};

class Position
{
public:
    int x, y;
    sf::Sprite sprite;
    sf::Texture texture;
    Position(int x = 0, int y = 0) : x(x), y(y)
    {
        if (!texture.loadFromFile("snake.png", sf::IntRect(0.5,0.5,20,20)))
        {
            std::cout << "can not be load snake.png";
        }
        sprite.setTexture(texture);
    }

};

class Snake
{
    int lastX;
    int lastY;
    int score;
public:
    sf::Texture textureForSnake;
    sf::Sprite spriteForSnake;
    std::deque<Position> snake;
    Snake()
    {
        score = 0;
        if (!textureForSnake.loadFromFile("snake.png", sf::IntRect(0.5, 0.5, 20, 20)))
        {
            std::cout << "can not be load snake.png";
        }
        sf::Sprite sprite;
        sprite.setTexture(textureForSnake);
        snake.emplace_back(220, 200);
        lastX = 220;
        lastY = 200;
    }
    int getSnakeHeadX()
    {
        return snake.front().x;
    }
    int getSnakeHeadY()
    {
        return snake.front().y;
    }
    sf::Sprite getSnakeSprite()
    {
        return spriteForSnake;
    }
    void move(Direction direction)
    {
        lastX = snake.back().x;
        lastY = snake.back().y;
        switch (direction)
        {
        //up
        case 1:
            snake.emplace_front(snake.front().x, snake.front().y - 20);
            if (snake.front().y < 0)
            {
                snake.front().y = 380;
            }
            snake.pop_back();
            break;
        //down
        case 2:
            snake.emplace_front(snake.front().x, snake.front().y + 20);
            if (snake.front().y > 400)
            {
                snake.front().y = 0;
            }
            snake.pop_back();
            break;
        //left
        case 3:
            snake.emplace_front(snake.front().x - 20, snake.front().y);
            if (snake.front().x < 0)
            {
                snake.front().x = 480;
            }
            snake.pop_back();
            break;
        //right
        case 4:
            snake.emplace_front(snake.front().x + 20, snake.front().y);
            if (snake.front().x > 500)
            {
                snake.front().x = 0;
            }
            snake.pop_back();
            break;
        default:
            break;
        }
    }
    void display()
    {
        std::cout << "fruit\n";
    }
    int getScore()
    {
        return score;
    }

    bool snakeIsNotEatHimself()
    {     
        for (auto it = snake.begin(); it != snake.end(); ++it)
        {
            if(it + 1 != snake.end())
            for (auto i = it + 1; i != snake.end(); ++i)
            {
                if (it->x == i->x && it->y == i->y)
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool eatFruit(Fruit fruit, Direction direction)
    {
        if (snake[0].x == fruit.getX() && snake[0].y == fruit.getY())
        {
            score += 10;
            snake.emplace_back(lastX, lastY);
            return true;
        }
        return false;
    }
};

class SnakeBoard
{
protected:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RenderWindow window;
    sf::Font arialFont;
    sf::Text text;
    sf::Event snakeMoves;
    sf::Event event;
    Direction direction;
    sf::Texture startBkTexture;
    sf::Sprite startBkSprite;
    sf::Texture textureGameOver;
    sf::Sprite spriteGameOver;
    Snake snakeObj;
    Fruit fruit;
    bool gOver;
public:
    SnakeBoard()
    {
        gOver = false;
        if (!texture.loadFromFile("ima.jpg"))
        {
            std::cout << "this img can not be load";
        }
        if (!arialFont.loadFromFile("arial.ttf"))
        {
            std::cout << "font can't load";
        }
        sprite.setTexture(texture);
    }

    bool startGame()
    {
        window.create(sf::VideoMode(500, 400), "Snake");
        sf::Sprite startButton;
        sf::Texture textureStartButton;  

        if (!textureStartButton.loadFromFile("start.png"))
        {
            std::cout << "this img can not be load";
        }
        if (!startBkTexture.loadFromFile("startBk.png"))
        {
            std::cout << "can not load startBk.png";
        }
        startBkSprite.setTexture(startBkTexture);
        startButton.setTexture(textureStartButton);

        while (window.isOpen())
        {
            window.clear();
            window.draw(startBkSprite);
            window.display();
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        return true;
                    }
                }
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    return false;
                }
            }
        }
        return false;
    }

    bool fruitCanBePlaced()
    {
        for (auto it = snakeObj.snake.begin(); it != snakeObj.snake.end(); ++it)
        {
            if (it->x == fruit.getX() && it->y == fruit.getY())
            {
                return false;
            }
        }
        return true;
    }

    void displaySnake()
    {
        sf::Clock clock;
        sf::Time time;
        clock.restart();
        time = clock.getElapsedTime();
        for (auto i = snakeObj.snake.begin(); i != snakeObj.snake.end(); ++i)
        {
            window.clear();
            window.draw(sprite);
            if (snakeObj.eatFruit(fruit, direction) == true)
            {
                while (fruitCanBePlaced() == false)
                {
                    fruit.getRandomX();
                    fruit.getRandomY();
                }
                break;
            }
            for (auto it = snakeObj.snake.begin(); it != snakeObj.snake.end(); ++it)
            {
                it->sprite.setPosition(it->x, it->y);
                window.draw(it->sprite);
            }
            
            fruit.sprite.setPosition(fruit.getX(), fruit.getY());
            window.draw(fruit.sprite);
            window.display();

            int k = 0;
            while (time.asSeconds() < 0.2)
            {
                if (k == 10000)
                    k = 0;
                else
                    k++;
                time = clock.getElapsedTime();
            }
        }
    }

    bool gameOver()
    {
        std::string str = std::to_string(snakeObj.getScore());
        if (!textureGameOver.loadFromFile("gameover.png"))
        {
            std::cout << "can not load gameover.png";
        }
        spriteGameOver.setTexture(textureGameOver);
        text.setFont(arialFont);
        text.setString(str);
        text.setCharacterSize(50);
        text.setPosition(200, 170);

        sf::Event gameOverEvent;
        while (window.isOpen())
        {
            window.pollEvent(gameOverEvent);
            if (gameOverEvent.type == sf::Event::MouseButtonPressed)
            {
                if (gameOverEvent.mouseButton.button == sf::Mouse::Left)
                {
                    if (gameOverEvent.mouseButton.x >= 142 && gameOverEvent.mouseButton.x <= 329
                        && gameOverEvent.mouseButton.y >= 228 && gameOverEvent.mouseButton.y <= 356)
                    {
                        return true;
                    }
                }
            }
            if (gameOverEvent.type == sf::Event::Closed)
            {
                window.close();
                return false;
            }
            window.clear();
            window.draw(spriteGameOver);
            window.draw(text);
            window.display();
        }

        return false;
    }

    bool play()
    {
        while (window.isOpen())
        {
            while (window.pollEvent(snakeMoves) )
            {
                if (snakeMoves.key.code == sf::Keyboard::Enter)
                    snakeMoves.key.code = sf::Keyboard::Left;
                switch (snakeMoves.key.code)
                {
                //right
                case sf::Keyboard::Right:
                {
                    if (direction != left)
                    {
                        direction = right;
                        while (snakeMoves.key.code == sf::Keyboard::Right)
                        {

                            window.pollEvent(event);
                            if (event.key.code == sf::Keyboard::Left ||
                                event.key.code == sf::Keyboard::Down ||
                                event.key.code == sf::Keyboard::Up)
                            {
                                snakeMoves = event;
                                break;
                            }

                            snakeObj.move(right);
                            if (snakeObj.snakeIsNotEatHimself() == false)
                            {
                                return false;
                            }

                            displaySnake();
                        }
                        continue;
                    }
                    else
                    {
                        return false;
                    }

                }
                //left
                case sf::Keyboard::Left:
                {
                    if (direction != right)
                    {
                        direction = left;
                        while (snakeMoves.key.code == sf::Keyboard::Left)
                        {
                            window.pollEvent(event);
                            if (event.key.code == sf::Keyboard::Right ||
                                event.key.code == sf::Keyboard::Down ||
                                event.key.code == sf::Keyboard::Up)
                            {
                                snakeMoves = event;
                                break;
                            }
                            snakeObj.move(left);
                            if (snakeObj.snakeIsNotEatHimself() == false)
                            {
                                std::cout << "false\n";
                                return false;
                            }
                            displaySnake();
                        }
                        continue;
                    }
                    else
                    {
                        return false;
                    }
                }
                //up
                case sf::Keyboard::Up:
                {
                    if (direction != down)
                    {
                        direction = up;
                        while (snakeMoves.key.code == sf::Keyboard::Up)
                        {
                            window.pollEvent(event);
                            if (event.key.code == sf::Keyboard::Left ||
                                event.key.code == sf::Keyboard::Down ||
                                event.key.code == sf::Keyboard::Right)
                            {
                                snakeMoves = event;
                                break;
                            }
                            snakeObj.move(up);
                            if (snakeObj.snakeIsNotEatHimself() == false)
                            {
                                return false;
                            }
                            displaySnake();
                        }
                        continue;
                    }
                    else
                    {
                        return false;
                    }

                }
                //down
                case sf::Keyboard::Down:
                {
                    if (direction != up)
                    {
                        direction = down;
                        while (snakeMoves.key.code == sf::Keyboard::Down)
                        {

                            window.pollEvent(event);
                            if (event.key.code == sf::Keyboard::Left ||
                                event.key.code == sf::Keyboard::Right ||
                                event.key.code == sf::Keyboard::Up)
                            {
                                snakeMoves = event;
                                break;
                            }
                            snakeObj.move(down);
                            if (snakeObj.snakeIsNotEatHimself() == false)
                            {
                                return false;
                            }                           
                            displaySnake();
                        }
                        continue;
                    }
                    else
                    {
                        return false;
                    }

                }
                default:
                    break;
                }
            }
        }

        return true;
    }
};

int main()
{
    bool start = true;

    while (start == true)
    {
        SnakeBoard s;

        if (s.startGame() == true)
        {
            if (s.play() == false)
                start = s.gameOver();
            else
                start = false;
        }
        else
        {
            start = false;
        }
    }
    
    return 0;
}