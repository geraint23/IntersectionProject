#include <iostream>
#include <vector>
#include <fstream>
#include<iomanip>
#include "Circle.h"

using namespace std;

void error() {
	cerr << "Wrong format!" << endl;
	exit(1);
}

int main(int argc, char* argv[]) {
	ifstream in;
	ofstream out;
	vector<Line> lines;
	vector<Circle> circles;
	char type;
	int N;
	for (int i = 0; i <= argc - 1; i++) {
		if (strcmp(argv[i], "-i") == 0) {
			in.open(argv[i + 1]);
		}
		else if (strcmp(argv[i], "-o") == 0) {
			out.open(argv[i + 1]);
		}
	}
	in >> N;
	while (N--) {
		in >> type;
		if (type == 'L') {
			double x1, y1, x2, y2;
			in >> x1 >> y1 >> x2 >> y2;
			if (!in) {
				error();
			}
			lines.push_back(Line(x1, y1, x2, y2));
		}
		else if (type == 'C') {
			double x, y, r;
			in >> x >> y >> r;
			if (!in) {
				error();
			}
			circles.push_back(Circle(x, y, r));
		}
		else {
			error();
		}
	}
	string node;
	int lineSize = (int)lines.size();
	int circleSize = (int)circles.size();
	/*for (auto it : lines) {
		cout << "k: " << it.k << endl;
		cout << "b: " << it.b << endl;
	}*/
	for (N = 0; N <= lineSize - 2; N++) {
		for (int i = N + 1; i <= lineSize - 1; i++) {
			lines[N].intersect_L(lines[i]);
		}
	}
	for (N = 0; N <= circleSize - 2; N++) {
		for (int i = N + 1; i <= circleSize - 1; i++) {
			circles[N].intersect_C(circles[i]);
		}
	}
	for (N = 0; N <= circleSize - 1; N++) {
		for (int i = 0; i <= lineSize - 1; i++) {
			circles[N].intersect_L(lines[i]);
		}
	}
	/*cout << "All nodes:" << endl;
	for (auto it : nodes) {
		cout << it.x << "," << it.y << endl;
	}*/
	out << nodes.size() << endl;
	in.close();
	out.close();
	return 0;
}