//
// Created by dacma on 5/13/2024.
//

#ifndef SPACEGAME_UNIFORMBLOCK_H
#define SPACEGAME_UNIFORMBLOCK_H


#include "../GlBuffer.h"
#include "../model/Material.h"

class UniformBlock: public GlBuffer {
private:
    struct GLSL_Material {
        glm::vec3 ambient;
        float padding1;
        glm::vec3 diffuse;
        float padding2;
        glm::vec3 specular;
        float padding3;
        glm::vec3 emissive;
        float opacity;
    };
public:
    enum BindingPoint {
        MATERIAL
    };
    explicit UniformBlock(Material* material);

    void setBindingPoint(GLuint index);
};


#endif //SPACEGAME_UNIFORMBLOCK_H
