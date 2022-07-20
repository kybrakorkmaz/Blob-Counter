#include<iostream>
#include<fstream>
#include<iomanip>
#define N 100
/*
* 
* @author Kubra Korkmaz 
* @date 20.07.2022
* 
*/
using namespace std;

float noOfRow;
float noOfCol;

void readFile();
void printShapes(char**, int*, int*);
void printTable(int*, int*, float &, float &);
void deleteArray(char**, int*);
int blobCount(char**, int, int);
void noOfShapes(char**, int*, int*);
void printLabel();
void printDownLine();

int main() {
	cout << endl << endl;
	readFile();	
	return 0;
}//end-main



void readFile() {
	ifstream inFile;
	char** grid;
	char c;
	int row, col;
	int i = 0, j = 0;

	//open file
	inFile.open("blobs1.txt");

	//check the file if open or not
	if (!inFile) {
		cout << "cannot open the file!\n";
	}
	//get row and col value from text file
	inFile >> row >> col;

	//allocate 2d array
	grid = new char* [N];
	for (int i = 0; i < N; i++) {
		grid[i] = new char[N];
	}
	//fill 2d dynamic array with wspace
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			grid[i][j]=' ';
		}
	}
	//move cursor to next line
	c = inFile.get();
	//get pixelst char by char and insert them to 2d array, including wspace
	for (i = 0; i < row; i++) {
		c = inFile.get();
		for (j = 0; j < col; j++) {
			if (c != '\n') {
				grid[i][j] = c;
				c = inFile.get();
			}									
		}		
	}
	//close file
	inFile.close();

	printShapes(grid, &row, &col);
	printLabel();
	noOfShapes(grid, &row, &col);
	printDownLine();
	deleteArray(grid, &row);
	//file close
	
	
}//end-readFile

int blobCount(char** grid, int r, int c) {
	if (r < 0 || r >= N || c < 0 || c >= N) { return 0; }
	else if (grid[r][c] != 'x') { return 0; }
	else {
		//sum of columns of shape
		noOfCol += c;
		//sum of rows of shape
		noOfRow += r;
		//visited pixel
		grid[r][c] = ' ';
		return(1 + blobCount(grid, r - 1, c) + blobCount(grid, r, c + 1)
			+ blobCount(grid, r, c - 1) + blobCount(grid, r + 1, c));			
	}	
}

void noOfShapes(char** grid, int* row, int* col) {
	float x = 0;
	float y = 0;
	int counter = 0, pixel = 0;
	for (int i = 0; i < *row; i++) {
		for (int j = 0; j < *col; j++) {
			if (grid[i][j] == 'x') {
				pixel=blobCount(grid, i, j);	
				//x coordinate mass of shape
				x = noOfRow / pixel;
				//y coordibate mass of shape
				y = noOfCol / pixel;
				//shape number
				counter++;
				printTable(&pixel, &counter, x, y);
				noOfCol = 0;
				noOfRow = 0;
			}
		}
	}
}
void printShapes(char** grid, int* row, int* col) {
	//up-horizontal coordinate numbers
	cout << "   ";
	for (int i = 0; i < *col; i++) { cout << i % 10; }
	cout << endl;
	//up-horizontal line
	cout << "  +";
	for (int i = 0; i < *col; i++) { cout << "-"; }
	cout << "+" << endl;
	//shapes
	for (int i = 0; i < *row; i++) {
		for (int j = 0; j < *col; j++) {
			//left-vertical coordinate numbers and line
			if (j == 0) { cout << " " << i % 10 << "|"; }
			cout << grid[i][j];
			//right-vertical coordinate numbers and line
			if (j == (*col - 1)) { cout << "|" << i % 10; }
		}
		cout << endl;
	}
	//dowm-horizontal line
	cout << "  +";
	for (int i = 0; i < *col; i++) { cout << "-"; }
	cout << "+" << endl;
	//down-horizontal coordinate numbers
	cout << "   ";
	for (int i = 0; i < *col; i++) { cout << i % 10; }
	cout << endl << endl << endl;

}
void printLabel() {
	cout << "+------+------------+---------+------------+" << endl;
	cout << "| BLOB | NoOfPixels | CoM Row | CoM Column |" << endl;
	cout << "+------+------------+---------+------------+" << endl;
}
void printTable(int* pixel, int* counter, float &x, float &y) {
	//6-12-9-13

	cout << "|" << setw(6) << *counter << "|" << setw(12) << *pixel
		<< "|" << setw(9) << fixed << setprecision(2) << x
		<< "|" << setw(12) << fixed << setprecision(2) << y << "|" << endl;
}
void printDownLine() {
	cout << "+------+------------+---------+------------+" << endl;
}
void deleteArray(char** grid, int* row) {
	for (int i = 0; i < *row; i++) { delete[]grid[i]; }
	delete[]grid;
	grid = NULL;
}