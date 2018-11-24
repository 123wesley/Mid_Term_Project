#include<iostream>
#include<cmath>
using namespace std;


// calculate the Euclidean distance
float dist(int x1, int y1, int x2, int y2)
{
	return sqrt((x1- x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// given starting, ending point and turning point, return the cost 
double cost(int startX, int startY, int endX, int endY, int turnX, int turnY, 
			int m, int x[], int y[], int r[], int p[])
{
	// initialize d1, d2 and count the distance from starting point to turning point
	float d1 = 0, d2 = 0;
	d1 = dist(startX, startY, turnX, turnY);
	
	// grab the integer part to midCnt1, store remainder, count the delta of x, y
	int midCnt1 = d1;
	float remainder = d1 - midCnt1;
	float xDelta = (turnX - startX) / d1, yDelta = (turnY - startY) / d2;
	
	// sum up the risk of the first part
	double sumRisk = 0;
	for(int i = 1; i < d1; i++)
	{
		for(int j = 0; j < m; j++)
		{
			if(r[j] > dist(startX + i * xDelta, startY + i * yDelta, x[j], y[j]))
				{
					sumRisk = sumRisk + p[j] * ((r[j] - dist(startX + i * xDelta, startY + i * yDelta, x[j], y[j])) / r[j]);  // sum up all the risky point
				}
		}
	}
	
	// count d2 and the delta of x, y
	d2 = dist(endX, endY, turnX, turnY);
	xDelta = (endX - turnX) / d2;
	yDelta = (endY - turnY) / d2;
	
	// calculate the risk of path 2 and sum up
	for(int i = 1; i < d2; i++)
	{
		for(int j = 0; j < m; j++)
		{
			if(r[j] > dist((turnX - remainder * xDelta) + i * xDelta, (turnY - remainder * yDelta) + i * yDelta, x[j], y[j]))
				{
					sumRisk = sumRisk + p[j] * ((r[j] - dist((turnX - remainder * xDelta) + i * xDelta, (turnY - remainder * yDelta) + i * yDelta, x[j], y[j])) / r[j]);  // sum up all the risky point
				}
		}
	}
	return sumRisk;
}

int main()
{
	int n = 0, m = 0, w = 0, d = 0;
	cin >> n >> m >> w >> d;
	
	int* x = new int[m];
	int* y = new int[m];
	int* r = new int[m];
	int* p = new int[m];
	
	for(int i = 0; i < m; i++)
	{
		cin >> x[i];
	}
	for(int i = 0; i < m; i++)
	{
		cin >> y[i];
	}
	for(int i = 0; i < m; i++)
	{
		cin >> r[i];
	}
	for(int i = 0; i < m; i++)
	{
		cin >> p[i];
	}
	
	int xStart = 0, yStart = 0, xEnd = 0, yEnd = 0;
	cin >> xStart >> yStart >> xEnd >> yEnd;
	
	double min = 0;
	int minX = -1, minY = -1;
	
	min = cost(xStart, yStart, xEnd, yEnd, xStart, yStart, m, x, y, r, p);
	
	// for all the points
	for(int i = xStart; i <= xEnd; i++)
	{
		for(int j = yStart; i <= yEnd; j++)
		{
			// if flying distance > limitation, break!!
			if(dist(xStart, yStart, i, j) + dist(i, j, xEnd, yEnd) > d)
			{
				break;
			}
			// if not, continue
			// initialize tempCost 
			double tempCost = cost(xStart, yStart, xEnd, yEnd, i, j, m, x, y, r, p);
			if(tempCost < min + w)
			{
				min = tempCost + w;
				minX = i;
				minY = j;
			}
		}
	}
	
	if(minX >= 0 && minY >= 0)
		cout << "1 " << minX << " " << minY;
	else
		cout << "0";
	
	return 0;
}


