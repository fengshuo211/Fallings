#include "Vector.h"

Vector VectorMath::Add(Vector v1, Vector v2)
{
	int addedX = v1.x + v2.x;
	int addedY = v1.y + v2.y;
	return Vector(addedX, addedY);
}

Vector VectorMath::multiplyScalar(Vector v, int scalar)
{
	int newX = v.x * scalar;
	int newY = v.y * scalar;
	return Vector(newX, newY);
}

Vector::Vector()
{
}

Vector::Vector(int inputX, int inputY)
{
	x = inputX;
	y = inputY;
}

void Vector::setVector(int inputX, int inputY)
{
	x = inputX;
	y = inputY;
}

void Vector::add(Vector v)
{
	x = x + v.x;
	y = y + v.y;
}
