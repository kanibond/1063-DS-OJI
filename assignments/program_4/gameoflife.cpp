/**
* @ProgramName: Game of Life
* @Author: Kanayo oji
* @Description:
*   This program uses a 2d array to implement the game of life.
* @Course: 1063 Data Structures
* @Semester: Spring 2017
* @Date: 28 April 2017
*/
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

class GameOfLife
{
private:
	int **Board;
	int **Board2;
	int **Board3;
	int Rows;
	int Cols;
public:
	GameOfLife(string filename)
	{
		string line;
		char ch;
		ifstream fin;
		fin.open(filename);
		fin >> Rows >> Cols;
		InitBoardArray(Board);
		InitBoardArray(Board2);
		InitBoardArray(Board3);
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				fin.get(ch);
				if (ch == 10)
				{
					continue;
				}
				Board[i][j] = int(ch) - 48;
			}
		}
	}

	GameOfLife(int r, int c){
		Rows = r;
		Cols = c;
		InitBoardArray(Board);
		InitBoardArray(Board2);
		PrintBoard();
	}

	void InitBoardArray(int **&b)
	{
		b = new int*[Rows];
		for (int i = 0; i < Rows; i++)
		{
			b[i] = new int[Cols];
		}
		ResetBoardArray(b);
	}

	void ResetBoardArray(int **&b)
	{
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				b[i][j] = 0;
			}
		}
	}

	void PrintBoard()
	{
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				if (Board[i][j] == 1)
					cout << char('X');
				else
					cout << " ";
			}
			cout << endl;
		}
	}

	int CountNeighbors(int row, int col)
	{
		int neighbors = 0;

		if (Board[(row + 1) % Rows][col] == 1)
			neighbors++;

		if (Board[(row + Rows - 1) % Rows][col] == 1)
			neighbors++;

		if (Board[(row + 1) % Rows][(col + 1) % Cols] == 1)
			neighbors++;

		if (Board[(row + 1) % Rows][(col + Cols - 1) % Cols] == 1)
			neighbors++;

		if (Board[(row + Rows - 1) % Rows][(col + 1) % Cols] == 1)
			neighbors++;

		if (Board[(row + Rows - 1) % Rows][(col + Cols - 1) % Cols] == 1)
			neighbors++;

		if (Board[row][(col + 1) % Cols] == 1)
			neighbors++;

		if (Board[row][(col + Cols - 1) % Cols] == 1)
			neighbors++;

		return neighbors;
	}

	bool OnBoard(int row, int col)
	{
		return (row >= 0 && row < Rows && col >= 0 && col < Cols);
	}

	void RandomPopulate(int num)
	{
		int r = 0;
		int c = 0;
		for (int i = 0; i < num; i++)
		{
			r = rand() % Rows;
			c = rand() % Cols;
			Board[r][c] = 1;
		}
	}

	void SetCell(int r, int c, int val)
	{
		Board[r][c] = val;
	}

	void AddGens()
	{
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				Board[i][j] += Board2[i][j];
			}
		}
		ResetBoardArray(Board2);
	}

	void clear_screen(int lines)
	{
		for (int i = 0; i < lines; i++)
		{
			cout << endl;
		}
	}

	void Run(int generations = 99999){
		int neighbors = 0;
		int g = 0;
		int stable = 0;
		bool check = true;
		PrintBoard();
		while (g < generations&&stable != 2){
			for (int i = 0; i < Rows; i++){
				for (int j = 0; j < Cols; j++){
					// cout<<"on spot "<<i<<","<<j<<endl;
					if (((i == 0 && j == 0) || (i == Rows - 1 && j == 0) || (i == Rows - 1 && j == Cols - 1) || (i == 0 && j == Cols - 1)) && Board[i][j] == 1)
					{
						Board2[i][j] = -1;
						check = false;
					}
					else
					{
						neighbors = CountNeighbors(i, j);
						if (Board[i][j] == 1 && (neighbors < 2 || neighbors > 3)){
							Board2[i][j] = -1;
							check = false;
						}
						else if (Board[i][j] == 0 && neighbors == 3){
							Board2[i][j] = 1;
							check = false;
						}
					}
				}
			}
			if (check == true)
				stable++;
			else{
				stable = 0;
				check = true;
			}
			AddGens();
			Sleep(500);
			clear_screen(30);
			PrintBoard();
			g++;
		}
	};


	bool Corner(int r, int c)
	{
		if (r == 0 && c == 0)
			return true;
		if (r == 0 && c == Cols - 1)
			return true;
		if (r == Rows - 1 && c == 0)
			return true;
		if (r == Rows - 1 && c == Cols - 1)
			return true;

		return false;
	}

	void GliderGun()
	{
		if (Rows>10 && Cols>37)
		{
			ResetBoardArray(Board);
			SetCell(1, 25, 1);
			SetCell(2, 25, 1);    //right 
			SetCell(6, 25, 1);
			SetCell(7, 25, 1);
			SetCell(2, 23, 1);
			SetCell(6, 23, 1);
			SetCell(3, 22, 1);
			SetCell(3, 21, 1);
			SetCell(4, 22, 1);
			SetCell(4, 21, 1);
			SetCell(5, 22, 1);
			SetCell(5, 21, 1);

			SetCell(6, 18, 1);
			SetCell(6, 17, 1);    //left 
			SetCell(5, 17, 1);
			SetCell(7, 17, 1);
			SetCell(4, 16, 1);
			SetCell(8, 16, 1);
			SetCell(6, 15, 1);
			SetCell(3, 14, 1);
			SetCell(3, 13, 1);
			SetCell(4, 12, 1);
			SetCell(5, 11, 1);
			SetCell(6, 11, 1);
			SetCell(7, 11, 1);
			SetCell(8, 12, 1);
			SetCell(9, 13, 1);
			SetCell(9, 14, 1);

			SetCell(5, 1, 1);
			SetCell(5, 2, 1);   //left box
			SetCell(6, 1, 1);
			SetCell(6, 2, 1);

			SetCell(3, 35, 1);
			SetCell(3, 36, 1);  //right box
			SetCell(4, 35, 1);
			SetCell(4, 36, 1);
		}
		return;
	}


	/**
	* @FunctionName: copy
	* @Description:
	*     Copies a board to another 2d array
	* @Params:
	*    None
	* @Returns:
	*    void
	*/
	void copy()
	{
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				Board3[i][j] = Board[i][j];
			}
		}
	}

	/**
	* @FunctionName: sameItems
	* @Description:
	*     Counts the amount of same values from 2 seperate boards
	* @Params:
	*     None
	* @Returns:
	*    int - Number of same values
	*/
	int sameItems()
	{
		int n = 0;
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				if (Board3[i][j] == Board[i][j])
					n++;
			}

		}
		return n;
	}

	/**
	* @FunctionName: Stable
	* @Description:
	*     determines if the same number of items on 2 seperate boards
	*	  is equivalent to the area
	* @Params:
	*     None
	* @Returns:
	*    bool - true if every item is the same / false otherwise
	*/
	bool Stable()
	{
		int area = Rows * Cols;
		return (sameItems() == area);
	}
};


int main()
{
	int x = 0;
	GameOfLife B("gen_one.txt");
	GameOfLife C(26, 40);
	C.GliderGun();
	while (x != 3)
	{
		cout << " Press 1 to run gen_one.txt " << endl;
		cout << " 2 for glider gun " << endl; 
		cout << " and 3 to quit" << endl;
		cin >> x;
		if (x == 1)
		{
			B.Run(100);
		}
		else if (x == 2)
		{
			C.Run(100);
		}
	}
	return 0;
}

