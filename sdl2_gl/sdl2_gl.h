#pragma once

#include <vector>
#include <sdl2_engine.h>
#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include "Shader.h"

namespace SDL
{

struct GLColor
{
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;

    GLColor()
        : r(0.0f)
        , g(0.0f)
        , b(0.0f)
        , a(1.0f)
    {}
    GLColor(GLfloat r, GLfloat g, GLfloat b)
        : r(r)
        , g(g)
        , b(b)
        , a(1.0f)
    {}
    GLColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {}
};

struct GLVector
{
    GLfloat x;
    GLfloat y;
    GLfloat z;

    GLVector()
        : x(0.0f)
        , y(0.0f)
        , z(0.0f)
    {}
    GLVector(GLfloat x, GLfloat y, GLfloat z)
    : x(x)
    , y(y)
    , z(z)
    {}
};

struct GLVertex
{
    GLVector pos;
    GLColor color;
};

struct GL_VBO
{
    std::vector<GLuint> data;

    GL_VBO(GLsizei count)
        :data(count)
    {
        glGenBuffers(count, data.data());
    }
};

struct GL_VAO
{
    std::vector<GLuint> data;

    GL_VAO(GLsizei count)
        :data(count)
    {
        glGenVertexArrays(count, data.data());
    }
};

struct GLVectorArray
{
    std::vector<GLfloat> data;

    GLVectorArray(uint32_t numPoints)
        : data(numPoints * 3)
    {
    }
    void AddVector(size_t index, GLVector vector)
    {
        data[index * 3 + 0] = vector.x;
        data[index * 3 + 1] = vector.y;
        data[index * 3 + 2] = vector.z;
    }
    void SetData()
    {
        uint32_t size = data.size() * sizeof(GLfloat);
        glBufferData(GL_ARRAY_BUFFER, size, data.data(), GL_STATIC_DRAW);
    }
};

struct GLColorArray
{
    std::vector<GLfloat> data;

    GLColorArray(uint32_t numPoints)
        : data(numPoints * 4)
    {
    }
    void AddColor(size_t index, GLColor color)
    {
        data[index * 4 + 0] = color.r;
        data[index * 4 + 1] = color.g;
        data[index * 4 + 2] = color.b;
        data[index * 4 + 3] = color.a;
    }
    void SetData()
    {
        uint32_t size = data.size() * sizeof(GLfloat);
        glBufferData(GL_ARRAY_BUFFER, size, data.data(), GL_STATIC_DRAW);
    }
};

struct GLVertexArray
{
    GLVectorArray dataVectors;
    GLColorArray dataColors;
    GL_VBO vbo;
    GL_VAO vao;
    Shader shader;

    GLVertexArray(uint32_t numPoints)
        : dataVectors(numPoints)
        , dataColors(numPoints)
        , vbo(2)
        , vao(1)
    {
    }
    ~GLVertexArray()
    {
        // Cleanup all the things we bound and allocated
        shader.CleanUp();

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDeleteBuffers(2, vbo.data.data());
        glDeleteVertexArrays(1, vao.data.data());
    }
    void AddVector(size_t index, GLVector vector)
    {
        dataVectors.AddVector(index, vector);
    }
    void AddColor(size_t index, GLColor color)
    {
        dataColors.AddColor(index, color);
    }
    void SetData()
    {
        glBindVertexArray(vao.data[0]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo.data[0]);
        dataVectors.SetData();
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo.data[1]);
        dataColors.SetData();
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);

        if (shader.Init())
            shader.UseProgram();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    void UpdateColorData()
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo.data[1]);
        dataColors.SetData();
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
};

class Demo : public Engine
{
public:
    Demo();
    virtual ~Demo();

    virtual void CreateSurface() override;
    virtual void DestroySurface() override;

    virtual void OnKeyDown(SDL_Event * event);
    virtual void OnKeyUp(SDL_Event * event);
    virtual void Update();
    virtual void Draw();

private:
    SDL_GLContext _glContext;
    SDL_Surface * _surface;
    SDL_Texture * _texture;
    GLColor _colorBackground;
    GLColor _color;
    GLfloat _component;
    GLfloat _componentDelta;
    int _componentIndex;
    GLVertexArray * _object;
};

}
