#ifndef V3DINCLUDED
#define V3DINCLUDED

#include <iostream>
#include <iomanip>
#include <functional>

class vector3d
{
public:
	double x, y, z;

	vector3d() : x(0), y(0), z(0) {}
	vector3d(double x, double y, double z) : x(x), y(y), z(z) {}
	vector3d(const vector3d && other) : x(other.x), y(other.y), z(other.z) {}
    vector3d(const vector3d & other) : x(other.x), y(other.y), z(other.z) {}

    vector3d & operator += (const vector3d & other) {
        x += other.x, y += other.y, z += other.z;
        return *this;
    }
    vector3d & operator -= (const vector3d & other) {
        x -= other.x, y -= other.y, z -= other.z;
        return *this;
    }
    vector3d & operator *= (double k) {
        x *= k, y *= k, z *= k;
        return *this;
    }
    friend vector3d operator + (const vector3d & first, const vector3d & second) {
        vector3d res(first.x + second.x, first.y + second.y, first.z + second.z);
        return res;
    }
    friend vector3d operator - (const vector3d & first, const vector3d & second) {
        vector3d res(first.x - second.x, first.y - second.y, first.z - second.z);
        return res;
    }

    const vector3d & operator = (vector3d && other) {
        x = other.x; y = other.y; z = other.z;
        return *this;
    }
    const vector3d & operator = (vector3d & other) {
        x = other.x; y = other.y; z = other.z;
        return *this;
    }
	inline vector3d & balance(double walls_size) {
		if ( x * 2 < -walls_size )
			x += walls_size;
		else if ( x * 2 > walls_size )
			x -= walls_size;

		if ( y * 2 < -walls_size )
			y += walls_size;
		else if ( y * 2 > walls_size )
			y -= walls_size;

		if ( z * 2 < -walls_size )
			z += walls_size;
		else if ( z * 2 > walls_size )
			z -= walls_size;

		return *this;
	}

    friend vector3d operator * (vector3d & ve, double k) {
        vector3d res(ve.x * k, ve.y * k, ve.z * k);
        return res;
    }
    friend vector3d operator * (double k, vector3d & ve) {
        vector3d res(ve.x * k, ve.y * k, ve.z * k);
        return res;
    }

	friend std::ostream & operator << (std::ostream & os, vector3d & ve) {
	    os << std::fixed << std::setprecision(8) << "{" << ve.x << ", " << ve.y << ", " << ve.z << "}";
	    return os;
	}

	friend bool operator == (vector3d & a, vector3d & b) {
		return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
	}

	inline double length_sqr() {
	    return x * x + y * y + z * z;
	}
};

#endif
