#pragma once 

#include "../material/Color.hpp"
#include "../math/Vector4.hpp"

class PointLight {
    public: 
         PointLight(const Color& color, const Vector4& position); 
         PointLight() = default;
        ~PointLight() = default;

         PointLight        with_color(const Color& color) const;
         PointLight     with_position(const Vector4& position) const;

         Color      get_color() const;
         Vector4 get_position() const;

    private:
        Vector4 position;
        Color      color;
};
