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

template<typename T>
struct Position4D {
	T x;
	T y;
	T z;
	T i;

	Position4D() {};

	Position4D(T posX, T posY, T posZ, T posI) {
		x = posX;
		y = posY;
		z = posZ;
		i = posI;
	};
};

template<typename T>
struct Position5D {
	T x;
	T y;
	T z;
	T i;
	T j;

	Position5D() {};

	Position5D(T posX, T posY, T posZ, T posI, T posJ) {
		x = posX;
		y = posY;
		z = posZ;
		i = posI;
		j = posJ;
	};
};

#endif