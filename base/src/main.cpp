// This example is heavily based on the tutorial at https://open.gl
//TODO: Rotation: m, n.  Translation: w, a, s, d   Scale: j, k   Selection: o   Deselect: c
//TODO: FTGH, camera control (perspective), R, Y camera control(otho)
// Note: Sometime after program run, 2, 3 won't generate shape, in the case need to re-run to work
// Note: ******* If started without a shader, click object will resolve.
// Note: Multiple same objects will be generated with same key press with norm to be modified later.
#include "Helpers.h"
#include "off.h"
#include <iostream>
#include <array>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
// GLFW is necessary to handle the OpenGL context
#include <GLFW/glfw3.h>
#else
// GLFW is necessary to handle the OpenGL context
#include <GLFW/glfw3.h>
#endif

// OpenGL Mathematics Library
#include <glm/glm.hpp> // glm::vec3
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>

// Timer
#include <chrono>

// VertexBufferObject wrapper
VertexBufferObject VBOCube;
VertexBufferObject VBORabbit;
VertexBufferObject VBOBumpy;
VertexBufferObject VBOCubeNormal;
VertexBufferObject VBOBumpyNormal;
VertexBufferObject VBORabbitNormal;
VertexBufferObject VBOCubePhNormal;
VertexBufferObject VBORabbitPhNormal;
VertexBufferObject VBOBumpyPhNormal;


// Contains the vertex positions
std::vector<glm::vec3> Cube(36);
std::vector<glm::vec3> CubeNormal(36);
std::vector<glm::vec3> CubePhNormal(36);
std::vector<glm::vec3> VCube(36);
std::vector<glm::vec3> VCubeNormal(36);
std::vector<glm::vec3> VCubePhNormal(36);

std::vector<glm::vec3> Bumpy(1000 * 3);
std::vector<glm::vec3> BumpyNormal(1000 * 3);
std::vector<glm::vec3> BumpyPhNormal(1000 * 3);
std::vector<glm::vec3> VBumpy(1000 * 3);
std::vector<glm::vec3> VBumpyNormal(1000 * 3);
std::vector<glm::vec3> VBumpyPhNormal(1000 * 3);

std::vector<glm::vec3> Rabbit(1000 * 3);
std::vector<glm::vec3> RabbitNormal(1000 * 3);
std::vector<glm::vec3> RabbitPhNormal(1000 * 3);
std::vector<glm::vec3> VRabbit(1000 * 3);
std::vector<glm::vec3> VRabbitNormal(1000 * 3);
std::vector<glm::vec3> VRabbitPhNormal(1000 * 3);

std::vector<glm::mat4> modelsCube(1);
std::vector<glm::mat4> modelsRabbit(1);
std::vector<glm::mat4> modelsBumpy(1);
std::vector<glm::vec3> foundFaces;
std::vector<glm::vec3> colorsCube(1);
std::vector<glm::vec3> colorsBumpy(1);
std::vector<glm::vec3> colorsRabbit(1);


glm::mat4 Projection = glm::perspective(
        glm::radians(45.0f),
        4.0f / 3.0f,
        0.1f,
        100.0f
);


glm::mat4 View = glm::lookAt(
        glm::vec3(4,3,3),
        glm::vec3(0,0,0),
        glm::vec3(0,1,0)
);

//glm::mat4 View = glm::mat4(1.0f);
// note that we're translating the scene in the reverse direction of where we want to move



glm::mat4 rotation = glm::rotate(glm::mat4(1.0f),
                                 glm::radians(0.0f), glm::vec3(1.0f , 1.0f , 0.0f)) ;


glm::mat4 Model = glm::mat4(1.0f);


float scale = 3.0;
float scale1 = 0.1;
float dx, dy, dz;

glm::mat4 scaleMatrix{scale, 0, 0, 0,
                      0, scale, 0, 0,
                      0, 0, scale, 0,
                      0, 0, 0, 1};


glm::mat4 scaleMatrix1{scale1, 0, 0, 0,
                      0, scale1, 0, 0,
                      0, 0, scale1, 0,
                      0, 0, 0, 1};

glm::mat4 scaleUp{1.2, 0, 0, 0,
                       0, 1.2, 0, 0,
                       0, 0, 1.2, 0,
                       0, 0, 0, 1};
glm::mat4 scaleDown{0.8, 0, 0, 0,
                  0, 0.8, 0, 0,
                  0, 0, 0.8, 0,
                  0, 0, 0, 1};
glm::mat4 rotationZ{cos(0.174533), sin(0.174533), 0, 0,
                    -1*sin(0.174533), cos(0.174533), 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1};
glm::mat4 rotationZC{cos(-0.174533), sin(-0.174533), 0, 0,
                    -1*sin(-0.174533), cos(-0.174533), 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1};
glm::mat4 rotationY{-1*sin(0.174533), cos(0.174533), 0, 0,
                    0, 0, 0, 0,
                    cos(0.174533), sin(0.174533), 1, 0,
                    0, 0, 0, 1};
glm::mat4 rotationX{
    0, 0, 1, 0,
    cos(0.174533), sin(0.174533), 0, 0,
    -1*sin(0.174533), cos(0.174533), 0, 0,
    0, 0, 0, 1
};


glm::vec3 lightPos(-1.0f, 0.0f, 0.0f);
glm::vec3 cameraPos = glm::vec3(4,3,3);
glm::vec3 lightColor = glm::vec3(0.7f, 0.7f, 0.7f);
glm::vec3 colorTemp;
glm::vec3 ORIGIN_COLOR(0.7, 0.7, 0.7);
glm::vec3 centric(0, 0, 0);
glm::vec3 centricBumpy(0, 0, 0);
glm::vec3 centricCube(0, 0, 0);
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(-4.0f, -3.0f, -3.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);


