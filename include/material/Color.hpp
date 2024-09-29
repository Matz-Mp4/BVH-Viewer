#pragma once

class Color {
public:
    float r,g,b;
    
    Color() = default;
    Color(const float c);
    Color(const float red, const float green, const float blue);

    Color  operator+ (const Color& rhs);
    Color& operator+=(const Color& rhs);
    Color  operator- (const Color& rhs);
    Color  operator* (const Color& rhs) const;
    Color  operator* (const float rhs) const;
    Color  operator/ (const float rhs) const;
    bool   operator==(const Color& rhs);

    Color powc(float p) const;
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
static const Color ORANGE  = Color(1.0, 0.5, 0.0);


