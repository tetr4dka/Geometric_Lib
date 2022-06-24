#include <iostream>
#include "Segment.h"
#include "Figure.h"

using namespace std;

void Vertexes(vector <point> &vec) { // Заполнение вектора точек для многоугольника
	cout << "Enter number of vertexes: " << endl;
	int n;
	cin >> n;
	if (n > 3)
		for (int i = 0; i < n; i++) {
			point a;
			cout << "Enter " << i + 1 << " point coordinates" << endl;
			cin >> a.x >> a.y;
			vec.push_back(a);
		}
	else
		cout << "Wrong number of vertexes" << endl;
}



int main() {

	/*point a, b;
	cin >> a.x >> a.y >> b.x >> b.y;
	point c, d;
	cin >> c.x >> c.y >> d.x >> d.y;

	point p;
	p.x = 0;
	p.y = 0;

	Segment n(a, b);
	Segment m(c, d);
	cout << n.Length() << " " << m.Length() << endl;

	m.Cross(n, m, p);*/



	vector <point> vec;
	Vertexes(vec);

	Polygon pol(vec);
	
	
	point a;
	cin >> a.x >> a.y;
	
	cout << "PI " << pol.Point_Inside(a) << endl;
	


	/*point a, b;
	cin >> a.x >> a.y >> b.x >> b.y;
	point c, d;
	cin >> c.x >> c.y >> d.x >> d.y;

	point x = { 0,0 };


	Segment l(a, b);
	Segment m(c, d);
	cout << l.Cross(l, m, x) << endl;
	cout << l.Cross_B(l, m) << endl;*/

}