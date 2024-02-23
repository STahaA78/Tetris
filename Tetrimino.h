#include<iostream>
#include <SFML/Graphics.hpp>
using namespace std;
class tetrimino
{
protected:
	int rf[1][2];
	int angle;
public:
	tetrimino(int r, int c)//rf stores the index of the top left corner of shape
	{
		rf[0][0] = r;
		rf[0][1] = c;
		angle = 0;
	};
	virtual void  rotate(game& gr) = 0; // Rotates the current tetrimino
	virtual void draw(RenderWindow& window) = 0; //Draws the tetrimino on screen
	virtual void moveright(game& gr) = 0; // Moves the tetrimino right
	virtual void reset() = 0; //Resets the rf value to starting value
	virtual void moveleft(game& gr) = 0; //Moves the tetrimino left
	void movedown(game& gr)
	{
		bool pos = (*this).checker1(gr);
		if (pos == 1)
			rf[0][0]++;
	}; //Moves the tetrimino down
	virtual bool end_game(game& gr) = 0; //Checks if there is space for tetrimino at start
	virtual void indexes(int arr[4][2]) = 0; //Returns the  current coordinate of tetrimino
	virtual bool checker1(game& gr) = 0; //checks wheather there is space for tetrimino to go down
};
class I: public tetrimino
{
public:
	I() :tetrimino(0, 5)
	{
		
	};
	bool checker1(game& gr) //Checks wheather tetrimino could move down
	{ 
		bool pos = 0;
		int c = 0;
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		if (angle == 0 || angle == 180)
		{
			if (rf[0][0] < 16)
			{
				if (grid[rf[0][0] + 4][rf[0][1]] == 0)
				{
					pos = 1;
				}
			}
		}
		else if (angle == 90 || angle == 270)
		{
			if (rf[0][0] < 19)
			{
				c = 0;
				for (int i = 0; i < 4; i++)
					if (grid[rf[0][0] + 1][rf[0][1] + i] == 0)
						c++;
				if (c == 4)
				{
					pos = 1;
				}
			}

		}
		return pos;
	}
	bool end_game(game& gr)
	{
		int c = 0;
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = 0, y = 5;
		for (int i = 0; i < 4; i++)
		{
			if (grid[x + i][y] == 0)
				c++;
		}
		if (c == 4)
			return false;
		return true;
	};
	void reset()
	{
		rf[0][0] = 0;
		rf[0][1] = 5;
		angle = 0;
	};
	void moveright(game & gr)
	{
		int c = 0;
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		if (angle == 0 || angle == 180)
		{
			if (rf[0][1] < 9)
			{
				c = 0;
				for (int i = 0; i < 4; i++)//checks whether right side is free for tetrimino
				{
					if (grid[rf[0][0] + i][rf[0][1] + 1] == 0)
						c++;
				}
				if (c == 4)
					rf[0][1]++;
			}
		}
		else if (angle == 90 || angle == 270)
		{
			if ((rf[0][1] + 3) < 9)
			{
				if (grid[rf[0][0]][rf[0][1] + 4] == 0)
					rf[0][1]++;
			}
		}
	};
	void moveleft(game& gr)
	{
		int c = 0;
		well a = gr.returnwell();
		int grid[20][10];
		int x = rf[0][0], y = rf[0][1];
		a.getgrid(grid);
		if (angle == 0 || angle == 180)
		{
			if (rf[0][1] > 0)
			{
				c = 0;
				for (int i = 0; i < 4; i++)
				{
					if (grid[x + i][y - 1] == 0)
						c++;
				}
				if (c == 4)
					rf[0][1]--;
			}
		}
		else if (angle == 90 || angle == 270)
		{
			if (rf[0][1] > 0)
			{
				if (grid[x][y -1] == 0)
					rf[0][1]--;
			}
		}
	};
	void rotate(game& gr) 
	{
		well a = gr.returnwell();
		int grid[20][10];
		int x = rf[0][0], y = rf[0][1];
		bool down = 0;
		int  l = 0, r = 0, u = 0, d = 0; bool f = 1;
		a.getgrid(grid);
		angle += 90;
		if (angle == 360)
			angle = 0;
		if (angle == 0 || angle == 180)
		{
			for (int i = 2; i > 0; i--)
				if (x + i > 19 || grid[x + i][y + 1] != 0)
					u = 3 - i;
			if (x - 1 < 0 || grid[x - 1][y + 1] != 0)
				d = 1;
			if (d == 1 && u == 0)
			{
				if (x + 3 > 19 || grid[x + 3][y + 1] != 0)
					f = 0;
			}
			else if (d == 0 && u == 1)
			{
				if (x - 2 < 0 || grid[x - 2][y + 1] != 0)
					f = 0;
			}
			else if (d == 0 && u == 2)
			{
				if (x - 3 < 0 || grid[x - 2][y + 1] != 0 || grid[x - 3][y + 1] != 0)
					f = 0;
			}
			else if (d != 0 && u != 0)
				f = 0;
			if (f == 0)
			{
				angle -= 90;
				if (angle == -90)
					angle = 270;
			}
			else
			{
				rf[0][1]++;
				rf[0][0] = rf[0][0] - 1 + d - u;
			}
		}
		else if (angle == 90 || angle == 270)
		{
			for (int i = 2; i > 0; i--)
				if (y + i > 9 || grid[x + 1][y + i] != 0)
					l = 3 - i;
			if (grid[x + 1][y - 1] != 0 || y - 1 < 0)
				r = 1;
			if (r == 1 && l == 0)
			{
				if (y + 3 > 9 || grid[x + 1][y + 3] != 0)
					f = 0;
			}
			else if (r == 0 && l == 1)
			{
				if (y - 2 < 0 || grid[x + 1][y - 2] != 0)
					f = 0;
			}
			else if (r == 0 && l == 2)
			{
				if (y - 3 < 0 || grid[x + 1][y - 2] != 0 || grid[x + 1][y - 3] != 0)
					f = 0;
			}
			else if (r != 0 && l != 0)
				f = 0;
			if (f == 0)
			{
				angle -= 90;
				if (angle == -90)
					angle = 270;
			}
			else
			{
				rf[0][1] = rf[0][1] - 1 + r - l;
				rf[0][0]++;
			}
		}

	};
	void draw(RenderWindow& window)
	{
		Vector2f l(30, 30);
		int x = rf[0][0], y = rf[0][1];
		Sprite box;
		Texture a;
		a.loadFromFile("Images/I.png", IntRect(0, 0, 30, 30));
		box.setTexture(a);
		if (angle == 0 || angle == 180)
		{
			for (int i = 0; i < 4; i++)
			{
				box.setPosition(((y * 30)+150), (((x + i) * 30)+100));
				window.draw(box);
			}
		}
		else if (angle == 90 || angle == 270)
		{
			for (int i = 0; i < 4; i++)
			{
				box.setPosition(((y+i) * 30 + 150), (x * 30 + 100));
				window.draw(box);
			}
		}
	};
	void indexes(int arr[4][2])
	{
		if (angle == 0 || angle == 180)
		{
			for (int i = 0; i < 4; i++)
			{
				arr[i][0] = rf[0][0] + i;
				arr[i][1] = rf[0][1];
			}
		}
		else if (angle == 90 || angle == 270)
		{
			for (int i = 0; i < 4; i++)
			{
				arr[i][0] = rf[0][0];
				arr[i][1] = rf[0][1] + i;
			}
		}
	}
};
class J :public tetrimino
{
public:
	J() :tetrimino(0, 4)
	{

	};
	void draw(RenderWindow& window)
	{
		Vector2f l(30, 30);
		int x = rf[0][0], y = rf[0][1];
		Sprite box;
		Texture a;
		a.loadFromFile("Images/J.png", IntRect(0, 0, 30, 30));
		box.setTexture(a);
		if (angle == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				box.setPosition((y * 30 + 150), ((x + i) * 30 + 100));
				window.draw(box);
			}
			box.setPosition(((y - 1) * 30 + 150), ((x +2) * 30 + 100));
			window.draw(box);
		}
		else if (angle == 90)
		{
			for (int i = 0; i < 2; i++)
			{
				box.setPosition((y * 30 + 150), ((x + i) * 30 + 100));
				window.draw(box);
			}
			for (int i = 1; i < 3; i++)
			{
				box.setPosition(((y + i) * 30 + 150), ((x+1) * 30 + 100));
				window.draw(box);
			}
		}
		else if (angle == 180)
		{
			for (int i = 0; i < 2; i++)
			{
				box.setPosition(((y + i) * 30 + 150), (x * 30 + 100));
				window.draw(box);
			}
			for (int i = 1; i < 3; i++)
			{
				box.setPosition((y * 30 + 150), ((x + i) * 30 + 100));
				window.draw(box);
			}
		}
		else if (angle == 270)
		{
			for (int i = 0; i < 3; i++)
			{
				box.setPosition(((y + i) * 30 + 150), (x * 30 + 100));
				window.draw(box);
			}
			box.setPosition(((y + 2) * 30 + 150), ((x + 1) * 30 + 100));
			window.draw(box);
		}
	};
	void reset()
	{
		rf[0][0] = 0;
		rf[0][1] = 4;
		angle = 0;
	};
	bool end_game(game& gr)
	{
		int c = 0;
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = 0, y = 4;
		for (int i = 0; i < 3; i++)
			if (grid[x + i][y] == 0)
				c++;
		if (grid[x +2][y - 1] == 0)
			c++;
		if (c == 4)
			return false;
		return true;
	};
	bool checker1(game& gr)
	{
		bool pos = 0;
		int c = 0;
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		if (angle == 0)
		{
			if (rf[0][0] < 17)
			{
				if (grid[rf[0][0] + 3][rf[0][1]] == 0 && grid[rf[0][0] + 3][rf[0][1] - 1] == 0)
					pos = 1;
			}
		}
		else if (angle == 90)
		{
			if (rf[0][0] < 18)
			{
				for (int i = 0; i < 3; i++)
				{
					if (grid[rf[0][0] + 2][rf[0][1] + i] == 0)
						c++;
				}
				if (c == 3)
					pos = 1;
			}
		}
		else if (angle == 180)
		{
			if (rf[0][0] < 17)
			{
				if (grid[rf[0][0] + 3][rf[0][1]] == 0 && grid[rf[0][0] + 1][rf[0][1] + 1] == 0)
					pos = 1;
			}
		}
		else if (angle == 270)
		{
			if (rf[0][0] < 18)
			{
				for (int i = 0; i < 2; i++)
					if (grid[rf[0][0] + 1][rf[0][1] + i] == 0)
						c++;
				if (grid[rf[0][0] + 2][rf[0][1] + 2] == 0)
					c++;
				if (c == 3)
					pos = 1;
			}
		}
		return pos;
	};
	void indexes(int arr[4][2])
	{
		if (angle == 0)
		{
			for (int i = 0; i < 3; i++)//Stores the index of the vertical 3 blocks
			{
				arr[i][0] = rf[0][0] + i;
				arr[i][1] = rf[0][1];
			}
			arr[3][0] = rf[0][0] + 2;//Index of left bottom block being stored
			arr[3][1] = rf[0][1] - 1;
		}
		else if (angle == 90)
		{
			for (int i = 0; i < 2; i++)//Index of starting 2 vertical blocks being stored
			{
				arr[i][0] = rf[0][0] + i;
				arr[i][1] = rf[0][1];
			}
			for (int i = 1; i < 3; i++)//Index of  2 bottom right blocks being stored
			{
				arr[i + 1][0] = rf[0][0] + 1;
				arr[i + 1][1] = rf[0][1] + i;
			}
		}
		else if (angle == 180)
		{
			for (int i = 0; i < 2; i++)//storing indexes of top 2 horizontal blocks
			{
				arr[i][0] = rf[0][0];
				arr[i][1] = rf[0][1] + i;
			}
			for (int i = 1; i < 3; i++)//storing indexes of bottom 2 vertical blocks
			{
				arr[i + 1][0] = rf[0][0] + i;
				arr[i + 1][1] = rf[0][1];
			}
		}
		else if (angle == 270)
		{
			for (int i = 0; i < 3; i++)//storing index of horizontal top 3 blocks
			{
				arr[i][0] = rf[0][0];
				arr[i][1] = rf[0][1] + i;
			}
			arr[3][0] = rf[0][0] + 1;//storing index of bottom right block
			arr[3][1] = rf[0][1] + 2;
		}
	};
	void moveright(game& gr)
	{
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = rf[0][0], y = rf[0][1];
		if (angle == 0)
		{
			if (rf[0][1] < 9)
			{
				if (grid[x][y + 1] == 0 && grid[x + 1][y + 1] == 0 && grid[x + 2][y + 1] == 0)
					rf[0][1]++;
			}
		}
		else if (angle == 90)
		{
			if (rf[0][1] < 7)
			{
				if (grid[x][y + 1] == 0 && grid[x + 1][y + 3] == 0)
					rf[0][1]++;
			}
		}
		else if (angle == 180)
		{
			if (rf[0][1] < 8)
			{
				if (grid[x][y + 2] == 0 && grid[x + 1][y + 1] == 0 && grid[x + 2][y + 1] == 0)
					rf[0][1]++;
			}
		}
		else if (angle == 270)
		{
			if (rf[0][1] < 7)
			{
				if (grid[x][y + 3] == 0 && grid[x + 1][y + 3] == 0)
					rf[0][1]++;
			}
		}
	};
	void moveleft(game& gr)
	{
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = rf[0][0], y = rf[0][1];
		if (angle == 0  )
		{
			if (rf[0][1] > 1)
			{
				if (grid[x][y - 1] == 0 && grid[x + 1][y - 1] == 0 && grid[x + 2][y - 2] == 0)
					rf[0][1]--;
			}
		}
		else if (angle == 90)
		{
			if (rf[0][1] > 0)
			{
				if (grid[x][y - 1] == 0 && grid[x + 1][y - 1] == 0 )
					rf[0][1]--;
			}
		}
		else if (angle == 180)
		{
			if (rf[0][1] > 0)
			{
				if (grid[x][y - 1] == 0 && grid[x + 1][y - 1] == 0 && grid[x + 2][y - 1] == 0)
					rf[0][1]--;
			}
		}
		else if (angle == 270)
		{
			if (rf[0][1] > 0)
			{
				if (grid[x][y - 1] == 0 && grid[x + 1][y + 1] == 0)
					rf[0][1]--;
			}
		}
	};
	void  rotate(game& gr)
	{
		bool up = 0, down = 0;
		well a = gr.returnwell();
		int grid[20][10];
		int x = rf[0][0], y = rf[0][1];
		int r = 0, u = 0, d = 0, l = 0; 
		bool f = 1;
		a.getgrid(grid);
		angle += 90;
		if (angle == 360)
			angle = 0;
		if (angle == 0)
		{
			if (grid[x + 1][y] != 0)
				r = 1;
			if (grid[x + 1][y + 1] != 0)
				u = 1;
			if (x - 1 < 0 || grid[x - 1][y + 1] != 0)
				d = 1;
			if (u == 0 && d == 1)
			{
				if (r == 0)
				{
					if (x + 2 > 19 || grid[x + 2][y] != 0 || grid[x + 2][y + 1] != 0)
						f = 0;
				}
				else
					if (x + 2 > 19 || grid[x + 2][y + 1] != 0 || grid[x + 2][y + 2] != 0)
						f = 0;
			}
			else if (u == 1 && d == 0)
			{
				if (r == 0)
				{
					if (x - 2 < 0 || grid[x - 2][y + 1] != 0)
						f = 0;
				}
				else
					if (x - 2 < 0 || grid[x - 2][y + 2] != 0 || grid[x - 1][y + 2] != 0)
						f = 0;
			}
			else if (u == 0 && d == 0 && r == 1)
			{
				if (x - 1 < 0 || grid[x - 1][y + 2] != 0)
					f = 0;
			}
			else if (u != 0 && d != 0)
				f = 0;
			if (f == 0)
				angle = 270;
			else
			{
				rf[0][0] = rf[0][0] - 1 - u + d;
				rf[0][1] = rf[0][1] + 1 + r;
			}
		}
		else if (angle == 90)
		{
			if (grid[x][y - 1] != 0)
				d = 1;
			if (grid[x + 1][y - 1] != 0)
				r = 1;
			if(y+1>9||grid[x+1][y+1]!=0)
				l=1;
			if (r == 1 && l == 0)
			{
				if (d == 0)
				{
					if (y + 2 > 9 || grid[x + 1][y + 2] != 0)
						f = 0;
				}
				else
				{
					if (y + 2 > 9 || grid[x + 2][y + 2] != 0 || grid[x + 2][y + 1] != 0)
						f = 0;
				}

			}
			else if (r == 0 && l == 1)
			{
				if (d == 0)
				{
					if (y - 2 < 0 || grid[x + 1][y - 2] != 0 || grid[x][y - 2] != 0)
						f = 0;
				}
				else
				{
					if (y - 2 < 0 || grid[x + 1][y - 2] != 0 || grid[x + 2][y - 2] != 0)
						f = 0;
				}
			}
			else if (r == 0 && l == 0 && d == 1)
			{
				if (grid[x + 2][y + 1] != 0)
					f = 0;
			}
			else if (r != 0 && l != 0)
				f = 0;
			if (f == 0)
				angle = 0;
			else
			{
				rf[0][0] += d;
				rf[0][1] = rf[0][1] - 1 - l + r;
			}
		}
		else if (angle == 180)
		{
			if (grid[x][y + 2] != 0)
				l = 1;
			if (grid[x][y + 1] != 0)
				d = 1;
			if (x + 2 > 19 || grid[x + 2][y + 1] != 0)
				u = 1;
			if (u == 1 && d == 0)
			{
				if (l == 0)
				{
					if (x - 1 < 0 || grid[x - 1][y + 1] != 0 || grid[x - 1][y + 2] != 0)
						f = 0;
				}
				else
					if (x - 1 < 0 || grid[x - 1][y + 1] != 0 || grid[x - 1][y] != 0)
						f = 0;
			}
			else if (u == 0 && d == 1)
			{
				if (l == 0)
				{
					if (x + 3 > 19 || grid[x + 3][y + 1] != 0)
						f = 0;
				}
				else
					if (x + 3 > 19 || grid[x + 2][y] != 0 || grid[x + 3][y] != 0)
						f = 0;
			}
			else if (u == 0 && d == 0 && l == 1)
			{
				if (x + 2 > 19 || grid[x + 2][y] != 0)
					f = 0;
			}
			else if (u != 0 && d != 0)
				f = 0;
			if (f == 0)
			{
				angle = 90;
			}
			else
			{
				rf[0][0] = rf[0][0] + d - u;
				rf[0][1] = rf[0][1] + 1 - l;
			}
		}
		else if (angle == 270)
		{
			if (y - 1 < 0 || grid[x + 1][y - 1] != 0)
				r = 1;
			if (grid[x + 1][y + 1] != 0)
				l = 1;
			if (grid[x + 2][y + 1] != 0)
				u = 1;
			if (r == 1 && l == 0)
			{
				if (u == 0)
				{
					if (y + 2 > 9 || grid[x + 1][y + 2] != 0 || grid[x + 2][y + 2] != 0)
						f = 0;
				}
				else
					if (y + 2 > 9 || grid[x][y + 2] != 0 || grid[x + 1][y + 2] != 0)
						f = 0;
			}
			else if (r == 0 && l == 1)
			{
				if (u == 0)
				{
					if (y - 2 < 0 || grid[x + 1][y - 2] != 0)
						f = 0;
				}
				else
					if (y - 2 < 0 || grid[x][y - 2] != 0 || grid[x][y - 1] != 0)
						f = 0;
			}
			else if (r == 0 && l == 0 && u == 1)
			{
				if (y - 1 < 0 || grid[x][y - 1] != 0)
					f = 0;
			}
			else if (r != 0 && l != 0)
				f = 0;
			if (f == 0)
				angle = 180;
			else
			{
				rf[0][1] = rf[0][1] - 1 + r - l;
				rf[0][0] = rf[0][0] + 1 - u;
			}
		}
	}
};
class L :public tetrimino
{
public:
	L() :tetrimino(0, 4)
	{

	};
	void  rotate(game& gr)
	{
		int down = 0, up = 0;
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = rf[0][0], y = rf[0][1];
		int r = 0, u = 0, l = 0, d = 0; bool f = 1;
		angle += 90;
		if (angle == 360)
			angle = 0;
		if (angle == 0)
		{
			if (grid[x][y - 1] != 0)
				d = 1;
			if (x + 2 > 19 || grid[x + 2][y - 1] != 0)
				u = 1;
			if (x + 2 > 19 || grid[x + 2][y] != 0)
				l = 1;
			if (d == 1 && u == 0)
			{
				if (l == 0)
				{
					if (x + 3 > 19 || grid[x + 3][y - 1] != 0 || grid[x + 3][y] != 0)
						f = 0;
				}
				else
					if (x + 3 > 19 || grid[x + 3][y - 2] != 0 || grid[x + 3][y - 1] != 0 && grid[x + 2][y - 2] != 0)
						f = 0;
			}
			else if (d == 0 && u == 1)
			{
				if (l == 0)
				{
					if (x - 1 < 0 || grid[x - 1][y - 1] != 0)
						f = 0;
				}
				else
					if (x - 1 < 0 || grid[x - 1][y - 2] != 0 || grid[x][y - 2] != 0)
						f = 0;
			}
			else if (d == 0 && u == 0 && l == 1)
			{
				if (grid[x][y - 2] != 0 || grid[x + 2][y - 2] != 0)
					f = 0;
			}
			else if (d != 0 && u != 0)
				f = 0;
			if (f == 0)
			{
				angle = 270;
			}
			else
			{
				rf[0][0] = rf[0][0] + d - u;
				rf[0][1] = rf[0][1] - 1 - l;
			}
		}
		else if (angle == 90)
		{
			if (grid[x + 1][y + 1] != 0)
				l = 1;
			if (y - 1 < 0 || grid[x + 1][y - 1] != 0)
				r = 1;
			if (y - 1 < 0 || grid[x + 2][y - 1] != 0)
				u = 1;
			if (r == 1 && l == 0)
			{
				if (u == 0)
				{
					if (y + 2 > 9 || grid[x + 1][y + 2] != 0)
						f = 0;
				}
				else
					if (y + 2 > 9 || grid[x][y + 1] != 0 || grid[x][y + 2] != 0)
						f = 0;
			}
			else if (r == 0 && l == 1)
			{
				if (u == 0)
				{
					if (y - 2 < 0 || grid[x + 1][y - 2] != 0 || grid[x + 2][y - 2] != 0)
						f = 0;
				}
				else
					if (y - 2 < 0 || grid[x][y - 2] != 0 || grid[x + 1][y - 2] != 0 || grid[x][y - 1] != 0)
						f = 0;
			}
			else if (r == 0 && l == 0 && u == 1)
			{
				if (y - 1 < 0 || grid[x][y - 1] != 0 || grid[x][y + 1] != 0)
					f = 0;
			}
			else if (r != 0 && l != 0)
				f = 0;
			if (f == 0)
				angle = 0;
			else
			{
				rf[0][0] = rf[0][0] + 1 - u;
				rf[0][1] = rf[0][1] - 1 + r - l;
			}
		}
		else if (angle == 180)
		{
			if (x - 1 < 0 || grid[x - 1][y] != 0)
				r = 1;
			if (x - 1 < 0 || grid[x - 1][y + 1] != 0)
				d = 1;
			if (grid[x + 1][y + 1] != 0)
				u = 1;
			if (u == 1 && d == 0)
			{
				if (r == 0)
				{
					if (x - 2 < 0 || grid[x - 2][y] != 0 || grid[x - 2][y + 1] != 0)
						f = 0;
				}
				else
					if (x - 2 < 0 || grid[x - 2][y + 2] != 0 || grid[x - 2][y + 1] != 0 || grid[x - 1][y + 2] != 0)
						f = 0;
			}
			else if (u == 0 && d == 1)
			{
				if (r == 0)
				{
					if (x + 2 > 19 || grid[x + 2][y + 1] != 0)
						f = 0;
				}
				else
					if (x + 2 > 19 || grid[x + 2][y + 2] != 0 || grid[x + 1][y + 2] != 0)
						f = 0;
			}
			else if (u == 0 && d == 0 && r == 1)
			{
				if (x - 1 < 0 || grid[x - 1][y + 2] != 0 || grid[x + 1][y + 2] != 0)
					f = 0;
			}
			else if (u != 0 && d != 0)
				f = 0;
			if (f == 0)
			{
				angle = 90;
			}
			else
			{
				rf[0][0] = rf[0][0] - 1 - u + d;
				rf[0][1] += r;
			}
		}
		else if (angle == 270)
		{
			if (grid[x + 1][y] != 0)
				r = 1;
			if (y + 2 > 9 || grid[x + 1][y + 2] != 0)
				l = 1;
			if (y + 2 > 9 || grid[x][y + 2] != 0)
				d = 1;
			if (r == 1 && l == 0)
			{
				if (d == 0)
				{
					if (y + 3 > 9 || grid[x][y + 3] != 0 || grid[x + 1][y + 3] != 0)
						f = 0;
				}
				else
					if (y + 3 > 9 || grid[x + 1][y + 3] != 0 || grid[x + 2][y + 2] != 0 || grid[x + 2][y + 3] != 0)
						f = 0;
			}
			else if (r == 0 && l == 1)
			{
				if (d == 0)
				{
					if (y - 1 < 0 || grid[x + 1][y - 1] != 0)
						f = 0;
				}
				else
					if (y - 1 < 0 || grid[x + 2][y - 1] != 0 || grid[x + 2][y] != 0)
						f = 0;
			}
			else if (r == 0 && l == 0 && d == 1)
			{
				if (y + 2 > 9 || grid[x + 2][y] != 0 || grid[x + 2][y + 2] != 0)
					f = 0;
			}
			else if (r != 0 && l != 0)
				f = 0;
			if (f == 0)
				angle = 180;
			else
			{
				rf[0][1] = rf[0][1] + 2 + r - l;
				rf[0][0] += d;
			}
		}
	};
	void reset()
	{
		rf[0][0] = 0;
		rf[0][1] = 4;
		angle = 0;
	};
	bool end_game(game& gr)
	{
		int c = 0;
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = 0, y = 4;
		for (int i = 0; i < 3; i++)
			if (grid[x + i][y] == 0)
				c++;
		if (grid[x + 2][y + 1] == 0)
			c++;
		if (c == 4)
			return false;
		return true;
	};
	bool checker1(game& gr)
	{
		bool pos = 0;
		int c = 0;
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		if (angle == 0)
		{
			if (rf[0][0] < 17)
				if (grid[rf[0][0] + 3][rf[0][1]] == 0 && grid[rf[0][0] + 3][rf[0][1] + 1] == 0)
					pos = 1;
		}
		else if (angle == 90)
		{
			if (rf[0][0] < 18)
				if (grid[rf[0][0] + 2][rf[0][1]] == 0 && grid[rf[0][0] + 1][rf[0][1] + 1] == 0 && grid[rf[0][0] + 1][rf[0][1] + 2] == 0)
					pos = 1;
		}
		else if (angle == 180)
		{
			if (rf[0][0] < 17)
				if (grid[rf[0][0] + 1][rf[0][1]] == 0 && grid[rf[0][0] + 3][rf[0][1] + 1] == 0)
					pos = 1;
		}
		else if (angle == 270)
		{
			if (rf[0][0] < 18)
				if (grid[rf[0][0] + 2][rf[0][1]] == 0 && grid[rf[0][0] + 2][rf[0][1] - 1] == 0 && grid[rf[0][0] + 2][rf[0][1] - 2] == 0)
					pos = 1;

		}
		return pos;
	};
	void indexes(int arr[4][2])
	{
		if (angle == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				arr[i][0] = rf[0][0] + i;
				arr[i][1] = rf[0][1];
			}
			arr[3][0] = rf[0][0] + 2;
			arr[3][1] = rf[0][1] + 1;
		}
		else if (angle == 90)
		{
			for (int i = 0; i < 3; i++)
			{
				arr[i][0] = rf[0][0];
				arr[i][1] = rf[0][1] + i;
			}
			arr[3][0] = rf[0][0] + 1;
			arr[3][1] = rf[0][1];
		}
		else if (angle == 180)
		{
			for (int i = 0; i < 3; i++)
			{
				arr[i][0] = rf[0][0] + i;
				arr[i][1] = rf[0][1] + 1;
			}
			arr[3][0] = rf[0][0];
			arr[3][1] = rf[0][1];
		}
		else if (angle == 270)
		{
			for (int i = 0; i < 3; i++)
			{
				arr[i][0] = rf[0][0] + 1;
				arr[i][1] = rf[0][1] - i;
			}
			arr[3][0] = rf[0][0];
			arr[3][1] = rf[0][1];
		}
	};
	void moveright(game& gr)
	{

		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = rf[0][0], y = rf[0][1];
		if (angle == 0)
		{
			if (y < 8)
				if (grid[x][y + 1] == 0 && grid[x + 1][y + 1] == 0 && grid[x + 2][y + 2] == 0)
					rf[0][1]++;
		}
		else if (angle == 90)
		{
			if (y < 7)
				if (grid[x][y + 3] == 0 && grid[x + 1][y + 1] == 0)
					rf[0][1]++;
		}
		else if (angle == 180)
		{
			if (y < 8)
				if (grid[x][y + 2] == 0 && grid[x + 1][y + 2] == 0 && grid[x + 2][y + 2] == 0)
					rf[0][1]++;
		}
		else if (angle == 270)
		{
			if (y < 9)
				if (grid[x][y + 1] == 0 && grid[x + 1][y + 1] == 0)
					rf[0][1]++;
		}
	};
	void moveleft(game& gr)
	{
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = rf[0][0], y = rf[0][1];
		if (angle == 0)
		{
			if (y > 0)
				if (grid[x][y - 1] == 0 && grid[x + 1][y - 1] == 0 && grid[x + 2][y - 1] == 0)
					rf[0][1]--;
		}
		else if (angle == 90)
		{
			if (y > 0)
				if (grid[x][y - 1] == 0 && grid[x + 1][y - 1] == 0)
					rf[0][1]--;

		}
		else if (angle == 180)
		{
			if (y > 0)
				if (grid[x + 1][y] == 0 && grid[x + 2][y] == 0 && grid[x][y - 1] == 0)
					rf[0][1]--;
		}
		else if (angle == 270)
		{
			if (y > 2)
				if (grid[x][y - 1] == 0 && grid[x + 1][y - 3] == 0)
					rf[0][1]--;
		}
	};
	void draw(RenderWindow& window)
	{
		int x = rf[0][0], y = rf[0][1];
		Sprite box;
		Texture a;
		a.loadFromFile("Images/L.png", IntRect(0, 0, 30, 30));
		box.setTexture(a);
		if (angle == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				box.setPosition((y * 30 + 150), ((x + i) * 30 + 100));
				window.draw(box);
			}
			box.setPosition(((y + 1) * 30 + 150), ((x + 2) * 30 + 100));
			window.draw(box);
		}
		else if (angle == 90)
		{
			for (int i = 0; i < 3; i++)
			{
				box.setPosition(((y + i) * 30 + 150), (x * 30 + 100));
				window.draw(box);
			}
			box.setPosition((y * 30 + 150), ((x + 1) * 30 + 100));
			window.draw(box);
		}
		else if (angle == 180)
		{
			for (int i = 0; i < 3; i++)
			{
				box.setPosition(((y + 1) * 30 + 150), ((x + i) * 30 + 100));
				window.draw(box);
			}
			box.setPosition((y * 30 + 150), (x * 30 + 100));
			window.draw(box);
		}
		else if (angle == 270)
		{
			for (int i = 0; i < 3; i++)
			{
				box.setPosition(((y - i) * 30 + 150), ((x + 1) * 30 + 100));
				window.draw(box);
			}
			box.setPosition((y * 30 + 150), (x * 30 + 100));
			window.draw(box);
		}
	};
};
class O :public tetrimino
{
public:
	O() :tetrimino(0, 4)
	{

	};
	void draw(RenderWindow& window)
	{
		int x = rf[0][0], y = rf[0][1];
		Sprite box;
		Texture a;
		a.loadFromFile("Images/O.png", IntRect(0, 0, 30, 30));
		box.setTexture(a);
		for (int i = 0; i < 2; i++)
		{
			box.setPosition(((y + i) * 30 + 150), (x * 30 + 100));
			window.draw(box);
		}
		for (int i = 0; i < 2; i++)
		{
			box.setPosition(((y + i) * 30 + 150), ((x + 1) * 30 + 100));
			window.draw(box);
		}
	};
	void reset()
	{
		rf[0][0] = 0;
		rf[0][1] = 4;
		angle = 0;
	};
	bool end_game(game& gr)
	{
		int c = 0;
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = 0, y = 4;
		for (int i = 0; i < 2; i++)
		{
			if (grid[x ][y+i] == 0)
				c++;
		}
		for (int i = 0; i < 2; i++)
		{
			if (grid[x + 1][y+i] == 0)
				c++;
		}
		if (c == 4)
			return false;
		return true;
	};
	bool checker1(game& gr)
	{
		bool pos = 0;
		int c = 0;
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		if (rf[0][0] < 18)
			if (grid[rf[0][0] + 2][rf[0][1]] == 0 && grid[rf[0][0] + 2][rf[0][1] + 1] == 0)
				pos = 1;
		return pos;
	};
	void indexes(int arr[4][2])
	{
		for (int i = 0; i < 2; i++)
		{
			arr[i][0] = rf[0][0];
			arr[i][1] = rf[0][1] + i;
		}
		for (int i = 0; i < 2; i++)
		{
			arr[i + 2][0] = rf[0][0] + 1;
			arr[i + 2][1] = rf[0][1] + i;
		}
	}
	void moveright(game& gr)
	{

		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = rf[0][0], y = rf[0][1];
		if (y < 8)
			if (grid[x][y + 2] == 0 && grid[x + 1][y + 2] == 0)
				rf[0][1]++;
	};
	void moveleft(game& gr)
	{
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = rf[0][0], y = rf[0][1];
		if (y > 0)
			if (grid[x][y - 1] == 0 && grid[x + 1][y - 1] == 0)
				rf[0][1]--;
	}
	void  rotate(game& gr)
	{

	};
};
class S : public tetrimino
{
public:
	S() :tetrimino(0, 5)
	{

	};
	void reset()
	{
		rf[0][0] = 0;
		rf[0][1] = 5;
		angle = 0;
	};
	bool end_game(game& gr)
	{
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = 0, y = 5;
		if (grid[x][y] == 0 && grid[x][y + 1] == 0 && grid[x + 1][y] == 0 && grid[x + 1][y - 1] == 0)
			return false;
		return true;
	};
	bool checker1(game& gr)
	{
		bool pos = 0;
		int c = 0;
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = rf[0][0], y = rf[0][1];
		if (angle == 0 || angle == 180)
		{
			if (x < 18)
				if (grid[x + 1][y + 1] == 0 && grid[x +2][y - 1] == 0 && grid[x +2][y] == 0)
					pos = 1;
		}
		else if (angle == 90 || angle == 270)
		{
			if (x < 17)
				if (grid[x + 2][y] == 0 && grid[x + 3][y + 1] == 0)
					pos = 1;
		}
		return pos;
	};
	void indexes(int arr[4][2])
	{
		int x = rf[0][0], y = rf[0][1];
		if (angle == 0 || angle == 180)
		{
			arr[0][0] = x; arr[0][1] = y;
			arr[1][0] = x; arr[1][1] = y + 1;
			arr[2][0] = x + 1; arr[2][1] = y - 1;
			arr[3][0] = x + 1; arr[3][1] = y;
		}
		else if (angle == 90 || angle == 270)
		{
			arr[0][0] = x; arr[0][1] = y;
			arr[1][0] = x + 1; arr[1][1] = y + 1;
			arr[2][0] = x + 2; arr[2][1] = y + 1;
			arr[3][0] = x + 1; arr[3][1] = y;
		}
	}
	void moveright(game& gr)
	{

		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = rf[0][0], y = rf[0][1];
		if (angle == 0 || angle == 180)
		{
			if (y < 8)
				if (grid[x][y + 2] == 0 && grid[x + 1][y + 1] == 0)
					rf[0][1]++;
		}
		else if (angle == 90 || angle == 270)
		{
			if (y < 8)
				if (grid[x][y + 1] == 0 && grid[x + 1][y + 2] == 0 && grid[x + 2][y + 2] == 0)
					rf[0][1]++;
		}
	};
	void moveleft(game& gr)
	{
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = rf[0][0], y = rf[0][1];
		if (angle == 0 || angle == 180)
		{
			if (y > 1)
				if (grid[x][y - 1] == 0 && grid[x + 1][y - 2] == 0)
					rf[0][1]--;
		}
		else if (angle == 90 || angle == 270)
		{
			if (y > 0)
				if (grid[x][y - 1] == 0 && grid[x + 1][y - 1] == 0 && grid[x + 2][y] == 0)
					rf[0][1]--;
		}
	};
	void draw(RenderWindow& window)
	{
		int x = rf[0][0], y = rf[0][1];
		Sprite box;
		Texture a;
		a.loadFromFile("Images/S.png", IntRect(0, 0, 30, 30));
		box.setTexture(a);
		if (angle == 0 || angle == 180)
		{
			for (int i = 0; i < 2; i++)
			{
				box.setPosition(((y + i) * 30 + 150), (x * 30 + 100));
				window.draw(box);
			}
			for (int i = 0; i < 2; i++)
			{
				box.setPosition(((y - i) * 30 + 150), ((x + 1) * 30 + 100));
				window.draw(box);
			}
		}
		else if (angle == 90 || angle == 270)
		{
			for (int i = 0; i < 2; i++)
			{
				box.setPosition(((y) * 30 + 150), ((x + i) * 30 + 100));
				window.draw(box);
			}
			for (int i = 0; i < 2; i++)
			{
				box.setPosition(((y + 1) * 30 + 150), ((x + 1 + i) * 30 + 100));
				window.draw(box);
			}
		}
	};
	void  rotate(game& gr)
	{
		well a = gr.returnwell();
		int grid[20][10];
		int x = rf[0][0], y = rf[0][1];
		int c = 0, u = 0, d = 0;
		bool f = 1;
		a.getgrid(grid);
		angle += 90;
		if (angle == 360)
			angle = 0;
		if (angle == 0 || angle == 180)
		{
			for (int i = 1; i >= 0; i--)
				if (y - i < 0 || grid[x + 2][y - i] != 0)
					c = 2 - i;
			if (c == 1)
			{
				if (y + 2 > 9 || grid[x + 1][y + 2] != 0)
					f = 0;
			}
			else if (c == 2)
				if (y + 3 > 9 || grid[x + 2][y + 2] != 0 || grid[x + 1][y + 2] != 0 || grid[x + 1][y + 3] != 0)
					f = 0;
			if (f == 0)
			{
				angle -= 90;
				if (angle == -90)
					angle = 270;
			}
			else
			{
				rf[0][0]++;
				rf[0][1] += c;
			}
		}
		else if (angle == 90 || angle == 270)
		{
			if (grid[x - 1][y] != 0 || x - 1 < 0)
				d = 1;
			if (grid[x + 1][y + 1] != 0)
				u = 1;
			if (d == 1 && u == 0)
			{
				if (x + 2 > 19 || grid[x + 2][y + 1] != 0)
					f = 0;
			}
			else if (d == 0 && u == 1)
			{
				if (x - 2 < 0 || grid[x - 2][y] != 0 || grid[x - 1][y + 1] != 0)
					f = 0;
			}
			else if (d == 1 && u == 1)
				f = 0;
			if (f == 0)
			{
				angle -= 90;
				if (angle == -90)
					angle = 270;
			}
			else
				rf[0][0] = rf[0][0] - 1 + d - u;
		}
	};
};
class T : public tetrimino
{
public:
	T() :tetrimino(0, 4)
	{

	};
	void reset()
	{
		rf[0][0] = 0;
		rf[0][1] = 4;
		angle = 0;
	};
	bool end_game(game& gr)
	{
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = 0, y = 4;
		if (grid[x][y] == 0 && grid[x][y + 1] == 0 && grid[x][y + 2] == 0 && grid[x + 1][y + 1] == 0)
			return false;
		return true;
	};
	bool checker1(game& gr)
	{
		bool pos = 0;
		int c = 0;
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = rf[0][0], y = rf[0][1];
		if (angle == 0)
		{
			if (x < 18)
				if (grid[x + 1][y] == 0 && grid[x + 1][y + 2] == 0 && grid[x + 2][y + 1] == 0)
					pos = 1;
			//cout << pos;
		}
		else if (angle == 90)
		{
			if (x < 17)
				if (grid[x + 2][y - 1] == 0 && grid[x + 3][y] == 0)
					pos = 1;
		}
		else if (angle == 180)
		{
			if (x < 18)
				if (grid[x + 2][y] == 0 && grid[x + 2][y - 1] == 0 && grid[x + 2][y + 1] == 0)
					pos = 1;
		}
		else if (angle == 270)
		{
			if (x < 17)
			{
				if (grid[x + 2][y + 1] == 0 && grid[x + 3][y] == 0)
					pos = 1;
			}
		}
		//cout << pos;
		return pos;
	};
	void indexes(int arr[4][2])
	{
		int x = rf[0][0], y = rf[0][1];
		if (angle == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				arr[i][0] = x;
				arr[i][1] = y + i;
			}
			arr[3][0] = x + 1;
			arr[3][1] = y + 1;
		}
		else if (angle == 90)
		{
			for (int i = 0; i < 3; i++)
			{
				arr[i][0] = x + i;
				arr[i][1] = y;
			}
			arr[3][0] = x + 1;
			arr[3][1] = y - 1;
		}
		else if (angle == 180)
		{
			y = rf[0][1] - 1;
			for (int i = 0; i < 3; i++)
			{
				arr[i][0] = x + 1;
				arr[i][1] = y + i;
			}
			arr[3][0] = x;
			arr[3][1] = y + 1;
		}
		else if (angle == 270)
		{

			for (int i = 0; i < 3; i++)
			{
				arr[i][0] = x + i;
				arr[i][1] = y;
			}
			arr[3][0] = x + 1;
			arr[3][1] = y + 1;
		}
	};
	void moveright(game& gr)
	{
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = rf[0][0], y = rf[0][1];
		if (angle == 0)
		{
			if (y < 7)
				if (grid[x][y + 3] == 0 && grid[x + 1][y + 2] == 0)
					rf[0][1]++;
		}
		else if (angle == 90)
		{
			if (y < 9)
				if (grid[x][y + 1] == 0 && grid[x + 1][y + 1] == 0 && grid[x + 2][y + 1] == 0)
					rf[0][1]++;
		}
		else if (angle == 180)
		{
			if (y < 8)
				if (grid[x + 1][y + 2] == 0 && grid[x][y + 1] == 0)
					rf[0][1]++;
		}
		else if (angle == 270)
		{
			if (y < 8)
				if (grid[x][y + 1] == 0 && grid[x + 1][y + 2] == 0 && grid[x + 2][y + 1] == 0)
					rf[0][1]++;
		}
	};
	void moveleft(game& gr)
	{
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = rf[0][0], y = rf[0][1];
		if (angle == 0)
		{
			if (y > 0)
				if (grid[x][y - 1] == 0 && grid[x + 1][y] == 0)
					rf[0][1]--;
		}
		else if (angle == 90)
		{
			if (y > 1)
				if (grid[x][y - 1] == 0 && grid[x + 1][y - 2] == 0 && grid[x + 2][y - 1] == 0)
					rf[0][1]--;
		}
		else if (angle == 180)
		{
			if (y > 1)
				if (grid[x][y - 1] == 0 && grid[x + 1][y - 2] == 0)
					rf[0][1]--;
		}
		else if (angle == 270)
		{
			if(y>0)
				if (grid[x][y - 1] == 0 && grid[x + 1][y - 1] == 0 && grid[x + 2][y - 1] == 0)
					rf[0][1]--;
		}
	};
	void draw(RenderWindow& window)
	{
		int x = rf[0][0], y = rf[0][1];
		Sprite box;
		Texture a;
		a.loadFromFile("Images/T.png", IntRect(0, 0, 30, 30));
		box.setTexture(a);
		if (angle == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				box.setPosition(((y + i) * 30 + 150), (x * 30 + 100));
				window.draw(box);
			}
			box.setPosition(((y + 1) * 30 + 150), ((x + 1) * 30 + 100));
			window.draw(box);
		}
		else if (angle == 90)
		{
			for (int i = 0; i < 3; i++)
			{
				box.setPosition((y * 30 + 150), ((x + i) * 30 + 100));
				window.draw(box);
			}
			box.setPosition(((y - 1) * 30 + 150), ((x + 1) * 30 + 100));
			window.draw(box);
		}
		else if (angle == 180)
		{
			y = rf[0][1] - 1;
			for (int i = 0; i < 3; i++)
			{
				box.setPosition(((y + i) * 30 + 150), ((x + 1) * 30 + 100));
				window.draw(box);
			}
			box.setPosition(((y + 1) * 30 + 150), (x * 30 + 100));
			window.draw(box);
		}
		else if (angle == 270)
		{
			for (int i = 0; i < 3; i++)
			{
				box.setPosition((y * 30 + 150), ((x + i) * 30 + 100));
				window.draw(box);
			}
			box.setPosition(((y + 1) * 30 + 150), ((x + 1) * 30 + 100));
			window.draw(box);
		}
	};
	void  rotate(game& gr)
	{
		well a = gr.returnwell();
		int grid[20][10];
		int x = rf[0][0], y = rf[0][1];
		int c = 0, u = 0, d = 0, l = 0;
		bool f = 1;
		a.getgrid(grid);
		angle += 90;
		if (angle == 360)
			angle = 0;
		if (angle == 0)
		{
			for (int i = 2; i > 0; i--)
				if (y + i > 9 || grid[x][y + i] != 0)
					l = 3 - i;
			if (l == 1)
			{
				if (y - 1 < 0 || grid[x][y - 1] != 0)
					f = 0;
			}
			else if (l == 2)
				if (y - 2 < 0 || grid[x][y - 2] != 0 || grid[x][y - 1] != 0 || grid[x + 1][y - 1] != 0)
					f = 0;
			if (f == 0)
				angle = 270;
			else
			{
				rf[0][1] -= l;
			}
		}
		else if (angle == 90)
		{
			for (int i = 2; i > 0; i--)
				if (grid[x + i][y + 2] != 0 || x + i > 19)
					u = 3 - i;
			if (u == 1)
			{
				if (x - 1 < 0 || grid[x - 1][y + 2] != 0)
					f = 0;
			}
			else if (u == 2)
				if (x - 2 < 0 || grid[x - 2][y + 2] != 0 || grid[x - 1][y + 2] != 0 || grid[x - 1][y + 1] != 0)
					f = 0;
			if (f == 0)
				angle = 0;
			else
			{
				rf[0][0] -= u; rf[0][1] += 2;
			}
		}
		else if (angle == 180)
		{
			for (int i = 2; i > 0; i--)
				if (y - i < 0 || grid[x + 2][y - i] != 0)
					c = 3 - i;
			if (c == 1)
			{
				if (y + 1 > 9 || grid[x + 2][y + 1] != 0)
					f = 0;
			}
			else if (c == 2)
				if (y + 2 > 9 || grid[x + 2][y + 1] != 0 || grid[x + 1][y + 1] != 0 || grid[x + 2][y + 2] != 0)
					f = 0;
			if (f == 0)
				angle = 90;
			else
			{
				rf[0][0]++; rf[0][1] = rf[0][1] - 1 + c;
			}
		}
		else if (angle == 270)
		{
			for (int i = 1; i >= 0; i--)
				if (grid[x - i][y - 1] != 0 || x - i < 0)
					d = 2 - i;
			if (d == 1)
			{
				if (x + 2 > 19 || grid[x + 2][y - 1] != 0)
					f = 0;
			}
			else if (d == 2)
				if (x + 3 < 0 || grid[x + 2][y] != 0 || grid[x + 2][y - 1] != 0 || grid[x + 3][y - 1] != 0)
					f = 0;
			if (f == 0)
				angle = 180;
			else
			{
				rf[0][0] = rf[0][0] - 1 + d; rf[0][1]--;
			}
		}
	};
};
class Z : public tetrimino
{
public:
	Z() :tetrimino(0, 4)
	{

	};
	void reset()
	{
		rf[0][0] = 0;
		rf[0][1] = 4;
		angle = 0;
	};
	bool end_game(game& gr)
	{
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = 0, y = 4;
		if (grid[x][y] == 0 && grid[x][y + 1] == 0 && grid[x + 1][y + 1] == 0 && grid[x + 1][y + 2] == 0)
			return false;
		return true;
	};
	bool checker1(game& gr)
	{
		bool pos = 0;
		int c = 0;
		well a = gr.returnwell();
		int grid[20][10];
		int x = rf[0][0], y = rf[0][1];
		a.getgrid(grid);
		if (angle == 0 || angle == 180)
		{
			if (grid[x + 1][y] == 0 && grid[x + 2][y + 1] == 0 && grid[x + 2][y + 2] == 0)
				pos = 1;
		}
		else if (angle == 90 || angle == 270)
		{
			if (grid[x + 2][y] == 0 && grid[x + 3][y - 1] == 0)
				pos = 1;
		}
		return pos;
	};
	void indexes(int arr[4][2])
	{
		int x = rf[0][0], y = rf[0][1];
		if (angle == 0 || angle == 180)
		{
			arr[0][0] = x; arr[0][1] = y;
			arr[1][0] = x; arr[1][1] = y + 1;
			arr[2][0] = x + 1; arr[2][1] = y + 1;
			arr[3][0] = x + 1; arr[3][1] = y + 2;
		}
		else if (angle == 90 || angle == 270)
		{
			arr[0][0] = x; arr[0][1] = y;
			arr[1][0] = x + 1; arr[1][1] = y;
			arr[2][0] = x + 1; arr[2][1] = y - 1;
			arr[3][0] = x + 2; arr[3][1] = y - 1;
		}
	};
	void moveright(game& gr)
	{

		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = rf[0][0], y = rf[0][1];
		if (angle == 0 || angle == 180)
		{
			if (y < 7)
				if (grid[x][y + 2] == 0 && grid[x + 1][y + 3] == 0)
					rf[0][1]++;
		}
		else if (angle == 90 || angle == 270)
		{
			if (y < 9)
				if (grid[x][y + 1] == 0 && grid[x + 1][y + 1] == 0 && grid[x + 2][y] == 0)
					rf[0][1]++;
		}
	};
	void moveleft(game& gr)
	{
		well a = gr.returnwell();
		int grid[20][10];
		a.getgrid(grid);
		int x = rf[0][0], y = rf[0][1];
		if (angle == 0 || angle == 180)
		{
			if (y > 0)
				if (grid[x][y - 2] == 0 && grid[x + 1][y] == 0)
					rf[0][1]--;
		}
		else if (angle == 90 || angle == 270)
		{
			if (y > 1)
				if (grid[x][y - 1] == 0 && grid[x + 1][y - 2] == 0 && grid[x + 2][y - 2] == 0)
					rf[0][1]--;
		}
	};
	void draw(RenderWindow& window)
	{
		int x = rf[0][0], y = rf[0][1];
		Sprite box;
		Texture a;
		a.loadFromFile("Images/Z.png", IntRect(0, 0, 30, 30));
		box.setTexture(a);
		if (angle == 0 || angle == 180)
		{
			for (int i = 0; i < 2; i++)
			{
				box.setPosition(((y + i) * 30 + 150), (x * 30 + 100));
				window.draw(box);
			}
			for (int i = 1; i < 3; i++)
			{
				box.setPosition(((y + i) * 30 + 150), ((x + 1) * 30 + 100));
				window.draw(box);
			}
		}
		else if (angle == 90 || angle == 270)
		{
			for (int i = 0; i < 2; i++)
			{
				box.setPosition(((y) * 30 + 150), ((x + i) * 30 + 100));
				window.draw(box);
			}
			for (int i = 0; i < 2; i++)
			{
				box.setPosition(((y - 1) * 30 + 150), ((x + 1 + i) * 30 + 100));
				window.draw(box);
			}
		}
	};
	void  rotate(game& gr)
	{
		well a = gr.returnwell();
		int grid[20][10];
		int x = rf[0][0], y = rf[0][1];
		int l = 0, u = 0, d = 0;
		bool f = 1;
		a.getgrid(grid);
		angle += 90;
		if (angle == 360)
			angle = 0;
		if (angle == 0 || angle == 180)
		{
			for (int i = 1; i >= 0; i--)
				if (y + i > 9 || grid[x + 2][y + i] != 0)
					l = 2 - i;
			if (l == 1)
			{
				if (y - 2 < 0 || grid[x + 1][y - 2] != 0)
					f = 0;
			}
			else if (l == 2)
				if (y - 3 < 0 || grid[x + 1][y - 2] != 0 || grid[x + 1][y - 3] != 0 || grid[x + 2][y - 2] != 0)
					f = 0;
			if (f == 0)
			{
				angle -= 90;
				if (angle == -90)
					angle = 270;
			}
			else
			{
				rf[0][1] = rf[0][1] - 1 - l; rf[0][0]++;
			}
		}
		else if (angle == 90 || angle == 270)
		{
			if (x - 1 < 0 || grid[x - 1][y + 1] != 0)
				d = 1;
			if (grid[x + 1][y] != 0)
				u = 1;
			if (d == 1 && u == 0)
			{
				if (x + 2 > 19 || grid[x + 2][y] != 0)
					f = 0;
			}
			else if (d == 0 && u == 1)
			{
				if (x - 2 < 0 || grid[x - 2][y + 1] != 0 || grid[x - 1][y] != 0)
					f = 0;
			}
			else if (d == 1 && u == 1)
				f = 0;
			if (f == 0)
			{
				angle -= 90;
				if (angle == -90)
					angle = 270;
			}
			else
			{
				rf[0][0] = rf[0][0] - 1 - u + d; rf[0][1]++;
			}
		}
	};
};