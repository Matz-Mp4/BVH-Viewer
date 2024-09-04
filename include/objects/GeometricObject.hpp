#pragma once
#include "Mesh.hpp"
#include "../material/Material.hpp"

enum class TYPE_DRAW {NORMAL, WIRE_FRAME};

class GeometricObject {
    public :
        virtual void         gen_triangles() = 0;
        virtual void                  draw(TYPE_DRAW type) = 0;
        virtual void              set_mesh(Mesh mesh) = 0;
        virtual void          set_material(Material material) = 0;
};
