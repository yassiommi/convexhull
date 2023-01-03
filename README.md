
# Convex Hull

By Yassaman Ommi

Email: ommiy@mcmaster.ca

* [Introduction](#Introduction)
    * [What is a Convex Hull?](#What-is-a-Convex-Hull?)
    * [Applications](#Applications)
* [Algorithms](#Algorithms)
    * [Gift-wrapping (Jarvis March)](#gift-wrapping-jarvis-march)
    * [Quickhull](#Quickhull)
* [Implementation](#Implementation)
    * [Geometry Classes](#geometry-classes)
    * [Utility Functions](utility-functions)
    * [Visualization Functions](visualization-functions)
    * [Bitmap Image Functions](bitmap-image-functions)
* [Running the Program](running-the-program)
    
## Introduction 
### What is a Convex Hull?

Imagine a set of nails randomly pinned down on a plane. Then, imagine stretching a rubber band so that it surrounds the entire set of nails. If you release the rubber band, it will tighten around the nails, enclosing them and forming a shape. That shape is called the **convex set** or the **convex hull** of the set of nails, which is the smallest convex [*a subset of Euclidean space is convex if given any two points in the subset, the subset contains the whole line segment that joins them*] set that contains it.
![Rubber Band Analogy](https://github.com/yassiommi/convexhull/blob/main/ch.jpg)

### Applications

Finding the convex set of a shape has a wide-range of applications, from simple daily life tasks to complex scientific problems, some of which have also inspired solutions to this problem. uses convex hull to keep track of the spatial expanding of a disease. Furthermore, the "magic wand" tool in photo editing apps, utilizes convex hull algorithms to completely select an object in the photo. Overall, finding the convex hull has many practical applications in various fields.

## Algorithms

### Gift-wrapping (Jarvis March)
Inspired by real-life, gift-wrapping is one of the simplest algorithms for this problem. It starts with the leftmost point $p_0$, which known to be on the convex hull, and at each step $i$, $p_i$ is selected such that all points are to the right of the line $p_{i-1}$ $p_{i+1}$. Considering $h$ to be the number of points on the convex hull, gift-wrapping has $O(nh)$ time complexity. 
![Gift-wrapping Algorithm](https://github.com/yassiommi/convexhull/blob/main/giftwrapping.png)

### Quickhull

Quickhull is a divide-and-conquer algorithm for computing the convex hull of a finite set of points. If $r$ is the number of the processed points, $O(nlog(r))$ is its time complexity. Even though this algorithm works well, the processing can become really slow in cases of high symmetry or points lying on the circumference of a circle. Quickhull starts by finding the points with minimum and maximum $x$ coordinates ($p$ and $q$ in the picture), as these will always be part of the convex hull. Then, it will use $pq$ line to divide the points into two subsets that will be processed recursively ($P_1$ and $P_2$). In the next step, in each subset, the point with the maximum distance from the line is chosen, forming a triangle with $p$ and $q$. By definition, the points within these triangles can't be in the convex hull, so they'll be ignored. These steps are then repeated using the two new lines created by the triangle, and terminated when there no more points left to process. 
![Quickhull ALgorithm](https://github.com/yassiommi/convexhull/blob/main/quickhull.png)

## Implementation

### Geometry Classes

- **Point Class**
 ```Point```  is implemented to store a point in Cartesian coordinate system. It has two private variables ```x``` and ```y```, which can be accessed using the functions ```get_x()``` and ```get_y()``` respectively. ```distance_to(Point)``` can be used to calculate the distance between two points. ```==```, ```!=```, ```<<```, ```-```, and ```=``` operators are also overloaded for this class. A test script is provided to test the different functionalities of the class in ```tests/geometry.test```. A sample code to use the class is provided below:
```
int main() {
    Point p1(1, 2);
    Point p2(3, 4);
    Point p3;
    
    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;
    cout << "p3 = " << p3 << endl;
    cout << "distance between p1 and p2 is: " << p1.distance_to(p2) << endl;
    cout << "distance between p2 and p3 is: " << p2.distance_to(p3) << endl;
    cout << "distance between p3 and p3 is: " << p3.distance_to(p3) << endl;
    
    if (p1 == p2) {
        cout << "p1 == p2 is True" << endl;
    }
    else {
        cout << "p1 == p2 is False" << endl;
    }
}
```
Output:
```
p1 = (1, 2)
p2 = (3, 4)
p3 = (0, 0)
distance between p1 and p2 is: 2.82843
distance between p2 and p3 is: 5
distance between p3 and p3 is: 0
p1 == p2 is False
```

- **Line Class**
```Line``` is implemented to store a line in Cartesian coordinate system. It has two private variables ```start```, and ```end```, which can be accessed using the functions ```get_start()```, ```get_end()``` respectively. ```slope()``` can be used to calculate the slope of the line. ```intersection()``` can be used to calculate the y-intercept of the line. ```length()``` returns the length of the line.```distance_from_point(Point)``` can be used to calculate the distance between a line and a point. Moreover, ```is_point_on_left_of_line(Point)``` checks if a point is on the left of the line. ```-```, ```*```, ```<<``` are also overloaded for this class. A test script is provided to test the different functionalities of the class in ```tests/geometry.test```. A sample code to use the class is provided below:
```
#include "geometry.hpp"

int main() {
    // y = 2x + 3
    Point p1 = Point(1, 5);
    Point p2 = Point(5, 13);
    Point p3; // (0,0)
    
    Line line = Line(p1, p2);
    
    cout << "line's slope is: " << line.slope() << endl;
    cout << "line's intersection with the y-axis is: " << line.intersection() << endl;
    cout << "the distance between (0,0) and the line is: " << line.distance_from_point(p3) << endl;
    
    if (line.is_point_on_left_of_line(p3)) {
        cout << "(0,0) is on the left of the line" << endl;
    }
    else {
        cout << "(0,0) is not on the left of the line" << endl;
    }
}
```
Output:
```
line's slope is: 2
line's intersection with the y-axis is: 3
the distance between (0,0) and the line is: 1.34164
(0,0) is on the left of the line
```

### Utility Functions

- **Generating Random Data**
```generate_random_data_points(uint64_t count)``` is a function that generates ```count``` random points in the Cartesian coordinate system. The function returns a vector of ```Point``` objects. A sample code to use the class is provided below:
```
#include "utils.hpp"

int main() {
    std::vector<Point> data = generate_random_data_points(5);
    cout << "Data points:" << endl;
    for (vector<Point>::iterator it = data.begin(); it != data.end(); it++)
        {
            Point point = (Point)*it;
            cout << point << endl;
        }
}
```
Output:
```
Data points:
(0.737111, 0.628095)
(0.388742, 0.585699)
(0.844349, 0.967414)
(0.332131, 0.130819)
(0.66698, 0.928009)
```

- **hex and int Conversions**
```hex_string_to_int(string)``` is a function that converts a hexadecimal string to an integer. ```int_to_hex_string(number)``` is a function that converts an integer to a hexadecimal string. A sample code to use the class is provided below:
```
#include "utils.hpp"

int main() {
    uint64_t number = 1234;
    string hex = int_to_hex_string(number);
    
    cout << "1234 in hex is: " << hex << endl;
    cout << hex << " in binary is: " << hex_string_to_binary_string(hex) << endl;
    
}
```
Output:
```
1234 in hex is: 000004D2
000004D2 in binary is: \322
```

### Visualization Functions

- **Initializing an Image**
```initialize_image_array(width, height)``` is a function that initializes an image array of size ```width``` x ```height```. The function returns a 2D array of zeros. 

- ** Getting Coordinate Locations from Image**
```get_coordinate_location_on_image(coord, length)``` can be used to get the coordinate location on the image. ```coord``` is the coordinate of the point, and ```length``` is the length of the image. A ```PADDING + POINT_THICKNESS``` is eliminated for obvious reasons. 

- **Constructing an Image**
In order to construct an image array from given points ```add_point_to_image_array(image_array, width, height, p)``` can be used. ```image_array``` is a 2d array, ```width``` and ```height``` are the dimensions of the image, and ```p``` is the point to be added to the image. The point's coordinates are accessed via the ```get_x()``` and ```get_y()``` functions, and then the corresponding element in the array is set to 1. The function returns the image array with the point added to it. A sample to show its usage is provided below:
```
#include "visualizer.hpp"
#include "geometry.hpp"

int main() {
    uint64_t width = 5;
    uint64_t height = 10;
    Point point = Point(2, 4);
    
    double **image_array = initialize_image_array(width, height);
    cout << "The initiated image array: " << endl;
    for (uint64_t i = 0; i < height; ++i)
        {
            for (uint64_t j = 0; j < width; ++j)
            {
                cout << image_array[i][j] << "  ";
            }
            cout << endl;
        }
    
    image_array = add_point_to_image_array(image_array, width, height, point);
    cout << endl;
    cout << "The image array with the point: " << point << endl;
    for (uint64_t i = 0; i < height; ++i)
        {
            for (uint64_t j = 0; j < width; ++j)
            {
                cout << image_array[i][j] << "  ";
            }
            cout << endl;
        }
}
```
Output:
```
The initiated image array: 
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  
The image array with the point: (2, 4)
0  0  0  0  0  0  0  0  0  0  0  0  0  0  1  1  1  1  0  1  1  1  1  0  1  1  1  1  0  1  1  1  1  0  1  1  1  1  0  0  0  0  0  0  0  0  0  0  0  0
```
Furthermore, ```add_line_to_image_array(image_array, width, height, line)``` can be used to add a line to the image array. ```image_array``` is a 2d array, ```width``` and ```height``` are the dimensions of the image, and ```line``` is the line to be added to the image. The function returns the image array with the line added to it. 

### Bitmap Image Functions
The program is designed to take a bitmap image as input, and output a bitmap image as well. Wikipedia' s guide for creating a bitmap image was used to implement this function. Each pixel in this format is presented with 3 bytes, along with a 1 byte padding to keep it at a 4 byte alignment. 

## Running the Program

Use the following command in the program's directory to run the program:
```
g++ main.cpp -Wall -Wextra -Wconversion -Wsign-conversion -Wshadow -Wpedantic -std=c++20 -o run
./run
```
The program will first generated 20 random points, and then it will generate a bitmap image with the points, which will be saved in the same directory as the program, named ```data.bmp```. Then the two algorithms will be run on the points, and the results will both be printed to the console, and saved as bmp files in the same directory as the program, named ```convex_hull_quickhull.bmp``` and ```convex_hull_giftwrapping.bmp``` with red lines forming the convex hull. **If ```data.bmp``` and the results' files already exist in the directory, the program will not generate a new image, and will overwrite the existing ones.**
An example of the output is provided below:
The generated data points:
![Data](https://github.com/yassiommi/convexhull/blob/main/data.bmp)

The convex hull generated by the quickhull algorithm:
![Quickhull](https://github.com/yassiommi/convexhull/blob/main/convex_hull_quickhull.bmp)

The convex hull generated by the gift wrapping algorithm:
![Gift Wrapping](https://github.com/yassiommi/convexhull/blob/main/convex_hull_giftwrapping.bmp)
