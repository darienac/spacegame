//
// Created by dacma on 4/3/2024.
//

#ifndef CS455GAME_SHADER2D_H
#define CS455GAME_SHADER2D_H


#include "ShaderProgram.h"
#include "../GlBuffer.h"
#include "../model/Cubemap.h"
#include "../model/Mesh2D.h"

class Shader2D: public ShaderProgram {
private:
    static std::string GLSL_HEADER;
    static inline std::unique_ptr<Mesh2D> STANDARD_MESH;

    // attributes
    GLint aVertex;
    GLint aTexCoord;

    // uniforms
    GLint uTexture;
public:
    static inline std::unique_ptr<GlBuffer> TEX_POSX_BUFFER;
    static inline std::unique_ptr<GlBuffer> TEX_NEGX_BUFFER;
    static inline std::unique_ptr<GlBuffer> TEX_POSY_BUFFER;
    static inline std::unique_ptr<GlBuffer> TEX_NEGY_BUFFER;
    static inline std::unique_ptr<GlBuffer> TEX_POSZ_BUFFER;
    static inline std::unique_ptr<GlBuffer> TEX_NEGZ_BUFFER;

    static void initBuffers();

    Shader2D(const std::vector<std::string> &vertexShader, std::vector<std::string> fragmentShader);

    void loadTexture(const Texture* texture);

    void draw();
    void draw(Cubemap *cubemap);
    void draw(Mesh2D *mesh);
    void draw(const Texture &texture);

    void bind(GlBuffer* vertices, GlBuffer* texCoords);
    void bind(GlBuffer* texCoords);
    void bind() override;
    void link() override;
};


#endif //CS455GAME_SHADER2D_H
