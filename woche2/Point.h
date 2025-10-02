#pragma once
#include <cmath>
#include <iostream>


// struct ist eine öffentliche Klasse
struct Point {
	int m_x, m_y; //public

	//const prevents changes of member variable inside of function (only read right)
	double dist(const Point &p) const {
		//m_x = 0; <- nicht erlaubt :D
		return hypot(this->m_x - p.m_x, this->m_y - p.m_y);
	}

	Point move(int dx, int dy) const {
		return Point{this->m_x + dx, this->m_y + dy};
	}

	//alternatively with chaining and not immutable:
	//Point& move(int dx, int dy {
	//m_x += dx; m_y += dy
	// return *this
	//}

	//friend is not an instance method of point but has access to private fields of Point
	//binary function allowing for method chaining: std::ostream&
	friend std::ostream &operator<<(std::ostream &os, const Point &p) {
		return os << "(" << p.m_x << ", " << p.m_y << ")";
	}
};
