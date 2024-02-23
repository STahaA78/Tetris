#include<iostream>
#include <SFML/Graphics.hpp>
#include"game.h"
#include<string.h>
#include"Tetrimino.h"
#include<Windows.h>
using namespace std;
using namespace sf;
int main()
{
    Texture back,start;
    start.loadFromFile("Images/Start10.png", IntRect(0, 0, 800, 800));
    Sprite st;
    st.setTexture(start);
    st.setPosition(0, 0);
    back.loadFromFile("Background1.png",IntRect(0,0,800,800));
    Sprite b;
    b.setTexture(back);
    b.setPosition(0, 0);
    bool d = 0;
    int r;
    srand(time(0));
    bool level;
    int coordinates[4][2];
    I i;
    J j;
    L l;
    O o;
    S s;
    T t;
    Z z;
    bool check=1;
    bool ch = 1;
    tetrimino* current=&i;
    bool c = 0;
    bool gameend1 = 0,gameend=0;
    float speed = 1,fix=0.5;
    Clock tim;
    game tetris;
    string name;
    RenderWindow window(VideoMode(800, 800), "Tetris");
    while (window.isOpen())
    {
        if (c == 0)
        {
            tim.restart(); 
            r = rand() % 7 + 1;
            //r = 1;
            if (r == 1)
                current = &i;
            else if (r == 2)
                current = &j;
            else if (r == 3)
                current = &l;
            else if(r==4)
                current = &o;
            else if (r == 5)
                current = &s;
            else if (r == 6)
                current = &t;
            else if (r == 7)
                current = &z;
            tetris.drawintro(window, c,st);
        }
        if (tetris.game_end() == 1 || (*current).end_game(tetris) == 1&&c==1)
        {
            Sleep(500);
            tetris.GameEndDisplay(window,ch,b);
            ch = 0;
        }
        else if(c==1)
        {
            tetris.draw(window,b);
            tetris.drawscoreboard(window);
            current->draw(window);
            Event event;
            while (window.pollEvent(event) )
            {
                if (event.key.code == Keyboard::Escape)
                    window.close();
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right))
                    current->moveright(tetris);
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left))
                    current->moveleft(tetris);
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
                    current->rotate(tetris);
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down))
                {
                    check = current->checker1(tetris);
                    current->movedown(tetris);
                    if(check==1)
                        tim.restart();
                    
                }
            }
            if (tim.getElapsedTime().asSeconds() >= fix)
            {
                check = current->checker1(tetris);
                if (check == 0)
                {
                    current->indexes(coordinates);
                    tetris.update(coordinates, r);
                    tetris.checker(tetris.getlevel(), speed);
                    current->reset();
                    r = rand() % 7 + 1;
                    if (r == 1)
                        current = &i;
                    else if (r == 2)
                        current = &j;
                    else if (r == 3)
                        current = &l;
                    else if (r == 4)
                        current = &o;
                    else if (r == 5)
                        current = &s;
                    else if (r == 6)
                        current = &t;
                    else if (r == 7)
                        current = &z;
                }
            }
            if (tim.getElapsedTime().asSeconds() >= speed)
            {
                cout << tim.getElapsedTime().asSeconds() << endl;
                current->movedown(tetris);
                
              
                tim.restart();
            }
            
            //check = current->checker1(tetris);
            if (tetris.game_end() == 1 || (*current).end_game(tetris) == 1)
            {
                current->draw(window);
            }
            
        }
        if (c == 1)
        {
            window.display();
            window.clear();
        }
    }
    return 0;
}