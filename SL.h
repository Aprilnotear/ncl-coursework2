void saveMaze(const char a[][M]);
void loadMaze();

void saveMaze(const char a[][M]) {

	ofstream outFile;
	char filename[10];
	cout << "Please input the name of file: ";
	cin.get();
	cin.getline(filename, 10);
	outFile.open(filename);

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++)
			outFile << a[i][j];
		outFile << endl;
	}

	outFile.close();

	cout << "Saving successfully. \n";
}

void loadMaze() {
	char a[M][M];
	cin.get();
	char fname[10];
	cout << "Please input the filename needs to open: ";
	cin.getline(fname, 10);

	ifstream infile;
	infile.open(fname);

	while (!infile.is_open()) {
		cout << "Could not find the txt file " << fname << endl;
		cout << "Please input correct file name again: ";
		cin.getline(fname, 10);
		infile.open(fname);
	}
	system("cls");
	
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			infile.get(a[i][j]);
			cout << a[i][j];
		}
	}
	infile.close();
	cout << endl;
}