#include<SFML/Graphics.hpp>
#include<queue>
#include<string>
#include<iostream>
#include<stack>
#include<vector>
#include<deque>
#include <stdlib.h>
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
public:
    sf::Texture textureForSnake;
    sf::Sprite spriteForSnake;
    std::deque<Position> snake;
    Snake()
    {
        if (!textureForSnake.loadFromFile("snake.png", sf::IntRect(0.5, 0.5, 20, 20)))
        {
            std::cout << "snake.png is not found";
        }
        sf::Sprite sprite;
        sprite.setTexture(textureForSnake);
        snake.emplace_back(220, 200);
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
    void down()
    {
        for (auto it = snake.begin(); it != snake.end(); ++it)
        {
            
            it->y = it->y + 20;
            if (it->y > 400)
            {
                it->y = 0;
            }
        }
    }
    void up()
    {
        for (auto it = snake.begin(); it != snake.end(); ++it)
        {
            it->y = it->y - 20;
            if (it->y < 0)
            {
                it->y = 400;
            }
        }
    }
    void left()
    {
        for (auto it = snake.begin(); it != snake.end(); ++it)
        {
            it->x = it->x - 20;
            if (it->x < 0)
            {
                it->x = 500;
            }
        }
    }
    void right()
    {
        for (auto it = snake.begin(); it != snake.end(); ++it)
        {
            it->x = it->x + 20;
            if (it->x > 500)
            {
                it->x = 0;
            }
        }
    }

    void  display()
    {
        std::cout << "fruit\n";
    }
    bool eatFruit(Fruit fruit, Direction direction)
    {
        
        switch (direction)
        {
            //up
        case 1: 
        {
            if (snake[0].x == fruit.getX() && (snake[0].y + 20) == fruit.getY())
            {
                snake.emplace_front(fruit.getX(), fruit.getY());
                //snake.emplace_back(fruit.getX(), snake[0].y - (20*snake.size()));
                display();
                return true;
            }
        }
            //down
        case 2:
        {
            if (snake[0].x == fruit.getX() && (snake[0].y - 20) == fruit.getY())
            {
                display();
                //snake.emplace_back(fruit.getX(), snake[0].y + (20 * snake.size()));
                snake.emplace_front(fruit.getX(), fruit.getY());
                return true;
            }
        }
            //left
        case 3:
        {
            
            if ((snake[0].x - 20) == fruit.getX() && snake[0].y == fruit.getY())
            {
                display();
                //snake.emplace_back(snake[0].x + (20 * snake.size()), fruit.getY());
                snake.emplace_front(fruit.getX(), fruit.getY());
                return true;
            }
        }
            //right
        case 4:
        {
            if ((snake[0].x + 20) == fruit.getX() && snake[0].y == fruit.getY())
            {
                display();
                //snake.emplace_back(snake[0].x + (20 * snake.size()), fruit.getY());
                snake.emplace_front(fruit.getX(), fruit.getY());
                return true;
            }
        }
        default:
            break;
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
public:
    SnakeBoard()
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
        direction = up;
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
            while (time.asSeconds() < 0.3)
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

        if (!texture.loadFromFile("gameover.png" , sf::IntRect(0,0,200,200)))
        {
            std::cout << "can not load gameover.png";
        }
        spriteGameOver.setTexture(textureGameOver);
    }

    void play()
    {
        while (window.isOpen())
        {
            while (window.pollEvent(snakeMoves))
            {

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
                            snakeObj.right();

                            displaySnake();
                        }
                        continue;
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
                            snakeObj.left();

                            displaySnake();
                        }
                        continue;
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
                            snakeObj.up();
                            displaySnake();
                        }
                        continue;
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
                            snakeObj.down();

                            displaySnake();

                        }
                        continue;
                    }
                    
                }
                default:
                    break;
                }

            }


        }

        
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
    std::vector<Position> snake;

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
        sf::Sprite startButton;
        sf::Texture textureStartButton;    

        if (!textureStartButton.loadFromFile("start.png"))
        {
            std::cout << "this img can not be load";
        }

        startButton.setTexture(textureStartButton);
         
        snake.emplace_back(10, 10   );
        auto i = snake.begin();
        i->sprite.setPosition(10, 10);
        while (window.isOpen())
        {

            window.clear();
            window.draw(sprite);
            startButton.setPosition(140, 120);
            window.draw(startButton);
            window.draw(i->sprite);
            window.display();
            sf::Event event;

            
            

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        std::cout << event.mouseButton.x << std::endl;
                        std::cout << event.mouseButton.y << std::endl;
                       
                    }
                }
               
            }
        }
        return false;
    }
};


int main()
{
    SnakeBoard s;
    if (s.startGame() == true)
    {
        s.play();
    }
    
    //Test test;
    //test.startGame();
    return 0;
}