bool phModeOn = false;
bool cubeSelected = false;
bool bumpySelected = false;
bool rabbitSelected = false;
bool initCube = true;
bool initRabbit = true;
bool initBumpy = true;
const float cameraSpeed = 0.05f;
float cameraX = 4, cameraY = 3, cameraZ = 3;
//std::vector<glm::vec3> VCu(8);
//std::vector<glm::vec3> cubeIndices(12);
//TODO: multiple objects


void print44matirx(glm::mat4x4 inMatrix){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            std::cout << inMatrix[i][j] << "   ";
        }
        std::cout << std::endl;
    }
}
glm::vec3 Barycenter(OFF* input) {
    glm::vec3 output;
    float xSum = 0.0;
    float ySum = 0.0;
    float zSum = 0.0;
    for (int i = 0; i < input->nVertex; i++){
        xSum += input->mVertex[i].dimension[0];
        ySum += input->mVertex[i].dimension[1];
        zSum += input->mVertex[i].dimension[2];
    }
    output.x = xSum/input->nVertex;
    output.y = ySum/input->nVertex;
    output.y = zSum/input->nVertex;
    return output;
}
float side(float x, float y, float s1x, float s1y, float s2x, float s2y)
{
    return (x - s2x) * (s1y - s2y) - (s1x - s2x) * (y - s2y);
}
bool inTriangle(float x,  float y, std::vector<glm::vec3> Vertrices)
{
    for (int i = 0; i < Vertrices.size(); i+=3){
        float a1, a2, a3;
        bool isNeg, isPos;
        a1 = side(x, y, Vertrices[i].x, Vertrices[i].y, Vertrices[i + 1].x, Vertrices[i + 1].y);
        a2 = side(x, y, Vertrices[i + 1].x, Vertrices[i + 1].y, Vertrices[i + 2].x, Vertrices[i + 2].y);
        a3 = side(x, y, Vertrices[i + 2].x, Vertrices[i + 2].y, Vertrices[i].x, Vertrices[i].y);
        isNeg = (a1 < 0) || (a2 < 0) || (a3 < 0);
        isPos = (a1 > 0) || (a2 > 0) || (a3 > 0);
        if (!(isNeg && isPos)){
            return true;
        }
    }
    return false;
}
glm::vec3 surfaceNormal (glm::vec3 a, glm::vec3 b, glm::vec3 c){
    glm::vec3 normal;
    glm::vec3 U = b - a;
    glm::vec3 V = c - a;
    normal.x = U.y * V.z - U.z * V.y;
    normal.y = U.z * V.x - U.x * V.z;
    normal.z = U.x * V.y - U.y * V.x;

    return normal;
}
glm::vec3 normalCalc (std::vector<glm::vec3> inFaces, int count){
    glm::vec3 total = glm::vec3(0, 0, 0);
    for (int i = 0; i< inFaces.size(); i++){
        total += inFaces[i];
    }
    total /= count;
    return total;
}
std::vector<glm::vec4> addHomo(std::vector<glm::vec3> inMatrix){
    std::vector<glm::vec4> outMatrix(inMatrix.size());
    for (int i = 0; i < inMatrix.size(); i++){
        outMatrix[i] = glm::vec4(inMatrix[i].x, inMatrix[i].y, inMatrix[i].z, 1.0f);
    }
    return outMatrix;
}

std::vector<glm::vec3> removeHomo(std::vector<glm::vec4> inMatrix){
    std::vector<glm::vec3> output(inMatrix.size());

    for (int i = 0; i < inMatrix.size(); i++){
        output[i].x = inMatrix[i].x / inMatrix[i].w;
        output[i].y = inMatrix[i].y / inMatrix[i].w;
        output[i].z = inMatrix[i].z / inMatrix[i].w;
    }

    return output;
}

void generateShapeNormal(OFF* inFile, std::vector<glm::vec3>& obj, std::vector<glm::vec3>& norm){
    int iFace = 0;
    for (int i = 0; i < obj.size(); i += 3){
        obj[i] = glm::vec3(inFile->mVertex[inFile->mFaces[iFace].vertrices[1]].dimension[0],
                               inFile->mVertex[inFile->mFaces[iFace].vertrices[1]].dimension[1],
                               inFile->mVertex[inFile->mFaces[iFace].vertrices[1]].dimension[2]);
        obj[i + 1] = glm::vec3(inFile->mVertex[inFile->mFaces[iFace].vertrices[2]].dimension[0],
                                   inFile->mVertex[inFile->mFaces[iFace].vertrices[2]].dimension[1],
                                   inFile->mVertex[inFile->mFaces[iFace].vertrices[2]].dimension[2]);
        obj[i + 2] = glm::vec3(inFile->mVertex[inFile->mFaces[iFace].vertrices[3]].dimension[0],
                                   inFile->mVertex[inFile->mFaces[iFace].vertrices[3]].dimension[1],
                                   inFile->mVertex[inFile->mFaces[iFace].vertrices[3]].dimension[2]);
        norm[i] = surfaceNormal(obj[i], obj[i + 1], obj[i + 2]);
        norm[i + 1] = surfaceNormal(obj[i], obj[i + 1], obj[i + 2]);
        norm[i + 2] = surfaceNormal(obj[i], obj[i + 1], obj[i + 2]);
        iFace += 1;
    }
}

