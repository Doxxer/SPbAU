#version 410

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 tes_worldCoord[3];
in vec4 tes_Position[3];

out vec3 gs_normal;
out vec3 gs_worldCoord;
out vec4 gs_Position;

void main(void)
{
    // Calculate the normal for the triangle
	vec3 diff1 = tes_worldCoord[2] - tes_worldCoord[0];
	vec3 diff2 = tes_worldCoord[1] - tes_worldCoord[0];
	vec3 normal = normalize(cross(diff1, diff2));
	
    //Pass through the original vertex and assign normals
    for(int i=0; i<3; i++) {
        gl_Position = gl_in[i].gl_Position;
        gs_worldCoord = tes_worldCoord[i];
        gs_normal = vec3(normal.x, -normal.y, -normal.z);
        gs_Position = tes_Position[i];
        EmitVertex();
    }
    EndPrimitive();
}
