#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "../intersect/Circle.h"

using namespace std;

#define random(a, b) (rand() % (b - a + 1)) + a

int random_para() {
	return random(-9999, 9999);
}

int main() {
	srand((int)time(NULL));
	int type;
	int N;
	vector<Line> lines;
	vector<Circle> circles;
	cin >> N;
	while (N--) {
		type = random(0, 1);
		if (type == 0) {
			lines.push_back(Line(random_para(), random_para(),random_para(), random_para()));
		}
		else if (type == 1) {
			circles.push_back(Circle(random_para(), random_para(), random_para()));
		}
	}
	string node;
	int lineSize = lines.size();
	int circleSize = circles.size();
	for (N = 0; N <= lineSize - 2; N++) {
		for (int i = N + 1; i <= lineSize - 1; i++) {
			node = lines[N].intersect_L(lines[i]);
			if (node != "not_exist") {
				nodes.insert(node);
			}
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
	cout << nodes.size() << endl;
	return 0;
}