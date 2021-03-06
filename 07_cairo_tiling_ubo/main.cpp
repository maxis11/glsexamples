//Fragment shader was taken from https://www.shadertoy.com/view/4ssSWf

#include <iostream>
#include <fstream>
#include <backend/engInit.hpp>
#include <backend/engBuffer.hpp>
#include <backend/engValue.hpp>
#include <backend/engShader.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

using namespace std;

int main()
{
    EngInit init;
    unsigned win = init.createGLWindow("Example 7",800,600);
    EngGLPlatform* platform = init.getEngGLPlatform(win);
    EngGLShader shader;
    string src;
    ifstream in("vert.glsl");
    getline(in,src,'\0');
    in.close();
    shader.compileShaderStage(gl::GLenum(GL_VERTEX_SHADER),src);
    in.open("frag.glsl");
    getline(in,src,'\0');
    in.close();
    shader.compileShaderStage(gl::GLenum(GL_FRAGMENT_SHADER),src);
    shader.linkShader();
    auto log = shader.getErrLog();
    for (unsigned i = 0; i < log.size(); i++)
        cout << log[i]<<endl;
    if (log.size() > 0) return 1;
    shader.bind_program();
    GLuint VAO;
    gl::glGenVertexArrays(1,&VAO);
    gl::glBindVertexArray(VAO);
    EngGLUBO ubo(&shader,"block");
    ubo.load(gl::GLenum(GL_STATIC_DRAW));
    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    glm::vec3 cam_position = glm::vec3(2,2,2);
    glm::mat4 View = glm::lookAt(cam_position, glm::vec3(0,0,0), glm::vec3(0,1,0));
    auto start = std::chrono::system_clock::now();
    auto end = start;
    std::chrono::duration<float> fsec = end- start;
    float time = fsec.count();
    float resolut [] = {400.0,300.0};
    ubo.writeUBOVec(resolut,0,2);
    ubo.writeUBOScalar(time,1);
    ubo.writeUBOMat((float*)&Projection[0][0],2,4,4);
    ubo.writeUBOMat((float*)&View[0][0],3,4,4);
    ubo.enable(0,true);
    EngGLVBO buf1(&shader,"pos");
    GLfloat pos[] = {
        -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
    };
    buf1.allocate(sizeof(pos),gl::GLenum(GL_STATIC_DRAW),pos);
    glClearColor(0.3f,0.3f,0.3f,1.0f);
    buf1.bind(3);
    buf1.enable();
    gl::glEnable(gl::GLenum(GL_DEPTH_TEST));
    gl::glDepthFunc(gl::GLenum(GL_LESS));
    do
    {
        if (glfwGetKey(platform->controll_window, GLFW_KEY_D ) == GLFW_PRESS)
        {
            cam_position.x += 0.1f;
            View = glm::lookAt(cam_position, glm::vec3(0,0,0), glm::vec3(0,1,0));
            ubo.writeUBOMat((float*)&View[0][0],3,4,4);
        }
        if (glfwGetKey(platform->controll_window, GLFW_KEY_A ) == GLFW_PRESS)
        {
            cam_position.x -= 0.1f;
            View = glm::lookAt(cam_position, glm::vec3(0,0,0), glm::vec3(0,1,0));
            ubo.writeUBOMat((float*)&View[0][0],3,4,4);
        }
        if (glfwGetKey(platform->controll_window, GLFW_KEY_W ) == GLFW_PRESS)
        {
            cam_position.y += 0.1f;
            View = glm::lookAt(cam_position, glm::vec3(0,0,0), glm::vec3(0,1,0));
            ubo.writeUBOMat((float*)&View[0][0],3,4,4);
        }
        if (glfwGetKey(platform->controll_window, GLFW_KEY_S ) == GLFW_PRESS)
        {
            cam_position.y -= 0.1f;
            View = glm::lookAt(cam_position, glm::vec3(0,0,0), glm::vec3(0,1,0));
            ubo.writeUBOMat((float*)&View[0][0],3,4,4);
        }
        if (glfwGetKey(platform->controll_window, GLFW_KEY_Q ) == GLFW_PRESS)
        {
            cam_position.z += 0.1f;
            View = glm::lookAt(cam_position, glm::vec3(0,0,0), glm::vec3(0,1,0));
            ubo.writeUBOMat((float*)&View[0][0],3,4,4);
        }
        if (glfwGetKey(platform->controll_window, GLFW_KEY_E ) == GLFW_PRESS)
        {
            cam_position.z -= 0.1f;
            View = glm::lookAt(cam_position, glm::vec3(0,0,0), glm::vec3(0,1,0));
            ubo.writeUBOMat((float*)&View[0][0],3,4,4);
        }
        end = std::chrono::system_clock::now();
        fsec = end- start;
        time = fsec.count();
        ubo.writeUBOScalar(time,1);
        gl::glClear(gl::ClearBufferMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        buf1.render(36);
        glfwSwapBuffers(platform->controll_window);
        glfwPollEvents();
    } while (glfwGetKey(platform->controll_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
             glfwWindowShouldClose(platform->controll_window) == 0);
    ubo.disable();
    buf1.disable();
    buf1.clear();
    gl::glDeleteVertexArrays(1,&VAO);
    return 0;
}

