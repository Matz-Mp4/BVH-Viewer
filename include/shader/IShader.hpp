#include <string>

class IShader {
    public:
       virtual void      use() = 0;
       virtual void  set_bool(const std::string &name, bool value) const = 0;
       virtual void   set_int(const std::string &name, int value) const = 0;
       virtual void set_float(const std::string &name, float value) const = 0;
};