void calcPhNorms (OFF* inFile, std::vector<glm::vec3> object, std::vector<glm::vec3> objectNorm){
    for (int i = 0; i < inFile->nVertex; i++){
        foundFaces.clear();
        for (int j = 0; j < object.size(); j++){
            if (inFile->mVertex[i].dimension[0] == object[j].x &&
                inFile->mVertex[i].dimension[1] == object[j].y &&
                inFile->mVertex[i].dimension[2] == object[j].z){
                foundFaces.push_back(objectNorm[j]);
            }
        }
        glm::vec3 temp = normalCalc(foundFaces, foundFaces.size());
        inFile->mVertexNorm[i].dimension[0] = temp.x;
        inFile->mVertexNorm[i].dimension[1] = temp.y;
        inFile->mVertexNorm[i].dimension[2] = temp.z;
    }
}

void generatePhNorm (OFF* inFile, std::vector<glm::vec3>& object){
    int iFace = 0;
    for (int i = 0; i < RabbitPhNormal.size(); i += 3){
        object[i] = glm::vec3(inFile->mVertexNorm[inFile->mFaces[iFace].vertrices[1]].dimension[0],
                                      inFile->mVertexNorm[inFile->mFaces[iFace].vertrices[1]].dimension[1],
                                      inFile->mVertexNorm[inFile->mFaces[iFace].vertrices[1]].dimension[2]);
        object[i + 1] = glm::vec3(inFile->mVertexNorm[inFile->mFaces[iFace].vertrices[2]].dimension[0],
                                          inFile->mVertexNorm[inFile->mFaces[iFace].vertrices[2]].dimension[1],
                                          inFile->mVertexNorm[inFile->mFaces[iFace].vertrices[2]].dimension[2]);
        object[i + 2] = glm::vec3(inFile->mVertexNorm[inFile->mFaces[iFace].vertrices[3]].dimension[0],
                                          inFile->mVertexNorm[inFile->mFaces[iFace].vertrices[3]].dimension[1],
                                          inFile->mVertexNorm[inFile->mFaces[iFace].vertrices[3]].dimension[2]);

        iFace += 1;
    }
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    // Get the position of the mouse in the window
    double xpos, ypos;

    glfwGetCursorPos(window, &xpos, &ypos);

    // Get the size of the window
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // Convert screen position to world coordinates
    double xworld = ((xpos/double(width))*2)-1;
    double yworld = (((height-1-ypos)/double(height))*2)-1; // NOTE: y axis is flipped in glfw

    // Update the position of the first vertex if the left button is pressed

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        if (inTriangle(xworld, yworld, VCube) && !initCube){
            std::cout << "clicked inside cube\n";
            colorTemp = colorsCube[0];
            colorsCube[0] = glm::vec3(1.0, 0.0, 0.0);
            cubeSelected = true;
            bumpySelected = false;
            rabbitSelected = false;
        }
        else if(inTriangle(xworld, yworld, VBumpy) && !initBumpy){
            std::cout << "clicked inside Bumpy\n";
            colorTemp = colorsBumpy[0];
            colorsBumpy[0] = glm::vec3(1.0, 0.0, 0.0);
            cubeSelected = false;
            bumpySelected = true;
            rabbitSelected = false;
        }
        else if(inTriangle(xworld, yworld, VRabbit) && !initRabbit){
            std::cout << "clicked inside Rabbit\n";
            colorTemp = colorsRabbit[0];
            colorsRabbit[0] = glm::vec3(1.0, 0.0, 0.0);
            cubeSelected = false;
            bumpySelected = false;
            rabbitSelected = true;
        }
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        std::cout << "mouse is released\n";
        colorsCube[0] = ORIGIN_COLOR;
        colorsBumpy[0] = ORIGIN_COLOR;
        colorsRabbit[0] = ORIGIN_COLOR;
    }

    // Upload the change to the GPU


}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Update the position of the first vertex if the keys 1,2, or 3 are pressed
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    float aspect_ratio = float(height)/float(width);

    switch (key)
    {
        case GLFW_KEY_1:
            if (action == GLFW_PRESS){
                if(initCube){
                    VCube.resize(Cube.size());
                    VCubeNormal.resize(CubeNormal.size());
                    VCubePhNormal.resize(CubePhNormal.size());
                    for (int i = 0; i < Cube.size(); i++) {
                        VCube[i] = Cube[i];
                        VCubeNormal[i] = CubeNormal[i];
                        VCubePhNormal[i] = CubePhNormal[i];
                        initCube = false;
                    }
                }
                else if(!initCube) {
                    for (int i = 0; i < Cube.size(); i++) {
                        VCube.push_back(Cube[i]);
                        VCubeNormal.push_back(CubeNormal[i]);
                        VCubePhNormal.push_back(CubePhNormal[i]);
                        modelsCube.push_back(glm::mat4 (1.0f));
                        colorsCube.push_back(glm::vec3(0.7, 0.7, 0.7));
                    }
                }
            }
            break;
        case GLFW_KEY_2:
            if (action == GLFW_PRESS){
                if(initBumpy){
                    VBumpy.resize(Bumpy.size());
                    VBumpyNormal.resize(BumpyNormal.size());
                    VBumpyPhNormal.resize(BumpyPhNormal.size());
                    for (int i = 0; i < Bumpy.size(); i++) {
                        VBumpy[i] = Bumpy[i];
                        VBumpyNormal[i] = BumpyNormal[i];
                        VBumpyPhNormal[i] = BumpyPhNormal[i];
                        initBumpy = false;
                    }
                }
                else if(!initBumpy) {
                    for (int i = 0; i < Bumpy.size(); i++) {
                        VBumpy.push_back(Bumpy[i]);
                        VBumpyNormal.push_back(BumpyNormal[i]);
                        VBumpyPhNormal.push_back(BumpyPhNormal[i]);
                        modelsBumpy.push_back(glm::mat4 (1.0f));
                        colorsBumpy.push_back(glm::vec3(0.7, 0.7, 0.7));
                    }
                }
            }
            break;
        case GLFW_KEY_3:
            if (action == GLFW_PRESS){
                if(initRabbit){
                    VRabbit.resize(Rabbit.size());
                    VRabbitNormal.resize(RabbitNormal.size());
                    VRabbitPhNormal.resize(RabbitPhNormal.size());
                    for (int i = 0; i < Bumpy.size(); i++) {
                        VRabbit[i] = Rabbit[i];
                        VRabbitNormal[i] = RabbitNormal[i];
                        VRabbitPhNormal[i] = RabbitPhNormal[i];
                        initRabbit = false;
                    }
                }
                else if(!initRabbit) {
                    for (int i = 0; i < Rabbit.size(); i++) {
                        VRabbit.push_back(Rabbit[i]);
                        VRabbitNormal.push_back(RabbitNormal[i]);
                        VRabbitPhNormal.push_back(RabbitPhNormal[i]);
                        modelsRabbit.push_back(glm::mat4 (1.0f));
                        colorsRabbit.push_back(glm::vec3(0.7, 0.7, 0.7));
                    }
                }
            }
            break;
        case GLFW_KEY_K:
            if (action == GLFW_PRESS){
                if (cubeSelected){
                    modelsCube[0] = modelsCube[0] * scaleUp;
                }
                else if(rabbitSelected){
                    modelsRabbit[0] = modelsRabbit[0] * scaleUp;
                }
                else if(bumpySelected){
                    modelsBumpy[0] = modelsBumpy[0] * scaleUp;
                }
            }
            break;

        case GLFW_KEY_J:
            if (action == GLFW_PRESS) {
                if (cubeSelected) {
                    modelsCube[0] = modelsCube[0] * scaleDown;
                } else if (rabbitSelected) {
                    modelsRabbit[0] = modelsRabbit[0] * scaleDown;
                } else if (bumpySelected) {
                    modelsBumpy[0] = modelsBumpy[0] * scaleDown;
                }
            }
            break;

        case GLFW_KEY_U:
            if (action == GLFW_PRESS){
                glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
            }
            break;

        case GLFW_KEY_I:
            if (action == GLFW_PRESS){
                glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
            }
            break;

        case GLFW_KEY_P:
            if (action == GLFW_PRESS){
                if(phModeOn){
                    phModeOn = false;
                }
                else if(!phModeOn){
                    phModeOn = true;
                }
            }
            break;
        case GLFW_KEY_C:
            if (action == GLFW_PRESS){
                cubeSelected = false;
                bumpySelected = false;
                rabbitSelected = false;
            }
            break;
        /*
        case GLFW_KEY_O:
            if (action == GLFW_PRESS) {
                glfwSetMouseButtonCallback(window, mouse_button_callback_o);
            }
            break;
            */
        case GLFW_KEY_N:
            if (action == GLFW_PRESS) {
                if (cubeSelected){
                    modelsCube[0] = modelsCube[0] * rotationZ;
                }
                else if(rabbitSelected){
                    modelsRabbit[0] = modelsRabbit[0] * rotationZ;
                }
                else if(bumpySelected){
                    modelsBumpy[0] = modelsBumpy[0] * rotationZ;
                }
            }
            break;
        case GLFW_KEY_M:
            if (action == GLFW_PRESS) {
                if (cubeSelected){
                    modelsCube[0] = modelsCube[0] * rotationZC;
                }
                else if(rabbitSelected){
                    modelsRabbit[0] = modelsRabbit[0] * rotationZC;
                }
                else if(bumpySelected){
                    modelsBumpy[0] = modelsBumpy[0] * rotationZC;
                }
            }
            break;
        case GLFW_KEY_W:
            if (action == GLFW_PRESS) {
                std::cout << cubeSelected << " " << bumpySelected << " " << rabbitSelected << std::endl;
                if (cubeSelected){
                    glm::mat4 translation{1, 0, 0, 0,
                                          0, 1, 0, 0,
                                          0, 0, 1, 0,
                                          0, 0.2, 0, 1};
                    modelsCube[0] = modelsCube[0] * translation;
                    centric.x += dx;
                    centric.y += dy;
                }
                else if(bumpySelected){
                    glm::mat4 translation{1, 0, 0, 0,
                                          0, 1, 0, 0,
                                          0, 0, 1, 0,
                                          0, 0.2, 0, 1};
                    modelsBumpy[0] = modelsBumpy[0] * translation;
                    centric.x += dx;
                    centric.y += dy;
                }
                else if(rabbitSelected){
                    glm::mat4 translation{1, 0, 0, 0,
                                          0, 1, 0, 0,
                                          0, 0, 1, 0,
                                          0, 0.2, 0, 1};
                    modelsRabbit[0] = modelsRabbit[0] * translation;
                    centric.x += dx;
                    centric.y += dy;
                }

            }
            break;
        case GLFW_KEY_S:
            if (action == GLFW_PRESS) {
                if (cubeSelected){
                    glm::mat4 translation{1, 0, 0, 0,
                                          0, 1, 0, 0,
                                          0, 0, 1, 0,
                                          0, -0.2, 0, 1};
                    modelsCube[0] = modelsCube[0] * translation;

                }
                else if(rabbitSelected){
                    glm::mat4 translation{1, 0, 0, 0,
                                          0, 1, 0, 0,
                                          0, 0, 1, 0,
                                          0, -0.2, 0, 1};
                    modelsRabbit[0] = modelsRabbit[0] * translation;

                }
                else if(bumpySelected){
                    glm::mat4 translation{1, 0, 0, 0,
                                          0, 1, 0, 0,
                                          0, 0, 1, 0,
                                          0, -0.2, 0, 1};
                    modelsBumpy[0] = modelsBumpy[0] * translation;

                }
            }
            break;
        case GLFW_KEY_A:
            if (action == GLFW_PRESS) {
                if (cubeSelected){
                    glm::mat4 translation{1, 0, 0, 0,
                                          0, 1, 0, 0,
                                          0, 0, 1, 0,
                                          -0.2, 0, 0, 1};
                    modelsCube[0] = modelsCube[0] * translation;

                }
                else if(rabbitSelected){
                    glm::mat4 translation{1, 0, 0, 0,
                                          0, 1, 0, 0,
                                          0, 0, 1, 0,
                                          -0.2, 0, 0, 1};
                    modelsRabbit[0] = modelsRabbit[0] * translation;

                }
                else if(bumpySelected){
                    glm::mat4 translation{1, 0, 0, 0,
                                          0, 1, 0, 0,
                                          0, 0, 1, 0,
                                          -0.2, 0, 0, 1};
                    modelsBumpy[0] = modelsBumpy[0] * translation;

                }
            }
            break;
        case GLFW_KEY_D:
            if (action == GLFW_PRESS) {
                if (cubeSelected){
                    glm::mat4 translation{1, 0, 0, 0,
                                          0, 1, 0, 0,
                                          0, 0, 1, 0,
                                          0.2, 0, 0, 1};
                    modelsCube[0] = modelsCube[0] * translation;
                    centric.x += dx;
                    centric.y += dy;
                }
                else if(rabbitSelected){
                    glm::mat4 translation{1, 0, 0, 0,
                                          0, 1, 0, 0,
                                          0, 0, 1, 0,
                                          0.2, 0, 0, 1};
                    modelsRabbit[0] = modelsRabbit[0] * translation;
                    centric.x += dx;
                    centric.y += dy;
                }
                else if(bumpySelected){
                    glm::mat4 translation{1, 0, 0, 0,
                                          0, 1, 0, 0,
                                          0, 0, 1, 0,
                                          0.2, 0, 0, 1};
                    modelsBumpy[0] = modelsBumpy[0] * translation;
                    centric.x += dx;
                    centric.y += dy;
                }
            }
            break;
        case GLFW_KEY_F:
            if (action == GLFW_PRESS) {
                const float moveSpeed = 0.5;
                cameraX += moveSpeed;
                //float cameraX, cameraY, cameraZ;
                View = glm::lookAt(
                        glm::vec3(cameraX,cameraY,cameraZ),
                        glm::vec3(0,0,0),
                        glm::vec3(0,1,0)
                );
            }
            break;
        case GLFW_KEY_H:
            if (action == GLFW_PRESS) {
                const float moveSpeed = 0.5;
                cameraX -= moveSpeed;
                //float cameraX, cameraY, cameraZ;
                View = glm::lookAt(
                        glm::vec3(cameraX,cameraY,cameraZ),
                        glm::vec3(0,0,0),
                        glm::vec3(0,1,0)
                );
            }
            break;
        case GLFW_KEY_T:
            if (action == GLFW_PRESS) {
                cameraPos += cameraSpeed * cameraFront;
                View = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
            }
            break;
        case GLFW_KEY_G:
            if (action == GLFW_PRESS) {
                cameraPos -= cameraSpeed * cameraFront;
                View = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
            }
            break;
        case GLFW_KEY_R:
            if (action == GLFW_PRESS) {
                cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
                View = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
            }
            break;
        case GLFW_KEY_Y:
            if (action == GLFW_PRESS) {
                cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
                View = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
            }
            break;
        case GLFW_KEY_B:
            if (action == GLFW_PRESS) {
                if (cubeSelected) {
                    if (VCube.size() == Cube.size()) {
                        VCube.clear();
                        VCubeNormal.clear();
                        VCubePhNormal.clear();
                        VCube.resize(Cube.size());
                        VCubeNormal.resize(Cube.size());
                        VCubePhNormal.resize(Cube.size());
                        initCube = true;
                    } else {
                        VCube.resize(VCube.size() - Cube.size());
                        VCubeNormal.resize(VCubeNormal.size() - CubeNormal.size());
                        VCubePhNormal.resize(VCubePhNormal.size() - CubePhNormal.size());
                    }
                    //std::cout << VCube.size() << std::endl;
                }

                if (bumpySelected) {
                    if (VBumpy.size() == Bumpy.size()) {
                        VBumpy.clear();
                        VBumpyNormal.clear();
                        VBumpyPhNormal.clear();
                        VBumpy.resize(Bumpy.size());
                        VBumpyNormal.resize(Bumpy.size());
                        VBumpyPhNormal.resize(Bumpy.size());
                        initBumpy = true;
                    } else {
                        VBumpy.resize(VBumpy.size() - Bumpy.size());
                        VBumpyNormal.resize(VBumpyNormal.size() - BumpyNormal.size());
                        VBumpyPhNormal.resize(VBumpyPhNormal.size() - BumpyPhNormal.size());

                    }
                }

                if (rabbitSelected) {
                    if (VRabbit.size() == Rabbit.size()) {
                        VRabbit.clear();
                        VRabbitNormal.clear();
                        VRabbitPhNormal.clear();
                        VRabbit.resize(Rabbit.size());
                        VRabbitNormal.resize(Rabbit.size());
                        VRabbitPhNormal.resize(Rabbit.size());
                        initRabbit = true;
                    } else {
                        VRabbit.resize(VRabbit.size() - VRabbit.size());
                        VRabbitNormal.resize(VRabbitNormal.size() - RabbitNormal.size());
                        VRabbitPhNormal.resize(VRabbitPhNormal.size() - RabbitPhNormal.size());
                    }
                }
            }
            break;

        case GLFW_KEY_8:
            if (action == GLFW_PRESS) {
                cubeSelected = true;
                rabbitSelected = false;
                bumpySelected = false;
                colorTemp = colorsCube[0];
                colorsCube[0] = glm::vec3(1.0, 0.0, 0.0);
            }
            else if(action == GLFW_RELEASE){
                colorsCube[0] = ORIGIN_COLOR;
            }
            break;
        case GLFW_KEY_9:
            if (action == GLFW_PRESS) {
                cubeSelected = false;
                rabbitSelected = false;
                bumpySelected = true;
                colorTemp = colorsBumpy[0];
                colorsBumpy[0] = glm::vec3(1.0, 0.0, 0.0);
            }
            else if(action == GLFW_RELEASE){
                colorsBumpy[0] = ORIGIN_COLOR;
            }
            break;
        case GLFW_KEY_0:
            if (action == GLFW_PRESS) {
                cubeSelected = false;
                rabbitSelected = true;
                bumpySelected = false;
                colorTemp = colorsRabbit[0];
                colorsRabbit[0] = glm::vec3(1.0, 0.0, 0.0);
            }
            else if(action == GLFW_RELEASE){
                colorsRabbit[0] = ORIGIN_COLOR;
            }
            break;

        default:
            break;
    }

    // Upload the change to the GPU
    VBOCube.update(VCube);
    VBOCubeNormal.update(VCubeNormal);
    VBOCubePhNormal.update(VCubePhNormal);

    VBOBumpy.update(VBumpy);
    VBOBumpyNormal.update(VBumpyNormal);
    VBOBumpyPhNormal.update(VBumpyPhNormal);

    VBORabbit.update(VRabbit);
    VBORabbitNormal.update(VRabbitNormal);
    VBORabbitPhNormal.update(VRabbitPhNormal);

}


