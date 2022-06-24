#pragma once
#include <cmath>
#include <iostream>
#include "Segment.h"
#include <vector>
#include <algorithm>
using namespace std;

class GeometricFigure {
public:
	GeometricFigure() {}
	~GeometricFigure() {}
	float Area() {}
	float Perimeter() {}
};



class Triangle: public GeometricFigure {
public:
	Triangle(point a, point b, point c) {
		m_a = a;
		m_b = b;
		m_c = c;
	}

	float Area() {
		//cout << "Triangle area :" << endl;
		return 0.5 * fabs((m_b.x - m_a.x) * (m_c.y - m_a.y) - (m_c.x - m_a.x) * (m_b.y - m_a.y));
	}

	float Perimeter() {
		Segment a(m_a, m_b), b(m_a, m_c), c(m_b, m_c);
		//cout << "Triangle perimeter :" << endl;
		return (a.Length() + b.Length() + c.Length());
	}


private:
	point m_a, m_b, m_c;
};


class Polygon: public GeometricFigure {
public:

	Polygon(vector <point> &vec){
		m_vertex = vec;
	}

	float Area() {
		float s = 0;
		for (int i = 1; i <= m_vertex.size() - 2; i++) {
			Triangle a(m_vertex[0], m_vertex[i], m_vertex[i + 1]);
			cout << a.Area() << " ";
			s += a.Area();
		}
		return s;
	}
	
	float Perimeter() {
		float p = 0;
		for (int i = 0; i < m_vertex.size(); i++) {
			if (i != m_vertex.size() - 1) {
				Segment a(m_vertex[i], m_vertex[i + 1]);
				p += a.Length();
			}
			else {
				Segment a(m_vertex[i], m_vertex[0]);
				p += a.Length();
			}	
		}
		return p;
	}
	

	bool Point_Inside(point n) {
		float max = -100;
		for (int i = 0; i < m_vertex.size(); i++) 
			if (m_vertex[i].x > max)
				max = m_vertex[i].x;

		point m = { max + 10, n.y + 1 };
		Segment ray(n, m);
		int intersec = 0;
		for (int i = 0; i < m_vertex.size(); i++) {
			if (i != m_vertex.size() - 1) {
				Segment a(m_vertex[i], m_vertex[i + 1]);
				if (ray.Cross_B(a))
					intersec += 1;
				cout << intersec << endl;
			}
			else {
				Segment a(m_vertex[i], m_vertex[0]);
				if (ray.Cross_B(a))
					intersec += 1;
				cout << intersec << endl;
			}
		}
		if ((intersec % 2 == 0) || (intersec == 0))
			return 0;
		return 1;
	}

	bool Bump() {
		double b = 0;
		for (int i = 0; i <= m_vertex.size() - 2; i++) {
			if (i != m_vertex.size() - 2) {
				cout << i << ":  " << SGN(m_vertex[i], m_vertex[i + 1], m_vertex[i + 2]) << endl;
				b += SGN(m_vertex[i], m_vertex[i + 1], m_vertex[i + 2]);
			}
			else {
				cout << i << ":  " << SGN(m_vertex[i], m_vertex[i + 1], m_vertex[0]) << endl;
				b += SGN(m_vertex[i], m_vertex[i + 1], m_vertex[0]);
			}
		}
		if (fabs(b) == m_vertex.size() - 1)
			return true;

		return false;
	}

	int Graham(double D_x[], double D_y[], int n, double* C_x, double* C_y) {
		double angle[2020], di[2020];
		double min_x = INT_MAX;
		double min_y = INT_MAX;
		int min_i = INT_MAX;
		for (int i = 0; i < n; i++) {
			if (D_x[i] < min_x) { min_x = D_x[i]; min_y = D_y[i]; min_i = i; }
			if (D_x[i] == min_x) { min_x = D_x[i]; min_y = D_y[i]; min_i = i; }
		}
		swap(D_x[0], D_x[min_i]);
		swap(D_y[0], D_y[min_i]);
		for (int i = 0; i < n; i++) {
			if (D_x[i] - D_x[0] == 0) angle[i] = INT_MAX;
			else angle[i] = (D_y[i] - D_y[0]) / (D_x[i] - D_x[0]);
			point a = { D_x[i], D_y[i] }, b = { D_x[0], D_y[0] };
			Segment M(a, b);
			di[i] = M.Length();
		}
	}


private:
	vector <point> m_vertex;

	double SGN(point a, point b, point c) { // ���� ��������������� �������.
		float check = (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
		if (check > 0) return 1;
		if (check < 0) return -1;
		return 0;
	}
};
