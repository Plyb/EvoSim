/*******************************************************************
** This code was adapted from Breakout on learnopengl.com
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "../Headers/ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "../Headers/stb_image.h"

// Instantiate static variables
std::map<std::string, Texture2D>    ResourceManager::textures;
std::map<std::string, Shader>       ResourceManager::shaders;
const char*                         ResourceManager::resourceRoot = "";

void ResourceManager::init() {
    stbi_set_flip_vertically_on_load(true);
}

void ResourceManager::setResourceRoot(const char* root) {
    resourceRoot = root;
}


Shader ResourceManager::loadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name) {
    std::string vShaderFileString = prependResourceRoot(vShaderFile);
    std::string fShaderFileString = prependResourceRoot(fShaderFile);
    std::string gShaderFileString;
    if (gShaderFile != nullptr) {
        gShaderFileString = prependResourceRoot(gShaderFile);
        gShaderFile = gShaderFileString.c_str();
    }

    shaders[name] = loadShaderFromFile(vShaderFileString.c_str(), fShaderFileString.c_str(), gShaderFile);
    return shaders[name];
}

std::string ResourceManager::prependResourceRoot(const char* path) {
    std::stringstream pathStream;
    pathStream << resourceRoot << path;
    return pathStream.str();
}

Shader ResourceManager::getShader(std::string name) {
    return shaders[name];
}

Texture2D ResourceManager::loadTexture(const char* file, bool alpha, std::string name) {
    std::string fileString = prependResourceRoot(file);

    textures[name] = loadTextureFromFile(fileString.c_str(), alpha);
    return textures[name];
}

Texture2D ResourceManager::getTexture(std::string name) {
    return textures.at(name);
}

void ResourceManager::clear() {
    // (properly) delete all shaders	
    for (auto iter : shaders)
        glDeleteProgram(iter.second.id);
    // (properly) delete all textures
    for (auto iter : textures)
        glDeleteTextures(1, &iter.second.id);
}

Shader ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile) {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try {
        // open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr) {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e) {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();
    // 2. now create shader object from source code
    Shader shader;
    shader.compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char* file, bool alpha) {
    // create texture object
    Texture2D texture;
    if (alpha) {
        texture.internalFormat = GL_RGBA;
        texture.imageFormat = GL_RGBA;
    }
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    // now generate texture
    texture.generate(width, height, data);
    // and finally free image data
    stbi_image_free(data);
    return texture;
}