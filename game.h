#include"well.h"
#include <SFML/Graphics.hpp>
#include<string>
#include<fstream>
using namespace sf;
class game
{
private:
	string name;
	int score;
	int lines;
	int levels;
	well d;
public:
	game()
	{
		score = 0; lines = 0; levels = 1;
	}
	int getlevel()
	{
		return levels;
	};
	void draw(RenderWindow& window,Sprite &b)
	{
		int g[20][10];
		d.getgrid(g);
		Vector2f s(300, 600), c(30, 30);
		RectangleShape outer(s); /*inner(c)*/ outer.setPosition(150, 100); outer.setFillColor(Color::Black); outer.setOutlineThickness(7); outer.setOutlineColor(Color::Blue);
		window.draw(outer);
		window.draw(b);
		Sprite inner;
		Texture a;
		a.loadFromFile("Images/Empty.png", IntRect(0, 0, 30, 30));
		inner.setTexture(a);
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (g[i][j] == 0)//empty
				{
					/*inner.setOutlineColor(Color::Black);
					inner.setOutlineThickness(0.5);
					inner.setFillColor(Color(0,0,0));*///white
					inner.setPosition((j * 30 + 150), (i * 30 + 100));
					window.draw(inner);
				}
				
			}
			
		}
		/*inner.setOutlineColor(Color::Black);
		inner.setOutlineThickness(0.5);*/

		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (g[i][j] == 1)//I
				{
					//inner.setFillColor(Color(173, 216, 230));
					a.loadFromFile("Images/I.png", IntRect(0, 0, 30, 30));
					inner.setTexture(a);
					inner.setPosition((j * 30 + 150), (i * 30 + 100));
					window.draw(inner);
				}//light blue
				else if (g[i][j] == 2)//J
				{
					//inner.setFillColor(Color(0, 0, 139));
					a.loadFromFile("Images/J.png", IntRect(0, 0, 30, 30));
					inner.setTexture(a);
					inner.setPosition((j * 30 + 150), (i * 30 + 100));
					window.draw(inner);
				}//dark blue
				else if (g[i][j] == 3)//L
				{
					//inner.setFillColor(Color(255, 165, 0));
					a.loadFromFile("Images/L.png", IntRect(0, 0, 30, 30));
					inner.setTexture(a);
					inner.setPosition((j * 30 + 150), (i * 30 + 100));
					window.draw(inner);
				}//orange
				else if (g[i][j] == 4)//O
				{
					//inner.setFillColor(Color(255, 255, 0));
					a.loadFromFile("Images/O.png", IntRect(0, 0, 30, 30));
					inner.setTexture(a);
					inner.setPosition((j * 30 + 150), (i * 30 + 100));
					window.draw(inner);
				}//yellow
				else if (g[i][j] == 5)//S
				{
					//inner.setFillColor(Color(0, 255, 0));
					a.loadFromFile("Images/S.png", IntRect(0, 0, 30, 30));
					inner.setTexture(a);
					inner.setPosition((j * 30 + 150), (i * 30 + 100));
					window.draw(inner);
				}//green
				else if (g[i][j] == 6)//T
				{
					//inner.setFillColor(Color(160, 32, 240));
					a.loadFromFile("Images/T.png", IntRect(0, 0, 30, 30));
					inner.setTexture(a);
					inner.setPosition((j * 30 + 150), (i * 30 + 100));
					window.draw(inner);
				}//purple
				else if (g[i][j] == 7)//Z
				{
					//inner.setFillColor(Color(255, 0, 0));
					a.loadFromFile("Images/Z.png", IntRect(0, 0, 30, 30));
					inner.setTexture(a);
					inner.setPosition((j * 30 + 150), (i * 30 + 100));
					window.draw(inner);
				}//red
				/*inner.setPosition((j * 30), (i * 30));
				window.draw(inner);*/
			}
		}
		//window.display();
	};
	void drawintro(RenderWindow& window, bool &c,Sprite &b)
	{
		Font font;
		font.loadFromFile("Fonts/PixelGamingRegular-d9w0g.ttf");

		int x = 370, y = 330;
		Text playername(name, font, 40);
		playername.setPosition(x, y);

		string n = "Please Enter Your Name:";
		Text text(n, font, 40);
		text.setFillColor(Color(153, 71, 88));
		text.setPosition(190, 240);

		Vector2f s(400, 75);
		RectangleShape box(s);
		box.setPosition(200, 300);
		box.setOutlineColor(Color(153, 71, 88));
		box.setFillColor(Color::Transparent);
		box.setOutlineThickness(5);


		Event event;
		window.pollEvent(event);
		while (event.key.code != Keyboard::Enter && c == 0)
		{
			while (window.pollEvent(event) && c == 0)
			{
				if (event.key.code == Keyboard::Escape)
					window.close();
				if (event.key.code == Keyboard::BackSpace && name != "")
				{
					name.pop_back();
					x = x + 5;
				}
				if (event.key.code == Keyboard::Enter)
				{
					c = 1;
				}
				if (event.type == sf::Event::TextEntered)
				{
					name += event.text.unicode;
					playername.setString(name);
					x = x - 5;
					playername.setPosition(x, y);
				}
			}
			window.clear(Color::Black);
			window.draw(b);
			window.draw(box);
			window.draw(text);
			window.draw(playername);
			window.display();
		}
	}
	void drawscoreboard(RenderWindow& window)
	{
		string sc("Score: "), li("Lines: "), le("Level# ");
		string sc1, li1, le1;
		sc1 = to_string(score);
		li1 = to_string(lines);
		le1 = to_string(levels);
		string sco = sc + sc1;
		string lin = li + li1;
		string lev = le + le1;
		Vector2f e(240, 60);
		RectangleShape d(e);
		d.setOutlineThickness(5);
		d.setOutlineColor(Color(255, 255, 255));
		d.setFillColor(Color::Black);
		for (int i = 1; i < 11; i += 3)
		{
			d.setPosition((12 * 30+150), (i * 30+100));// makes 4 boxes
			window.draw(d);
		}
		Font c;
		c.loadFromFile("Fonts/Nestocopper42-1GVw2.ttf");
		Text nam(name, c, 25);
		Text s(sco, c, 25);
		Text line(lin, c, 25);
		Text level(lev, c, 25);
		nam.setFillColor(Color(255, 255, 255));
		s.setFillColor(Color(255, 255, 255));
		line.setFillColor(Color(255, 255, 255));
		level.setFillColor(Color(255, 255, 255));
		nam.setPosition((13 * 30+150), (1.5 * 30+100));
		s.setPosition((13 * 30+150), (4.5 * 30+100));
		line.setPosition((13 * 30+150), (7.5 * 30+100));
		level.setPosition((13 * 30+150), (10.5 * 30+100));
		window.draw(nam);
		window.draw(s);
		window.draw(line);
		window.draw(level);
	};
	void checker( int prev,float &speed)
	{
		int l = 0;
		int f = d.horizontallinechecker();
		score = score + (f * 100);
		lines += f;
		levels = (score / 1000) + 1;
		levels = levels % 8;
		if (levels == 0)
			levels = 8;
		if (levels > prev)
			speed *= 0.9;
		if (levels == 1)
			speed = 1;
	};
	well returnwell()
	{
		return d;
	};
	bool game_end()
	{
		int g[20][10], c = 0;
		d.getgrid(g);
		for (int j = 0; j < 10; j++)
			if (g[0][j] == 0)
				c++;
		if (c == 10)
			return false;
		return true;
		return false;
	}
	void update(int arr[4][2], int n)
	{
		int g[20][10];
		d.getgrid(g);
		for (int i = 0; i < 4; i++)
			g[arr[i][0]][arr[i][1]] = n;
		d.setgrid(g);
	};
	void GameEndDisplay(RenderWindow& window,bool ch,Sprite back)
	{
		window.draw(back);
		string top_names[5];
		int top_scores[5];
		if(ch==1)
			(*this).store_score();
		ifstream fin("names.txt");
		ifstream fin1("highscores.txt");
		string te;
		int i = 0;
		while (getline(fin1, te) && i < 5)
		{
			top_scores[i] = stoi(te);
			getline(fin, top_names[i]);
			i++;
		}
		Event event;
		while (window.pollEvent(event))
		{
			if (event.key.code == Keyboard::Escape)
				window.close();
		}
		string sc("Score: "), li("Lines: "), le("Level# ");
		string gameend("GAME END!!");
		string sc1, li1, le1;
		string top(" TOP SCORES");
		sc1 = to_string(score);
		li1 = to_string(lines);
		le1 = to_string(levels);
		string sco = sc + sc1;
		string lin = li + li1;
		string lev = le + le1;
		Vector2f e(240, 60);
		Vector2f si(340, 240);
		RectangleShape scoreb(si);
		scoreb.setOutlineThickness(5);
		scoreb.setOutlineColor(Color::White);
		scoreb.setFillColor(Color::Black);
		scoreb.setPosition((15 * 30), (8 * 30));
		RectangleShape d(e);
		d.setOutlineThickness(5);
		d.setOutlineColor(Color::White);
		d.setFillColor(Color::Black);
		Font c;
		c.loadFromFile("Fonts/OpenSans-Italic.ttf");
		string t;
		Text temp;
		temp.setFont(c);
		temp.setCharacterSize(20);
		window.draw(scoreb);
		for (int i = 0; i < 5; i++)
		{
			t = to_string(i + 1) + ": " + top_names[i] + "->"+to_string(top_scores[i]);
			//cout << t << endl;
			temp.setString(t);
			temp.setPosition(460, 240 + ((i ) * 48));
			window.draw(temp);
		}
		for (int i = 5; i < 15; i += 3)
		{
			d.setPosition((5 * 30), (i * 30));// makes 4 boxes
			window.draw(d);
		}
		d.setPosition((15 * 30), (5 * 30));
		window.draw(d);
		d.setPosition((10 * 30), (2 * 30));
		window.draw(d);
		Text nam(name, c, 25);
		Text s(sco, c, 25);
		Text line(lin, c, 25);
		Text level(lev, c, 25);
		Text top1(top, c, 25);
		Text ge(gameend, c, 30);
		ge.setFillColor(Color::White);
		top1.setFillColor(Color::White);
		nam.setFillColor(Color::White);
		s.setFillColor(Color::White);
		line.setFillColor(Color::White);
		level.setFillColor(Color::White);
		nam.setPosition((6 * 30), (5.5 * 30));
		s.setPosition((6 * 30), (8.5 * 30));
		line.setPosition((6 * 30), (11.5 * 30));
		level.setPosition((6 * 30), (14.5 * 30));
		top1.setPosition((16 * 30), (5.5 * 30));
		ge.setPosition((11 * 30), (2.5 * 30));
		window.draw(nam);
		window.draw(s);
		window.draw(line);
		window.draw(level);
		window.draw(top1);
		window.draw(ge);

	}
	void store_score()
	{
		string n[6];
		int h[6];
		ifstream fin("names.txt");
		ifstream num1("highscores.txt");
		string temp;
		int i = 0;
		while (getline(num1, temp) && i < 5)
		{
			h[i] = stoi(temp);
			getline(fin, n[i]);
			i++;
		}
		h[5] = score;
		n[5] = name;
		int min, index;
		for (int size = 6; size > 1; size--)
		{
			min = h[0]; index = 0;
			for(int i=1;i<size;i++)
				if (min > h[i])
				{
					min = h[i];
					index = i;
				}
			swap(h[size - 1], h[index]);
			swap(n[size - 1], n[index]);
		}
		ofstream fout("names.txt");
		ofstream num2("highscores.txt");
		for (int i = 0; i < 5; i++)
		{
			fout << n[i] << endl;
			num2 << h[i] << endl;
		}
		fin.close();
		num1.close();
		fout.close();
		num2.close();
	}
};