#include "../ExportLight.hpp"

class ExportAPD: public ExportLight{
    public:
         ExportAPD(std::string _ambient, std::string _point_light[]);
         ExportAPD();
        ~ExportAPD() = default;
         void     export_ambient(size_t shader_id, const GlobalAmbient &_ambient) override;
         void export_point_light(size_t shader_id, const PointLight &_point_light)override;
         
    private:
        std::string     ambient;
        //point_light[0] = position
        //point_light[1] = color 
        std::string point_light[2];
};
