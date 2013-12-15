#ifndef SHADER_HPP
#define SHADER_HPP

struct shaders {
    GLuint vertex;
    GLuint fragment;
    GLuint geometry;
    GLuint tess_control;
    GLuint tess_eval;

    shaders(GLuint v, GLuint f, GLuint g, GLuint tcs, GLuint tes)
        : vertex(v), fragment(f), geometry(g), tess_control(tcs), tess_eval(tes)
    {
    }
    
    ~shaders() {
        free();
    }

    void free()
    {
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        glDeleteShader(geometry);
        glDeleteShader(tess_eval);
        glDeleteShader(tess_control);
    }
};

GLuint LoadShaders(const char *vertex_file_path,
                   const char *fragment_file_path,
                   const char *geometry_file_path,
                   const char *tess_control_file_path,
                   const char *tess_eval_file_path,
                   const char *attributeLocations[],
                   GLuint numberOfLocations);

#endif
