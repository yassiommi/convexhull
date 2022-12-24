
# Convex Hull

By Yassaman Ommi
Email: ommiy@mcmaster.ca

* [Introduction](#Introduction)
    * [What is a Convex Hull?](#What-is-a-Convex-Hull?)
    * [Applications](#Applications)
* [Algorithms](#Algorithms)
    * [Gift-wrapping (Jarvis March)](#Gift-wrapping-(Jarvis-March))
    * [Quickhull](#Quickhull)
* [Implementation](#Implementation)

## Introduction 
### What is a Convex Hull?

Imagine a set of nails randomly pinned down on a plane. Then, imagine stretching a rubber band so that it surrounds the entire set of nails. If you release the rubber band, it will tighten around the nails, enclosing them and forming a shape. That shape is called the **convex set** or the **convex hull** of the set of nails, which is the smallest convex [*a subset of Euclidean space is convex if given any two points in the subset, the subset contains the whole line segment that joins them*] set that contains it.
![Rubber Band Analogy](http://url/to/img.png)

### Applications

Finding the convex set of a shape has a wide-range of applications, from simple daily life tasks to complex scientific problems, some of which have also inspired solutions to this problem. uses convex hull to keep track of the spatial expanding of a disease. Furthermore, the "magic wand" tool in photo editing apps, utilizes convex hull algorithms to completely select an object in the photo. Overall, finding the convex hull has many practical applications in various fields.

## Algorithms

### Gift-wrapping (Jarvis March)
Inspired by real-life, gift-wrapping is one of the simplest algorithms for this problem. It starts with the leftmost point p~0~, which known to be on the convex hull, and at each step i, p~i~ is selected such that all points are to the right of the line p~i-1~ p~i+1~. Considering h to be the number of points on the convex hull, gift-wrapping has O(nh) time complexity. 
![Gift-wrapping Algorithm]()

### Quickhull

Quickhull is a divide-and-conquer algorithm for computing the convex hull of a finite set of points. If r is the number of the processed points, O(nlog( r )) is its time complexity. Even though this algorithm works well, the processing can become really slow in cases of high symmetry or points lying on the circumference of a circle. Quickhull starts by finding the points with minimum and maximum x coordinates (p and q in the picture), as these will always be part of the convex hull. Then, it will use $pq$ line to divide the points into two subsets that will be processed recursively (P~1~ and P~2~). In the next step, in each subset, the point with the maximum distance from the line is chosen, forming a triangle with p and q. By definition, the points within these triangles can't be in the convex hull, so they'll be ignored. These steps are then repeated using the two new lines created by the triangle, and terminated when there no more points left to process. 
![Quickhull ALgorithm]()

## Implementation

- **Point Class**
 ```Point```  is implemented to store a point in Cartesian coordinate system. It has two private variables ```x``` and ```y```, which can be accessed using the functions ```get_x()``` and ```get_y()``` respectively. ```origin_distance()``` can be used to get the point's distance from origin. ```distance(Point)``` also returns the distance between two points. ```orientation()``` is a function to determine the orientation of three points. ```==```, ```!=``` and ```<<``` operators are also overloaded for this class. An example of these functions are demonstrated in the following: 
### Example:
- Constructing a Point:
```
int main() {
Point test1, test2 = Point(1,2);
cout << test1 << endl;
cout << test2 << endl;
}
```
Output:
```
(0, 0)
(1, 2)
```








