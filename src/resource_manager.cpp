#include "resource_manager.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

#include "stb_image.h"

// Instantiate static variables
std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;


Shader& ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    Shader& tmp = Shaders[name];
    return tmp;
}

Shader& ResourceManager::GetShader(std::string name)
{
    Shader& tmp = Shaders[name];
    return tmp;
}

Texture2D ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

void ResourceManager::Clear()
{
    // (Properly) delete all shaders	
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    // (Properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    // Open files
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;
    // 设置ifstream对象可以抛出异常：
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::stringstream vShaderStream, fShaderStream;
    try
    {
        vertexShaderFile.open(vShaderFile);
        fragmentShaderFile.open(fShaderFile);
        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // If geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    const GLchar *gShaderCode = geometryCode.c_str();
    // 2. Now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const GLchar *img_file_path, GLboolean alpha)
{
    // Create Texture object
    Texture2D texture;
    // load and generate the texture
    int width, height, nrChannels;
    // 翻转Y轴
    // stbi_set_flip_vertically_on_load(true);
    unsigned char *image_data = stbi_load(img_file_path, &width, &height, &nrChannels, 0);
    if (image_data)
    {
        if(nrChannels==4) // rgba四通道图像
            {
                texture.Internal_Format = GL_RGBA;
                texture.Image_Format = GL_RGBA;
            }
        texture.Generate(width, height, image_data);
    }
    else
    {
        std::cout << "Failed to load texture: " << img_file_path << std::endl;
    }
    // 纹理已经绑定了图片，可以释放图片资源了。
    stbi_image_free(image_data);

    return texture;
}

