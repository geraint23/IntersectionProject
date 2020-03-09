#pragma once
#include <string>
#include <iostream>

using namespace std;

class Line {
public:
	double k;	// 斜率
	double b;	// 截距

	Line(double x1, double y1, double x2, double y2) {	// 斜率存在时b是截距，不存在时b是x坐标
		if (x1 == x2) {
			k = INFINITY;
			b = x1;
		}
		else {
			k = (y2 - y1) / (x2 - x1);
			b = y1 - k * x1;
		}
	}

	double trans(double ans) {
		return abs(ans) < 1e-10 ? 0.0 : ans;
	}

	string intersect_L(Line otherLine) {
		double x, y;
		if (k == otherLine.k) {
			return "not_exist";
		}
		else if (k == INFINITY) {
			x = b;
			y = otherLine.k * x + otherLine.b;
		}
		else if (otherLine.k == INFINITY) {
			x = otherLine.b;
			y = k * x + b;
		}
		else {
			x = (otherLine.b - b) / (k - otherLine.k);
			y = k * x + b;
		}
		return to_string(trans(x)) + "," + to_string(trans(y));
	}
};