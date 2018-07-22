#ifndef VECTOR_H
#define VECTOR_H

class Vector {
public:
	Vector();
	Vector(int inputX, int inputY);
	
	void setVector(int inputX, int inputY);
	void add(Vector v);
	int x;
	int y;
};

class VectorMath {
public:
	Vector Add(Vector v1, Vector V2);
	static Vector multiplyScalar(Vector v, int scalar);
};

#endif // !VECTOR_H
