#pragma once
#include <cmath>
#include <iostream>


// struct ist eine öffentliche Klasse
struct Point {
	int m_x, m_y; //public

	// Ohne explixit, wird der Compiler versuchen, einen Ausdruck in einen Point zu konvertieren
	Point(int x = 0, int y = 0) : m_x(x), m_y(y){}

	// automatischer generierter Operator
	// lexiokografische Ordnung der Instanzvariablen
	// alle statement Operatoren abgedeckt (< == <= etc.)
	auto operator<=>(const Point &) const = default;


	// // Java's equals() methode
	// bool operator==(const Point& p) const {
	// 	return m_x == p.m_x && m_y == p.m_y;
	// }
	//
	// bool operator<(const Point& p) const {
	// 	// lexikografische Ordnung
	// 	if (m_x == p.m_x) {
	// 		return m_y < p.m_y;
	// 	}
	//
	// 	return m_x < p.m_x;
	// }

	// veränder this nicht
	Point operator-() const {
		return Point(-m_x, -m_y);
	}

	// Instanzmethode
	Point& operator+=(const Point& p) {
		this->m_x += p.m_x;
		this->m_y += p.m_y;
		return *this;
	}

	friend Point operator+(Point&& lhs, const Point& rhs) {
		return lhs += rhs;
	}

	// freie Methode
	// keine Instanzmethode!
	friend Point operator+(Point lhs, const Point& rhs) {
		return lhs += rhs;
	}

	// // Überladung von + Operator
	// // const Point& p und const this
	// Point operator+(const Point& p) const {
	// 	Point result(*this);
	// 	result.m_x += p.m_x;
	// 	result.m_y += p.m_y;
	// 	return result;
	// }

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
