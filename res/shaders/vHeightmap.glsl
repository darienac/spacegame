uniform sampler2D textureDiffuse;

void main() {
    vVertex = aVertex;
    vVertexRotated = (uNormalMatrix * vec4(aVertex, 1.0)).xyz;
    vPosition = (uModelMatrix * vec4(aVertex, 1.0)).xyz;
    vNormal = (uNormalMatrix * vec4(aNormal, 1.0)).xyz;
    vTexCoord = aTexCoord;

    float height = max(texture(textureDiffuse, vTexCoord).r * planetProps.maxLandHeight, planetProps.liquidHeight);
    gl_Position = uViewProjectionMatrix * vec4(aVertex * (height + 1.0), 1.0);
}