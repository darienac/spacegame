//
// Created by dacma on 4/3/2024.
//

#ifndef CS455GAME_SHADER2D_H
#define CS455GAME_SHADER2D_H


#include "ShaderProgram.h"
#include "../GlBuffer.h"
#include "../model/Cubemap.h"

class Shader2D: public ShaderProgram {
private:
    static std::string GLSL_HEADER;

    static inline GlBuffer *VERTICES_BUFFER;
    static inline GlBuffer *TEX_BUFFER;
    static inline GlBuffer *FACES_BUFFER;

    // attributes
    GLint aVertex;
    GLint aTexCoord;

    // uniforms
    GLint uTexture;
public:
    static inline GlBuffer *TEX_POSX_BUFFER;
    static inline GlBuffer *TEX_NEGX_BUFFER;
    static inline GlBuffer *TEX_POSY_BUFFER;
    static inline GlBuffer *TEX_NEGY_BUFFER;
    static inline GlBuffer *TEX_POSZ_BUFFER;
    static inline GlBuffer *TEX_NEGZ_BUFFER;

    static void initBuffers();

    Shader2D(const std::vector<std::string> &vertexShader, std::vector<std::string> fragmentShader);

    void loadTexture(Texture* texture);

    void draw();
    void draw(Cubemap *cubemap);

    void bind(GlBuffer* texCoords);
    void bind() override;
    void link() override;

    ~Shader2D() override;
};


#endif //CS455GAME_SHADER2D_H
