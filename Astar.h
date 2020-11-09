using namespace std;

struct Point {
	int x;
	int y;
	int f;
	int g;
	int h;
	bool isReach = false;
};

struct Maze_c {
	int  val;
	bool  isWalked;
};

struct tree {
	Point p = { 0 };
	tree* parent;
	vector<tree*> child;
};


bool canWalk(Point p, Maze_c** m);
int getH(Point begin, Point end);
vector<Point> algA(Point begin, Point end, int m[][M]);

vector<Point> algA(Point begin, Point end, int m[][M]) {
	Maze_c** m_c = new Maze_c * [M];
	for (int i = 0; i < M; i++)
		m_c[i] = new Maze_c[M];
	for (int i = 0; i < M; i++)
		for (int j = 0; j < M; j++) {
			m_c[i][j].val = 0;
			m_c[i][j].isWalked = 0;
		}
	for (int i = 0; i < M; i++)
		for (int j = 0; j < M; j++) {
			if (m[i][j] == -1)
				m_c[i][j].isWalked = 0;
			else {
				m_c[i][j].val = m[i][j];
				m_c[i][j].isWalked = m[i][j];
			}
		}
	m_c[begin.x][begin.y].isWalked = 0;

	tree* root = NULL;
	root = new tree;
	memset(root, 0, sizeof tree);
	root->p = begin;

	vector<tree*> li;

	tree* temp = root;

	bool reachEnd = false;
	vector<Point> route;                                //save the coordinates searched by A*

	if (begin.x == end.x && begin.y == end.y)
		reachEnd = true;
	else {
		while (1) {
			for (int i = 0; i < 4; i++) {
				tree* t_child = new tree;
				t_child->p = temp->p;
				switch (i)
				{
				case 0:
					t_child->p.x--;
					t_child->p.g++;
					break;
				case 1:
					t_child->p.x++;
					t_child->p.g++;
					break;
				case 2:
					t_child->p.y--;
					t_child->p.g++;
					break;
				case 3:
					t_child->p.y++;
					t_child->p.g++;
					break;
				}
				if (canWalk(t_child->p, m_c)) {
					t_child->p.h = getH(t_child->p, end);
					t_child->p.f = t_child->p.h + t_child->p.g;
					temp->child.push_back(t_child);
					t_child->parent = temp;
					li.push_back(t_child);
				}
			}
			auto li_min = li.begin();

			for (auto li_1 = li.begin(); li_1 != li.end() - 1; li_1++) {
				if ((*li_min)->p.f > (*li_1)->p.f)
					li_min = li_1;
			}

			m_c[(*li_min)->p.x][(*li_min)->p.y].isWalked = 0;
			temp = *li_min;

			li.erase(li_min);

			if (temp->p.x == end.x && temp->p.y == end.y) {
				reachEnd = true;
				break;
			}

		}
	}

	if (reachEnd == true) {
		if (begin.x == end.x && begin.y == end.y) {                  //the players who have reached the final target
			route.push_back(end);
			draw(m);
		}
		else {
			while (temp != NULL) {
				Point d = { temp->p.x,temp->p.y };
				route.push_back(d);
				temp = temp->parent;
			}
		}
	}
	return route;
}

bool canWalk(Point p, Maze_c** m) {
	if (p.x < 0 || p.x>M || p.y < 0 || p.y>M)return false;
	if (m[p.x][p.y].val == 0) return false;
	if (m[p.x][p.y].isWalked == 0)return false;
	return true;
}

int getH(Point begin, Point end) {
	int h = abs(begin.x - end.x) + abs(begin.y - end.y);
	return h;
}

