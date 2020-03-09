#pragma once
#include <string>
#include <iostream>
#include <unordered_set>
#include <cmath>
#include "Line.h"

using namespace std;

unordered_set<string> nodes;

class Circle {
public:
	double x;	// 圆心x坐标
	double y;	// 圆心y坐标
	double r;	// 半径

	Circle(double x, double y, double r) {
		this->x = x;
		this->y = y;
		this->r = r;
	}

	double trans(double ans) {
		return abs(ans) < 1e-10 ? 0.0 : ans;
	}

	void intersect_C(Circle otherCircle) {
		double center_d = sqrt((x - otherCircle.x) * (x - otherCircle.x)
			+ (y - otherCircle.y) * (y - otherCircle.y));
		if (center_d != 0) {
			double a = (r * r - otherCircle.r * otherCircle.r + center_d * center_d) / (2 * center_d);
			double x0 = x + a / center_d * (otherCircle.x - x);
			double y0 = y + a / center_d * (otherCircle.y - y);
			if ((center_d == r + otherCircle.r) || (center_d == abs(r - otherCircle.r))) {
				nodes.insert(to_string(trans(x0)) + "," + to_string(trans(y0)));
			}
			else if ((center_d > abs(r - otherCircle.r)) && (center_d < r + otherCircle.r)) {
				double h = sqrt(r * r - a * a);
				double x1 = x0 - h / center_d * (otherCircle.y - y);
				double y1 = y0 + h / center_d * (otherCircle.x - x);
				double x2 = x0 + h / center_d * (otherCircle.y - y);
				double y2 = y0 - h / center_d * (otherCircle.x - x);
				nodes.insert(to_string(trans(x1)) + "," + to_string(trans(y1)));
				nodes.insert(to_string(trans(x2)) + "," + to_string(trans(y2)));
			}
		}
	}

	void intersect_L(Line line) {
		if (line.k == INFINITY) {
			double d = abs(line.b - x);
			if (d < r) {
				double offset = sqrt(r * r - d * d);
				double y1 = y + offset;
				double y2 = y - offset;
				nodes.insert(to_string(line.b) + "," + to_string(trans(y1)));
				nodes.insert(to_string(line.b) + "," + to_string(trans(y2)));
			}
			else if (d == r) {
				nodes.insert(to_string(line.b) + "," + to_string(y));
			}
		}
		else {
			double c = -x, d = -y, k = line.k, b = line.b;
			double delta = k * k * r * r + r * r - c * c * k * k + 2 * c * d * k +
				2 * b * c * k - d * d - 2 * b * d - b * b;
			if (delta > 0) {
				delta = sqrt(delta);
				double x1 = -((delta + k * d + k * b + c) / (k * k + 1));
				double y1 = -((k * delta + k * c + d * k * k - b) / (k * k + 1));
				double x2 = (delta - k * d - k * b - c) / (k * k + 1);
				double y2 = -((-k * delta + k * c + d * k * k - b) / (k * k + 1));
				nodes.insert(to_string(trans(x1)) + "," + to_string(trans(y1)));
				nodes.insert(to_string(trans(x2)) + "," + to_string(trans(y2)));
			}
			else if (delta == 0) {
				double x1 = (-k * d - k * b - c) / (k * k + 1);
				double y1 = (b - d * k * k - k * c) / (k * k + 1);
				nodes.insert(to_string(trans(x1)) + "," + to_string(trans(y1)));
			}
		}
	}
};