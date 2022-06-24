#pragma once
#include <cmath>

using namespace std;

struct point {
    float x;
    float y;
};

class Segment {
public:
    Segment(point a, point b) {
        m_a = a;
        m_b = b;
    }

    ~Segment() {}

    float Length() { return sqrt(pow(m_a.x - m_b.x, 2) + pow(m_a.y - m_b.y, 2)); }

    void setPoint(point a, point b) { 
        m_a = a;
        m_b = b;
    }

    bool intersect_1(float a, float b, float c, float d) {
        if (a > b)  swap(a, b);
        if (c > d)  swap(c, d);
        return max(a, c) <= min(b, d);
    }

    bool Cross_B(Segment n) {
        return intersect_1(m_a.x, m_b.x, n.m_a.x, n.m_b.x)
            && intersect_1(m_a.y, m_b.y, n.m_a.y, n.m_b.y)
            && SGN(m_a, m_b, n.m_a) * SGN(m_a, m_b, n.m_b) <= 0
            && SGN(n.m_a, n.m_b, m_a) * SGN(n.m_a, n.m_b, m_b) <= 0;
    }

    bool Cross(Segment n, Segment m, point c) {
        float k;
        if (n.m_b.y - n.m_a.y != 0) {  
            float q = (n.m_b.x - n.m_a.x) / (n.m_a.y - n.m_b.y);
            float sk = (m.m_a.x - m.m_b.x) + (m.m_a.y - m.m_b.y) * q; if (!sk) { return 0; }  
            float fk = (m.m_a.x - n.m_a.x) + (m.m_a.y - n.m_a.y) * q;  
            k = fk / sk;
        }
        else {
            if (!(m.m_a.y - m.m_b.y)) { 
                cout << "Cross point not found" << endl;
                return 0; 
            }  
            k = (m.m_a.y - n.m_a.y) / (m.m_a.y - m.m_b.y);  
        }
        c.x = m.m_a.x + (m.m_b.x - m.m_a.x) * k;  
        c.y = m.m_a.y + (m.m_b.y - m.m_a.y) * k;  
        cout << "Cross point found: " << c.x << " " << c.y << endl;
        return 1;
    }

    bool Point_Cross(point a) {
        float check1 = (a.x - m_a.x) * (m_b.y - m_a.y);
        float check2 = (m_b.x - m_a.x) * (a.y - m_a.y);
        if (check1 == check2)
            if (min(m_a.y, m_b.y) <= a.y && (max(m_a.y, m_b.y) >= a.y) && min(m_a.x, m_b.x) <= a.x && max(m_a.x, m_b.x) >= a.x) {
                cout << "Point lies on segment";
                return 1;
            }
        cout << "Point doesn't lies on segment";
        return 0;
    }

   


protected:
    point m_a, m_b;
    double SGN(point a, point b, point c) { // Знак ориентированной площади.
        float check = (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
        if (check > 0) return 1;
        if (check < 0) return -1;
        return 0;
    }
};