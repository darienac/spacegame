//
// Created by dacma on 5/13/2024.
//

#ifndef SPACEGAME_UNIFORMBLOCK_H
#define SPACEGAME_UNIFORMBLOCK_H


#include "../GlBuffer.h"
#include "../model/Material.h"

class UniformBlock: public GlBuffer {
private:
    static void loadVec3(GLfloat *buffer, const glm::vec3 &data);
public:
    enum BindingPoint {
        MATERIAL
    };
    explicit UniformBlock(Material* material);

    void setBindingPoint(GLuint index);
};


#endif //SPACEGAME_UNIFORMBLOCK_H
