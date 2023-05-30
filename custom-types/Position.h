#ifndef POSITION_H
#define POSITION_H


// 2D and 3D flexible variable-type structures
template<typename T>
struct Position2D {
	T x;
	T y;

	Position2D() {};

	Position2D(T posX, T posY) {
		x = posX;
		y = posY;
	};
};

template<typename T>
struct Position3D {
	T x;
	T y;
	T z;

	Position3D() {};

	Position3D(T posX, T posY, T posZ) {
		x = posX;
		y = posY;
		z = posZ;
	};
};

#endif