int main(void)
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
        return -1;

    // Activate supersampling
    glfwWindowHint(GLFW_SAMPLES, 8);

    // Ensure that we get at least a 3.2 context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    // On apple we have to load a core profile with forward compatibility
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

#ifndef __APPLE__
    glewExperimental = true;
    GLenum err = glewInit();
    if(GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    glGetError(); // pull and savely ignonre unhandled errors like GL_INVALID_ENUM
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif

    int major, minor, rev;
    major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
    minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
    rev = glfwGetWindowAttrib(window, GLFW_CONTEXT_REVISION);
    printf("OpenGL version recieved: %d.%d.%d\n", major, minor, rev);
    printf("Supported OpenGL is %s\n", (const char*)glGetString(GL_VERSION));
    printf("Supported GLSL is %s\n", (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

    //off file read
    OFF* inFile = loadPPM("../data/bunny.off");
    OFF* inFile2 = loadPPM("../data/bumpy_cube.off");
    // Initialize the VAO
    // A Vertex Array Object (or VAO) is an object that describes how the vertex
    // attributes are stored in a Vertex Buffer Object (or VBO). This means that
    // the VAO is not the actual object storing the vertex data,
    // but the descriptor of the vertex data.
    VertexArrayObject VAO;
    VAO.init();
    VAO.bind();

    // Initialize the VBO with the vertices data
    // A VBO is a data container that lives in the GPU memory
    //TODO: DON'T FORGET TO INIT NEW VBOs
    VBOCube.init();
    VBORabbit.init();
    VBOBumpy.init();
    VBOCubeNormal.init();
    VBOCubePhNormal.init();
    VBOBumpyNormal.init();
    VBOBumpyPhNormal.init();
    VBORabbitNormal.init();
    VBORabbitPhNormal.init();

    //View = glm::translate(View, glm::vec3(0.0f, 0.0f, -3.0f));

    // Vertex Coordinates
    Cube.resize(36);
    //data for the cube
    float cubeSide = 0.5f;
    //front 1
    Cube[0] = glm::vec3(cubeSide, cubeSide, cubeSide);
    Cube[1] = glm::vec3(-1 * cubeSide, cubeSide, cubeSide);
    Cube[2] = glm::vec3(cubeSide, -1 * cubeSide, cubeSide);

    //front 2
    Cube[3] = glm::vec3(-1 * cubeSide, cubeSide, cubeSide);
    Cube[4] = glm::vec3(-1 * cubeSide, -1 * cubeSide, cubeSide);
    Cube[5] = glm::vec3(cubeSide, -1 * cubeSide, cubeSide);

    //back 1
    Cube[6] = glm::vec3(cubeSide, cubeSide, -1 * cubeSide);
    Cube[7] = glm::vec3(-1 * cubeSide, -1 * cubeSide, -1 * cubeSide);
    Cube[8] = glm::vec3(-1 * cubeSide, cubeSide, -1 * cubeSide);

    //back 2
    Cube[9] = glm::vec3(cubeSide, cubeSide, -1 * cubeSide);
    Cube[10] = glm::vec3(cubeSide, -1 * cubeSide, -1 * cubeSide);
    Cube[11] = glm::vec3(-1 * cubeSide, -1 * cubeSide, -1 * cubeSide);

    //top 1
    Cube[12] = glm::vec3(cubeSide, cubeSide, cubeSide);
    Cube[13] = glm::vec3(cubeSide, cubeSide, -1 * cubeSide);
    Cube[14] = glm::vec3(-1 * cubeSide, cubeSide, -1 * cubeSide);

    //top 2
    Cube[15] = glm::vec3(cubeSide, cubeSide, cubeSide);
    Cube[16] = glm::vec3(-1 * cubeSide, cubeSide, -1 * cubeSide);
    Cube[17] = glm::vec3(-1 * cubeSide, cubeSide, cubeSide);

    //down 1
    Cube[18] = glm::vec3(cubeSide, -1 * cubeSide, cubeSide);
    Cube[19] = glm::vec3(-1 * cubeSide, -1 * cubeSide, -1 * cubeSide);
    Cube[20] = glm::vec3(cubeSide, -1 * cubeSide, -1 * cubeSide);

    //down 2
    Cube[21] = glm::vec3(cubeSide, -1 * cubeSide, cubeSide);
    Cube[22] = glm::vec3(-1 * cubeSide, -1 * cubeSide, cubeSide);
    Cube[23] = glm::vec3(-1 * cubeSide, -1 * cubeSide, -1 * cubeSide);

    //left 1
    Cube[24] = glm::vec3(-1 * cubeSide, -1 * cubeSide, -1 * cubeSide);
    Cube[25] = glm::vec3(-1 * cubeSide, cubeSide, cubeSide);
    Cube[26] = glm::vec3(-1 * cubeSide, cubeSide, -1 * cubeSide);

    //left 2
    Cube[27] = glm::vec3(-1 * cubeSide, -1 * cubeSide, -1 * cubeSide);
    Cube[28] = glm::vec3(-1 * cubeSide, -1 * cubeSide, cubeSide);
    Cube[29] = glm::vec3(-1 * cubeSide, cubeSide, cubeSide);

    //right 1
    Cube[30] = glm::vec3(cubeSide, cubeSide, cubeSide);
    Cube[31] = glm::vec3(cubeSide, -1 * cubeSide, -1 * cubeSide);
    Cube[32] = glm::vec3(cubeSide, cubeSide, -1 * cubeSide);

    //right 2
    Cube[33] = glm::vec3(cubeSide, -1 * cubeSide, -1 * cubeSide);
    Cube[34] = glm::vec3(cubeSide, cubeSide, cubeSide);
    Cube[35] = glm::vec3(cubeSide, -1 * cubeSide, cubeSide);


    //put in all rabbit vertex values.
    Rabbit.resize(3000);
    RabbitNormal.resize(3000);
    RabbitPhNormal.resize(3000);
    generateShapeNormal(inFile, Rabbit, RabbitNormal);
    //Calculate ph vertex normal
    calcPhNorms(inFile, Rabbit, RabbitNormal);
    //Assign and fomulate ph normal
    generatePhNorm(inFile, RabbitPhNormal);

    Bumpy.resize(3000);
    BumpyNormal.resize(3000);
    BumpyPhNormal.resize(3000);
    generateShapeNormal(inFile2, Bumpy, BumpyNormal);
    calcPhNorms(inFile2, Bumpy, BumpyNormal);
    generatePhNorm(inFile2, BumpyPhNormal);


    centric = Barycenter(inFile);
    centricBumpy = Barycenter(inFile2);


    //translate to center and normalize
    for (int i = 0; i < inFile->nFace * 3; i++){
        Rabbit[i].x -= centric.x;
        Rabbit[i].y -= centric.y;
        Rabbit[i].z -= centric.z;
    }
    for (int i = 0; i < inFile2->nFace * 3; i++){
        Bumpy[i].x -= centricBumpy.x;
        Bumpy[i].y -= centricBumpy.y;
        Bumpy[i].z -= centricBumpy.z;
    }
    //Resize (normalize two shapes)
    std::vector<glm::vec4> tempRabbit = addHomo(Rabbit);
    for (int i = 0; i < tempRabbit.size(); i++){
        tempRabbit[i] = tempRabbit[i] * scaleMatrix;
    }
    Rabbit = removeHomo(tempRabbit);
    std::vector<glm::vec4> tempBumpy = addHomo(Bumpy);
    for (int i = 0; i < tempBumpy.size(); i++){
        tempBumpy[i] = tempBumpy[i] * scaleMatrix1;
    }
    Bumpy = removeHomo(tempBumpy);


    //calculations done
    modelsCube[0] = glm::mat4(1.0f);
    modelsBumpy[0] = glm::mat4(1.0f);
    modelsRabbit[0] = glm::mat4(1.0f);

    //calculate cube normal

    for (int i = 0; i < Cube.size(); i+=3){
        glm::vec3 normTemp = surfaceNormal(Cube[i], Cube[i + 1], Rabbit[i + 2]);
        CubeNormal[i] = normTemp;
        CubeNormal[i + 1] = normTemp;
        CubeNormal[i + 2] = normTemp;
    }

    std::vector<glm::vec3> cubeFaces;
    std::vector<int> vertexIndex;
    for (int i = 0; i < Cube.size(); i++){
        cubeFaces.clear();
        vertexIndex.clear();
        glm::vec3 total(0, 0, 0);
        for (int j = 0; j < Cube.size(); j++){
            if (Cube[j] == Cube[i]){
                cubeFaces.push_back(CubeNormal[j]);
                vertexIndex.push_back(j);
                total += CubeNormal[j];
            }
        }
        glm::vec3 tempNorm = normalCalc(cubeFaces, cubeFaces.size());
        for (int k = 0; k < vertexIndex.size(); k++){
            CubePhNormal[vertexIndex[k]] = tempNorm;
        }
    }


    colorsCube[0] = glm::vec3(0.7, 0.7, 0.7);
    colorsCube[1] = glm::vec3(0.7, 0.7, 0.7);
    colorsCube[2] = glm::vec3(0.7, 0.7, 0.7);


    VBOCube.update(VCube);
    VBOCubeNormal.update(VCubeNormal);
    VBOCubePhNormal.update(VCubePhNormal);

    VBOBumpy.update(VBumpy);
    VBOBumpyNormal.update(VBumpyNormal);
    VBOBumpyPhNormal.update(VBumpyPhNormal);

    VBORabbit.update(VRabbit);
    VBORabbitNormal.update(VRabbitNormal);
    VBORabbitPhNormal.update(VRabbitPhNormal);

    Program program;
    const GLchar* vertex_shader =
            "#version 150 core\n"
            "in vec3 position;"
            "in vec3 rNormal;"
            "uniform mat4 model;"
            "uniform mat4 view;"
            "uniform mat4 proj;"
            "out vec3 FragPos;"
            "out vec3 Normal;"

            "void main()"
            "{"
            "    gl_Position = proj * view * model * vec4(position, 1.0);"
            "    FragPos = vec3(model * vec4(position, 1.0));"
            "    Normal = mat3(transpose(inverse(model))) * rNormal;"
            "}";
    const GLchar* fragment_shader =
            "#version 150 core\n"
            "in vec3 Normal;"
            "in vec3 FragPos;"
            "out vec4 outColor;"
            "uniform vec3 lightPos;"
            "uniform vec3 lightColor;"
            "uniform vec3 viewPos;"
            "uniform vec3 color;"
            "void main()"
            "{"
            "    float ambientStr = 0.1f;"
            "    float specularStr = 0.5f;"
            "    float diffuseStr = 0.5f;"
            "    vec3 ambient = ambientStr * lightColor;"
            "    vec3 norm = normalize(Normal);"
            "    vec3 viewDir = normalize(viewPos - FragPos);"
            "    vec3 lDirection = normalize(lightPos - FragPos);"
            "    vec3 reflectDir = reflect(-lDirection, norm);"
            "    vec3 diffuse = diffuseStr * max(dot(norm, lDirection), 0.0) * lightColor;"
            "    vec3 specular = specularStr * pow(max(dot(viewDir, reflectDir), 0.0), 32) * lightColor;"
            "    vec3 finalResult = ( ambientStr + diffuse + specular) * color;"
            "    outColor = vec4(finalResult, 1.0f);"
            "}";

    program.init(vertex_shader,fragment_shader,"outColor");
    program.bind();

    // Register the keyboard callback
    glfwSetKeyCallback(window, key_callback);

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    // Update viewport
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Bind your program
    program.bind();
    //glEnable(GL_DEPTH_TEST);
    glUniformMatrix4fv(program.uniform("proj"), 1, GL_FALSE, glm::value_ptr(Projection));
    glUniform3f(program.uniform("lightColor"), lightColor.x, lightColor.y, lightColor.z);
    glUniform3f(program.uniform("lightPos"), lightPos.x, lightPos.y, lightPos.z);

    //debug only
    std::cout << "rabbit data sample: " << Rabbit[5].x << std::endl;
    std::cout << "bumpy sample: " << Bumpy[5].x << std::endl;

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {

        // Bind your VAO (not necessary if you have only one)
        VAO.bind();

        // Bind your program
        program.bind();


        glUniformMatrix4fv(program.uniform("model"), 1, GL_FALSE, glm::value_ptr(Model));
        glUniformMatrix4fv(program.uniform("view"), 1, GL_FALSE, glm::value_ptr(View));

        //glUniform3f(program.uniform("viewPos"), cameraPosition.x, cameraPosition.y, cameraPosition.z);

        // Clear the framebuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        program.bindVertexAttribArray("position", VBOCube);
        program.bindVertexAttribArray("rNormal", VBOCubeNormal);
        glUniform3f(program.uniform("color"), colorsCube[0].x, colorsCube[0].y, colorsCube[0].z);
        Model = modelsCube[0];
        glUniformMatrix4fv(program.uniform("model"), 1, GL_FALSE, glm::value_ptr(Model));
        if (phModeOn){
            program.bindVertexAttribArray("rNormal", VBOCubePhNormal);
        }
        else{
            program.bindVertexAttribArray("rNormal", VBOCubeNormal);
        }
        glDrawArrays(GL_TRIANGLES, 0, VCube.size());



        program.bindVertexAttribArray("position", VBORabbit);
        glUniform3f(program.uniform("color"), colorsRabbit[0].x, colorsRabbit[0].y, colorsRabbit[0].z);
        Model = modelsRabbit[0];
        glUniformMatrix4fv(program.uniform("model"), 1, GL_FALSE, glm::value_ptr(Model));
        if (phModeOn){
            program.bindVertexAttribArray("rNormal", VBORabbitPhNormal);
        }
        else{
            program.bindVertexAttribArray("rNormal", VBORabbitNormal);
        }
        glDrawArrays(GL_TRIANGLES, 0, VRabbit.size());



        program.bindVertexAttribArray("position", VBOBumpy);
        if (phModeOn){
            program.bindVertexAttribArray("rNormal", VBOBumpyPhNormal);
        }
        else{
            program.bindVertexAttribArray("rNormal", VBOBumpyNormal);
        }
        glUniform3f(program.uniform("color"), colorsBumpy[0].x, colorsBumpy[0].y, colorsBumpy[0].z);
        Model = modelsBumpy[0];
        glUniformMatrix4fv(program.uniform("model"), 1, GL_FALSE, glm::value_ptr(Model));
        glDrawArrays(GL_TRIANGLES, 0, VBumpy.size());


        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }

    // Deallocate opengl memory
    program.free();
    VAO.free();
    VBOCube.free();
    VBOCubePhNormal.free();
    VBOCubeNormal.free();
    VBOBumpy.free();
    VBOBumpyNormal.free();
    VBOBumpyPhNormal.free();
    VBORabbit.free();
    VBORabbitNormal.free();
    VBORabbitPhNormal.free();


    // Deallocate glfw internals
    glfwTerminate();
    return 0;
}
