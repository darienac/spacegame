void main() {
	vVertex = aVertex;
	vVertexRotated = (uNormalMatrix * vec4(aVertex, 1.0)).xyz;
	vPosition = (uModelMatrix * vec4(aVertex, 1.0)).xyz;
	vNormal = (uNormalMatrix * vec4(aNormal, 1.0)).xyz;
	vTexCoord = aTexCoord;

	gl_Position = uViewProjectionMatrix * vec4(aVertex, 1.0);
}