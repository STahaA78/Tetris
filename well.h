#include<iostream>
#include<Windows.h>
using namespace std;
class well
{
private:
	int grid[20][10];
public:
	well()
	{
		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 10; j++)
				grid[i][j] = 0;
	};
	void getgrid(int arr[20][10])
	{
		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 10; j++)
				arr[i][j] = grid[i][j];
	};
	void setgrid(int arr[20][10])
	{
		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 10; j++)
				grid[i][j] = arr[i][j];
	}
	int horizontallinechecker()
	{
		//found keeps track of number of complete lines
		//c counts the non zero elements of a row
		int found = 0,c;
		for (int i = 19; i >= 0; i--)
		{
			c = 0;
			//detection
			for (int j = 0; j < 10; j++)
				if (grid[i][j] != 0)
					c++;
			if (c == 10)
			{
				//Sleep(500);
				found++;
				//deletion of complete row
				for (int j = 0; j < 10; j++)
					grid[i][j] = 0;
				//swapping
				for (int k = i; k >= 1; k--)
					for (int j = 0; j < 10; j++)
						swap(grid[k][j], grid[k - 1][j]);
				i++;
			}
		}
		return found;
	};
};
