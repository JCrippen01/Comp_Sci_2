#include <iostream>
#include <string>

// ============================================================
// Rectangle class - represents a rectangle with width and height
// ============================================================
class Rectangle {
private:
    double width;
    double height;

public:
    // Constructor - sets width and height
    Rectangle(double width, double height) : width(width), height(height) {}

    // Calculate and return the area
    double getArea() const { return width * height; }

    // Calculate and return the perimeter
    double getPerimeter() const { return 2 * (width + height); }

    // Getters
    double getWidth()  const { return width; }
    double getHeight() const { return height; }

    // Overload << so Rectangle can be printed directly with cout
    friend std::ostream& operator<<(std::ostream& os, const Rectangle& r) {
        os << "Rectangle(Width: " << r.width 
           << ", Height: "        << r.height
           << ", Area: "          << r.getArea()
           << ", Perimeter: "     << r.getPerimeter() << ")";
        return os;
    }
};

// ============================================================
// Box class template - wraps a single value of any type
// ============================================================
template <typename T>
class Box {
private:
    T value;  // The single stored value

public:
    // Constructor
    Box(T value) : value(value) {}

    // Getter
    T getValue() const { return value; }

    // Sette:
    void setValue(T newValue) { value = newValue; }

    // Prints the stored value
    void display() const {
        std::cout << "[ " << value << " ]" << std::endl;
    }
};

// ============================================================
// main - demonstrates a Box holding a Rectangle
// ============================================================
int main() {

    // --- Create a Rectangle ---
    Rectangle rect(10.0, 5.0);

    // --- Put the Rectangle inside a Box ---
    Box<Rectangle> box(rect);

    // --- Display the Box contents ---
    box.display();
    // Output: [ Rectangle(Width: 10, Height: 5, Area: 50, Perimeter: 30) ]

    // --- Retrieve the Rectangle from the Box and use its methods ---
    Rectangle retrieved = box.getValue();
    std::cout << "Width:     " << retrieved.getWidth()     << std::endl;
    std::cout << "Height:    " << retrieved.getHeight()    << std::endl;
    std::cout << "Area:      " << retrieved.getArea()      << std::endl;
    std::cout << "Perimeter: " << retrieved.getPerimeter() << std::endl;

    // --- Update the Box with a new Rectangle ---
    Rectangle newRect(7.0, 3.0);
    box.setValue(newRect);

    std::cout << "\nAfter update:" << std::endl;
    box.display();
    // Output: [ Rectangle(Width: 7, Height: 3, Area: 21, Perimeter: 20) ]

    return 0;
}
```

**Output:**
```
[ Rectangle(Width: 10, Height: 5, Area: 50, Perimeter: 30) ]
Width:     10
Height:    5
Area:      50
Perimeter: 30

After update:
[ Rectangle(Width: 7, Height: 3, Area: 21, Perimeter: 20) ]
