#include <iostream>
#include <vector>
#include <string>
#include <memory>


class Shape {
protected:
    std::string color;
    
public:
    // TASK 1: Implement the constructor to initialize the 'color' attribute.
    Shape(const std::string& c) : color(c) {}

    
    // TASK 2: Define the pure virtual function for drawing, named 'draw'.
    virtual void draw() const = 0;

    
    // TASK 3. Define a virtual destructor.
    // Inside, print: "Base (Shape) destructor for 'color'.
    virtual ~Shape(){
        std::cout << "Base (Shape) destructor for " << color << "." << std::endl;
    }

};


class Circle : public Shape {
private:
    double radius;
    
public:
    // TASK 4: Implement the Circle constructor. It must call the Base (Shape) constructor.
    Circle(const std::string &col, double r) : Shape(col), radius(r) {}
    
    // TASK 5: Implement the 'draw' function, using the 'override' keyword.
    // Inside, print: "'color' circle with radius 'radius'."
    void draw() const override{
         std::cout << color << " circle with radius " << radius << "." << std::endl;
    }

    
    // TASK 6: Include a derived destructor.
    // Inside, print: "Circle destructor."
    ~Circle(){
        std::cout << "Circle destructor." << std::endl;
    }

};


class Rectangle : public Shape {
private:
    double width, height;
    
public:
    // TASK 7: Implement the Rectangle constructor, calling the Base (Shape) constructor.
    Rectangle(std::string col, double w, double h) : Shape(col), width(w), height(h) {}

    
    // TASK 8: Implement the 'draw' function, using the 'override' keyword.
    // Inside, print: "'color' rectangle ('width' x 'height')."
    void draw() const override{
         std::cout << color << " rectangle (" << width << " x " << height << ")." << std::endl;
    }
    
    // TASK 9: Include a derived destructor.
    // Inside, print: "Rectangle destructor."
    ~Rectangle(){
        std::cout << "Rectangle destructor." << std::endl;
    }

};


int main() {
    std::vector<std::unique_ptr<Shape>> canvas;

    // TASK 10: Create a "Red" Circle (with radius 5.0) and add its pointer to the canvas.
    // Use std::make_unique and push_back functions.
    canvas.push_back(std::make_unique<Circle>("Red",5.0));

    
    // TASK 11: Create a "Blue" Rectangle (10.0 x 8.0) and add its pointer to the canvas.
    canvas.push_back(std::make_unique<Rectangle>("Blue",10.0,8.0));


    for (const auto& s : canvas) {
        // TASK 12: Call the draw method polymorphically.
        s->draw();

    }
    // Task 13: create an object and delete it properly without memory leaks by using virtual destructors, not relying on smart pointers.
    Shape* shape = new Circle("Green", 12.345);
    shape->draw();
    delete shape;

    canvas.clear();
    return 0;
}
