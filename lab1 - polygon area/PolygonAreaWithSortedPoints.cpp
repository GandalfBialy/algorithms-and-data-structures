#include <iostream>


struct Point {
    long long x;
    long long y;
};


bool comparePointsPosition(Point a, Point b, Point lowestPoint) {
    long double angleA = atan2(a.y - lowestPoint.y, a.x - lowestPoint.x);
    long double angleB = atan2(b.y - lowestPoint.y, b.x - lowestPoint.x);

    if (angleA == angleB) {
        return a.x < b.x;
    }

    return angleA < angleB;
}


void sortClockwise(Point points[], int n) {
    int lowestPointIndex = 0;

    for (int i = 1; i < n; i++) {
        if (points[i].y < points[lowestPointIndex].y ||
            (points[i].y == points[lowestPointIndex].y && points[i].x < points[lowestPointIndex].x)) {
            lowestPointIndex = i;
        }
    }

	Point temp = points[0];
	points[0] = points[lowestPointIndex];
	points[lowestPointIndex] = temp;

	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (comparePointsPosition(points[i], points[j], points[0])) {
				Point temp = points[i];
				points[i] = points[j];
				points[j] = temp;
			}
		}
	}
}


int main()
{
    int polygonsQuantity = 0;

    std::cin >> polygonsQuantity;

    for (int i = 0; i < polygonsQuantity; i++) {
        long double area = 0;
        int coordinatesQuantity = 0;
        int pointsQuantity = 0;
        
		std::cin >> coordinatesQuantity;
		pointsQuantity = coordinatesQuantity / 2;

        Point* points = new Point[pointsQuantity];

        for (int i = 0; i < pointsQuantity; i++) {
            std::cin >> points[i].x >> points[i].y;
        }

        sortClockwise(points, pointsQuantity);

        int j = pointsQuantity - 1;
        for (int i = 0; i < pointsQuantity; i++) {
            area += (long double)(points[j].x + points[i].x) * (points[j].y - points[i].y);
            j = i;
        }

        area = abs(area) / 2;
        
        std::cout << (long long)(area) << std::endl;
    }

    return 0;
}
