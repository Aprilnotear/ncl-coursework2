#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <vector>
#include <fstream>
#include "function.h"
#include "Astar.h"
#include "SL.h"

vector<Point> current_point(int** m);
int **progress(vector<Point> p, int m_backup[][M], Point end, int m[][M]);
bool Allreach(int m[][M]);
void startplay(int m[][M]);
void function(int m[][M], int entrance, int size);
void menu();

using namespace std;

int main() {
	srand((unsigned)time(NULL));
	menu();
}

vector<Point> current_point(int** m) {
	vector<Point> c_point;
	for (int i = 0; i < M; i++)
		for (int j = 0; j < M; j++) {
			if (m[i][j] == 6) {
				Point a = { i,j };
				c_point.push_back(a);
			}
		}
	return c_point;
}

int **progress(vector<Point> p, int m_backup[][M], Point end, int m[][M]) {                  //show current progress of all players
	int** maze = new int* [M];
	for (int i = 0; i < M; i++)
		maze[i] = new int[M];
	for (int i = 0; i < M; i++)
		for (int j = 0; j < M; j++) {
			maze[i][j] = m_backup[i][j];
		}

	for (int i = 0; i < p.size(); i++) {
		if (p[i].x == end.x && p[i].y == end.y)
			maze[p[i].x][p[i].y] = 9;
		else
			maze[p[i].x][p[i].y] = 6;
	}
	return maze;
}



void function(int m[][M], int entrance, int size) {
	Point p_e = { size / 2, size / 2 };
	int** maze = new int* [M];
	for (int i = 0; i < M; i++)
		maze[i] = new int[M];
	for (int i = 0; i < M; i++)
		for (int j = 0; j < M; j++)
			maze[i][j] = m[i][j];

	char ch;
	cout << "Command(s:Save Enter:Continue)\n";
	cin.get(ch);
	while (ch) {
		if (ch == 's') {
			saveMaze(a);
			cout << "Command(s:Save Enter:Continue)\n";
			cin.get(ch);
			continue;
		}
		else if (ch == '\n') {
			vector<Point> entrance_p;
			entrance_p = current_point(maze);
			vector<Point> point;
			for (int i = 0; i < entrance; i++) {
				Point p_b = { entrance_p[i].x,entrance_p[i].y };
				vector<Point> r = algA(p_b, p_e, m);
				if ((r.size() == 1))
					point.push_back(r[0]);
				else point.push_back(r[r.size() - 2]);
			}
			for (int i = 0, j = 0; i < point.size(), j < point.size(); i++, j++) {
				cout << "\nP" << j << " move to (" << point[i].x << ", " << point[i].y << ") ";
				if (point[i].x == p_e.x && point[i].y == p_e.y)
					entrance--;
			}
			cout << endl;
			maze = progress(point, m2, p_e, m);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < M; j++)
					m[i][j] = maze[i][j];
			if (!Allreach(m)) {
				draw(m);
				cin.get(ch);
				continue;
			}
			else {
				cout << "All the player reach the final target!\n";
				draw(m);
				break;
			}
			break;
		}
	}
}

bool Allreach(int m[][M]) {
	for(int i=0;i<M;i++)
		for (int j = 0; j < M; j++) {
			if (m[i][j] == 6)
				return false;
		}
	return true;
}

void startplay(int m[][M]) {
	for (int i = 0; i < M; i++)
		for (int j = 0; j < M; j++) {
			if (m[i][j] == 3)
				m[i][j] = 6;
		}
}


void menu() {
	int size, entrance;
	char cmd_menu;
	while (1) {
		cout << "Please input the command(s:Start game l:Load q:Quit) :";
		cin >> cmd_menu;
		if (cmd_menu == 's') {
			cout << "Please input the size of maze: ";
			cin >> size;
			cout << "Please input the number of player: ";
			cin >> entrance;
			init(size);
			generate_entrance(entrance);
			for (int i = 0; i < M; i++)
				for (int j = 0; j < M; j++)
					m2[i][j] = m[i][j];
			draw(m);
			startplay(m);
			function(m, entrance, size);
			char cmd_s;
			cout << "Press any key return to menu.";
			cmd_s=_getch();
			system("cls");
			continue;
		}
		else if (cmd_menu == 'l') {
			loadMaze();
			char cmd_l;
			cout << "Press any key return to menu.";
			cmd_l = _getch();
			system("cls");
			continue;
		}
		else if (cmd_menu == 'q') {
			cout << "Quit the game.";
			break;
		}
		else {
			cout << "Wrong input, please try again: ";
			continue;
		}
	}
}