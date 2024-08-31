/**
  Describes how to compute the color of a specific material 
**/
class IShade {
    public:
        virtual          ~IShade() {};
        virtual void       shade() = 0;
        virtual void load_shader() = 0;
};
