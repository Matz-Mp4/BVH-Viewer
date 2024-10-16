#pragma once 

#include "../material/Color.hpp"

class GlobalAmbient {
    public: 
         GlobalAmbient(const Color& color); 
         GlobalAmbient() = default;
        ~GlobalAmbient() = default;

         GlobalAmbient with_color(const Color& color) const;
         Color          get_color() const;


    private:
        Color     color;
};
