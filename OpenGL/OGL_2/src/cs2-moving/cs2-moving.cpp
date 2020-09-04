// Include GLEW - opengl extension wrangler
#include <GL/glew.h>

// Include GLFW -  graphics library framework
#include <GLFW/glfw3.h>
GLFWwindow *window;

// Include C++ standard headers
#include <iostream>
#include <random>
#include <chrono>

// Include C/C++ standard headers
#include <cstdlib>
#include <cmath>

void framebuffer_size_callback(GLFWwindow *window, const int width, const int height);
void process_input(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// vertex shader
const char *vertexShaderSource =
    "#version 330 core\n"

    "layout (location = 0) in vec2 pos;\n"
    "layout (location = 1) in vec2 vel;\n"
    "layout (location = 2) in vec3 col;\n"
    "layout (location = 3) in float ctime;\n"

    "uniform vec2 mypos;\n"
    "uniform float mytime;\n"

    "out vec4 fcol;\n"

    "void main()\n"
    "{\n"
    "    gl_Position.x = (pos.x - mypos.x) - (ctime - mytime) * (vel.x);\n"
    "    gl_Position.y = (pos.y - mypos.y) - (ctime - mytime) * (vel.y);\n"
    "    gl_Position.z = 0.0;\n"
    "    gl_Position.w = 1.0;\n"

    "    gl_Position.x = clamp(gl_Position.x,-2.0,2.0);\n"
    "    gl_Position.y = clamp(gl_Position.y,-2.0,2.0);\n"

    "    fcol = vec4(col.r, col.g, col.b, 1.0);\n"
    "}\n";

// fragment shader
const char *fragmentShaderSource =
    "#version 330 core\n"

    "in vec4 fcol;\n"

    "out vec4 frag_color;\n"

    "void main()\n"
    "{\n"
    "   frag_color = vec4(fcol);\n"
    "}\n";
    
int main(void) 
    // bad code : a big main function, don't copy in your code
    // we will write better code in future code snippets
{
    // glfw stuff

    // initialize and configure glfw
    // ------------------------------
    if (!glfwInit()) {
        std::cerr << "Failed to initialize glfw.\n";
        exit(EXIT_FAILURE);
    }
    // multisampling anti-aliasing (MSAA) 4x
    glfwWindowHint(GLFW_SAMPLES, 4);

    // opengl version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // opengl core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation

    std::cerr << "Creating windows.\n";

    GLFWwindow *window =
        glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
                         "OpenGL Code Snippets : More Triangles", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create glfw window." << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glew stuff

    // initialize glew
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize glew.\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // build and compile our shader program

    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Vertex shader compilation failed.\n"
                  << infoLog << std::endl;
    }

    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "fragment shader compilation failed.\n"
                  << infoLog << std::endl;
    }

    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Shade program linking failed.\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up chrono
    
    auto start = std::chrono::steady_clock::now();
    auto cur = std::chrono::steady_clock::now();
    std ::chrono::duration<float> cur_dur = cur - start;


    // set up random
    
    GLfloat rng_float(void);

    // set up vertices randomly

    enum { max_triads = 1000 };

    struct Buf_data {
        GLfloat pos[2];
        // GLfloat _pad1[2];
        GLfloat vel[2];
        // GLfloat _pad2[2];
        GLfloat col[3];
        // GLfloat _pad3[1];
        GLfloat ctime;
        GLfloat life;
        // GLfloat _pad4[2];
    };

    Buf_data vertices[max_triads * 3];

    // set up vertex data

    const GLfloat cross_dur = 60.0f;
    const GLfloat avg_life = 10.0f;
    const GLfloat sz_tri = 0.25f;


    for (auto i = 0; i < max_triads; i++) {

        GLfloat tx = rng_float()*6.0f - 3.0f;
        GLfloat ty = rng_float()*6.0f - 3.0f;

        GLfloat tr = rng_float();
        GLfloat tg = rng_float();
        GLfloat tb = rng_float();

        for (auto k = 0; k < 3; k++) {
            vertices[3*i+k].pos[0] = tx + rng_float()*sz_tri;
            vertices[3*i+k].pos[1] = ty + rng_float()*sz_tri;
            // vertices[3*i+k]._pad1[0] = 0.0f;
            // vertices[3*i+k]._pad1[1] = 0.0f;

            vertices[3*i+k].vel[0] = (rng_float() - 0.5f)*2.0f/cross_dur;
            vertices[3*i+k].vel[1] = (rng_float() - 0.5f)*2.0f/cross_dur;
            // vertices[3*i+k]._pad2[0] = 0.0f;
            // vertices[3*i+k]._pad2[1] = 0.0f;

            vertices[3*i+k].col[0] = tr + (rng_float() - 0.5)*0.75;
            vertices[3*i+k].col[1] = tg + (rng_float() - 0.5)*0.75;
            vertices[3*i+k].col[2] = tb + (rng_float() - 0.5)*0.75;
            // vertices[3*i+k]._pad3[0] = 0.0f;

            vertices[3*i+k].ctime = (GLfloat) cur_dur.count();
            vertices[3*i+k].life = rng_float()*avg_life;
            // vertices[3*i+k]._pad4[0] = 0.0f;
            // vertices[3*i+k]._pad4[1] = 0.0f;

            /*
            GLfloat * p = &vertices[3*i+k].pos[0];
            for (auto j = 0; j < 9; j++) {
                std::cerr << p[j] << ", ";
            }
            std::cerr << '\n';
            */
        }
    }


    // set up buffer(s) and configure vertex attributes

    GLuint vbo[1], vao[1];

    glGenVertexArrays(1, vao);
    glGenBuffers(1, vbo);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s),
    // and then configure vertex attributes(s).
    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Buf_data),
                          (GLvoid *)(offsetof(Buf_data,pos)));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Buf_data),
                          (GLvoid *)(offsetof(Buf_data,vel)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Buf_data),
                          (GLvoid *)(offsetof(Buf_data,col)));
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Buf_data),
                          (GLvoid *)(offsetof(Buf_data,ctime)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    // note that this is allowed, the call to glVertexAttribPointer registered
    // vbo as the vertex attribute's bound vertex buffer object so afterwards we
    // can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the vao afterwards so other vao calls won't accidentally
    // modify this vao, but this rarely happens. Modifying other vao requires a
    // call to glBindVertexArray anyways so we generally don't unbind vao (nor
    // vbo) when it's not directly necessary.
    glBindVertexArray(0);

    // set up uniforms

    GLfloat myposx = 0.0f, myposy = 0.0f;
    GLfloat myvelx, myvely;
    GLfloat mytime = 0.0f;

    GLint mypos_loc = glGetUniformLocation(shaderProgram, "mypos");
    GLint mytime_loc = glGetUniformLocation(shaderProgram, "mytime");

    myvelx = rng_float() * 2.0f - 1.0f;
    myvely = rng_float() * 2.0f - 1.0f;;

    // std::cerr << myvelx << ' ' << myvely << "\n";

    glUniform2f(mypos_loc,0.0f,0.0f);
    glUniform1f(mytime_loc,0.0f);

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    while (!glfwWindowShouldClose(window)) {
        // input
        process_input(window);

        // do some stuff

        cur = std::chrono::steady_clock::now();
        cur_dur = cur - start;
        
        GLfloat old_time = mytime;

        mytime = cur_dur.count();

        // std::cerr << mytime << '\n';

        glUniform1f(mytime_loc,mytime);

        GLfloat cur_posx = 0.0f, cur_posy = 0.0f;

        cur_posx = myposx + (mytime - old_time) * myvelx * 0.2f; 
        cur_posy = myposy + (mytime - old_time) * myvely * 0.2f; 

        if (cur_posx < -2.0f || cur_posx > 2.0f) myvely = 2.0f * rng_float() - 1.0f;
        if (cur_posy < -2.0f || cur_posy > 2.0f) myvelx = 2.0f * rng_float() - 1.0f;

        if (cur_posx > 2.0f) myvelx = - rng_float();
        if (cur_posx < -2.0f) myvelx = rng_float();

        if (cur_posy > 2.0f) myvely = - rng_float();
        if (cur_posy < -2.0f) myvely = rng_float();

        myposx = cur_posx;
        myposy = cur_posy;

        // std::cerr << myposx  << " " << myposy << '\n';

        glUniform2f(mypos_loc, myposx, myposy);

        // render
        glClearColor(0.085f, 0.13f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our triangles
        glUseProgram(shaderProgram);

        glBindVertexArray(vao[0]);
        glDrawArrays(GL_TRIANGLES, 0, max_triads * 3);  

        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse
        // moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, vao);
    glDeleteBuffers(1, vbo);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void process_input(GLFWwindow *window) 
    // process all input: query GLFW whether relevant keys are pressed/released this
    // frame and react accordingly
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, const int width, const int height) 
    // glfw: whenever the window size changed (by OS or user resize) this callback
    // function executes
{
    // make sure the viewport matches the new window dimensions; note that width
    // and height will be significantly larger than specified on retina
    // displays.
    glViewport(0, 0, width, height);
}

static std::random_device rd;
static std::mt19937 gen(rd());

GLfloat rng_float(void)
{
  std::uniform_real_distribution<GLfloat> dis(0.0f,1.0f);
  return dis(gen);
}
