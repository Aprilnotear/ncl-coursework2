#define M 30

int m_size, current_x, current_y;
int m[M][M];                                //digital maze             (0:'X'    3:'E'     5:' '    6:'P'   9:'F')
int m2[M][M];                               //backup created maze
char a[M][M];                               //ASCII maze

using namespace std;

void init(int num);
bool neighbour(int px, int py);
void alg_createMaze(int px, int py);
void draw(int maze[][M]);
void generate_entrance(int n);

void init(int num) {
	m[M][M] = { 0 };
	m2[M][M] = { 0 };
	if (num % 2 == 0)
		m_size = num + 1;
	else m_size = num;

	//initialize
	for (int i = 0; i < m_size; i++)
		for (int j = 0; j < m_size; j++)
			m[i][j] = 0;

	for (int i = 0; i < M; i++)
		for (int j = 0; j < M; j++) {
			if (i >= m_size || j >= m_size)
				m[i][j] = -1;
			else if (i % 2 == 1 && j % 2 == 1)
				m[i][j] = 1;
		}

	alg_createMaze(1, 1);

	//set centre space
	int inner = m_size / 2;
	m[inner][inner] = 9;
	m[inner + 1][inner] = 5;
	m[inner - 1][inner] = 5;
	m[inner][inner + 1] = 5;
	m[inner][inner - 1] = 5;
	m[inner + 1][inner + 1] = 5;
	m[inner + 1][inner - 1] = 5;
	m[inner - 1][inner + 1] = 5;
	m[inner - 1][inner - 1] = 5;
}

bool neighbour(int px, int py) {
	if (px >= 3 && m[px - 2][py] == 1
		|| px < m_size - 3 && m[px + 2][py] == 1
		|| py >= 3 && m[px][py - 2] == 1
		|| py < m_size - 3 && m[px][py + 2] == 1)
		return true;
	else return false;
}

void alg_createMaze(int px, int py) {
	int r_direction = 0;
	while (1) {
		if (!neighbour(px, py))
			return;
		else {
			m[px][py] = 5;
			while (1) {
				r_direction = rand() % 4;
				if (r_direction == 0 && px >= 3 && m[px - 2][py] == 1) {
					m[px - 2][py] = 5;
					m[px - 1][py] = 5;
					px -= 2;
				}
				else if (r_direction == 1 && px < m_size - 3 && m[px + 2][py] == 1) {
					m[px + 2][py] = 5;
					m[px + 1][py] = 5;
					px += 2;
				}
				else if (r_direction == 2 && py >= 3 && m[px][py - 2] == 1) {
					m[px][py - 2] = 5;
					m[px][py - 1] = 5;
					py -= 2;
				}
				else if (r_direction == 3 && py < m_size - 3 && m[px][py + 2] == 1) {
					m[px][py + 2] = 5;
					m[px][py + 1] = 5;
					py += 2;
				}
				alg_createMaze(px, py);
				break;
			}
		}
	}
}

void draw(int maze[][M]) {                           //draw ASCII maze
	for (int i = 0; i < M; i++)
		for (int j = 0; j < M; j++) {
			if (maze[i][j] == 0)
				a[i][j] = 'X';
			else if (maze[i][j] == 5)
				a[i][j] = ' ';
			else if (maze[i][j] == 6)
				a[i][j] = 'P';
			else if (maze[i][j] == 3)
				a[i][j] = 'E';
			else if (maze[i][j] == 9)
				a[i][j] = 'F';
		}

	for (int i = 0; i < m_size; i++) {
		for (int j = 0; j < m_size; j++)
			cout << a[i][j];
		cout << endl;
	}
}

void generate_entrance(int n) {
	int a, b, i = 0;
	while (i < n) {
		a = rand() % m_size;
		b = rand() % 4;
		if (b == 0 && m[a][1] != 0) {
			m[a][0] = 3;
			i++;
		}
		else if (b == 1 && m[a][m_size - 2] != 0) {
			m[a][m_size - 1] = 3;
			i++;
		}
		else if (b == 2 && m[1][a] != 0) {
			m[0][a] = 3;
			i++;
		}
		else if (b == 3 && m[m_size - 2][a] != 0) {
			m[m_size - 1][a] = 3;
			i++;
		}
		else continue;
	}
}


