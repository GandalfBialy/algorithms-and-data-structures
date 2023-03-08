#include <iostream>


struct Point {
	int x;
	int y;
};


int main()
{
	int coordinatesQuantity;
	int pointsQuantity;
	long double area = 0;

	std::cin >> coordinatesQuantity;
	pointsQuantity = coordinatesQuantity / 2;

	// 1st variant - without use of array

	Point currentPoint{}, previousPoint{};
	Point firstPoint{};

	std::cin >> firstPoint.x >> firstPoint.y;
	previousPoint = firstPoint;

	for (int i = 0; i < pointsQuantity - 1; i++) {
		std::cin >> currentPoint.x >> currentPoint.y;

		area += (previousPoint.x + currentPoint.x) * (previousPoint.y - currentPoint.y);

		previousPoint = currentPoint;
	}
	area += (previousPoint.x + firstPoint.x) * (previousPoint.y - firstPoint.y);
	

	// 2nd variant - with use of array
	
	/*Point* points = new Point[pointsQuantity];

	for (int i = 0; i < pointsQuantity; i++) {
		std::cin >> points[i].x >> points[i].y;
	}

	int j = pointsQuantity - 1;
	for (int i = 0; i < pointsQuantity; i++) {
		std::cout << points[i].x << " " << points[i].y << std::endl;
		
		area += (points[j].x + points[i].x) * (points[j].y - points[i].y);
		j = i;
	}*/
	
	area = abs(area) / 2;

	std::cout << (int)area << std::endl;
}
