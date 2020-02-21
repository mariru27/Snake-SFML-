#include<SFML/Graphics.hpp>
#include<queue>
#include<string>
#include<iostream>
#include<stack>
#include<vector>
#include<deque>
#include<stdlib.h>
#include<string>
#include<memory>


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
        y = 200;

    }
    bool fruitCanBeEaten(int x, int y)
    {
        
        
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
            std::cout << "can not load snake.png";
        }
        sprite.setTexture(texture);
    }

};

class MessageBox
{
    sf::Font arialFont;
    sf::Text text;
public: 
    MessageBox()
    {
        if (!arialFont.loadFromFile("arial.ttf"))
        {
            std::cout << "font can't load";
        }

    }
    void activateMassageBox(std::string str)
    {
        sf::RenderWindow win(sf::VideoMode(250, 40), "message");
        sf::Event event;
        text.setFont(arialFont);
        text.setString(str);
        text.setCharacterSize(17);
        while (win.pollEvent(event))
        {
            while (win.isOpen())
            {
                win.clear();
                win.draw(text);
                win.display();
            }
        }
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
            std::cout << "snake.png is not found";
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
                snake.front().y = 400;
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
        case 3:
            //left
            snake.emplace_front(snake.front().x - 20, snake.front().y);
            if (snake.front().x < 0)
            {
                snake.front().x = 500;
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
        direction = down;
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

        startButton.setTexture(textureStartButton);

        while (window.isOpen())
        {

            window.clear();
            window.draw(sprite);
            startButton.setPosition(140, 120);
            window.draw(startButton);
            window.display();
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if(event.mouseButton.x >= 145 && event.mouseButton.x <= 313 
                            && event.mouseButton.y >= 126 && event.mouseButton.y <=173)
                        {
                            std::cout << "game will start now!!!" << std::endl;
                            return true;
                        }
                    }
                }
                if (event.type == sf::Event::Closed)
                {
                    MessageBox exitMessage;
                    exitMessage.activateMassageBox("do you want to exit from this game?");
                }
            }
        }
        return false;
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
                fruit.getRandomX();
                fruit.getRandomY();
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
            while (time.asSeconds() < 0.1)
            {
                if (k == 10000)
                    k = 0;
                else
                    k++;
                time = clock.getElapsedTime();
            }
        }
    }

    void gameOver()
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
        while (window.isOpen())
        {
            window.clear();
            window.draw(spriteGameOver);
            window.draw(text);
            window.display();
        }
    }

    bool play()
    {
        while (window.isOpen())
        {
            while (window.pollEvent(snakeMoves))
            {
                std::cout << direction << std::endl;
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

class Test
{
protected:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RenderWindow window;
    sf::Font arialFont;
    sf::Text text;
    std::deque<Position> snake;
    sf::Texture textureGameOver;
    sf::Sprite spriteGameOver;
public:
    Test()
    {
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


        if (!texture.loadFromFile("gameover.png"))
        {
            std::cout << "can not load gameover.png";
        }
        spriteGameOver.setTexture(textureGameOver);



   
        while (window.isOpen())
        {

            window.clear();
            window.draw(sprite);
            window.display();
        }
        return false;
    }
};

int main()
{

    SnakeBoard s;
    if (s.startGame() == true)
    {
        if (s.play() == false)
            s.gameOver();
        
    }
    
    //Test test;
    //test.startGame();
    return 0;
}