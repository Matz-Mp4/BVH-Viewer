#pragma once

class Color {
public:
    double r,g,b;
    
    Color() = default;
    Color(const double c);
    Color(const double red, const double green, const double blue);

    Color  operator+ (const Color& rhs);
    Color& operator+=(const Color& rhs);
    Color  operator- (const Color& rhs);
    Color  operator* (const Color& rhs) const;
    Color  operator* (const double rhs) const;
    Color  operator/ (const double rhs) const;
    bool   operator==(const Color& rhs);

    Color powc(double p) const;
};

Color operator*(const float a, const Color& c);

//static const: "... will retain its value 
//               till the execution of the 
//               program and also, it will 
//               not accept any change in its value."
static const Color WHITE   = Color(1.0, 1.0, 1.0);
static const Color BLACK   = Color(0.0, 0.0, 0.0);
static const Color RED     = Color(1.0, 0.0, 0.0);
static const Color BLUE    = Color(0.0, 0.0, 1.0);
static const Color GREEN   = Color(0.0, 1.0, 0.0);
static const Color CYAN    = Color(0.0, 1.0, 1.0);
static const Color MAGENTA = Color(1.0, 0.0, 1.0);
static const Color YELLOW  = Color(1.0, 1.0, 0.0);


