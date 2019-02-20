// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>


GLuint loadBMP_custom(const char * imagepath) {
    char header[54]; // BMP ファイルのヘッダーは54byte
    unsigned int dataPos;
    unsigned int width, height, imageSize;

    char * data;

    // ファイルを開いてチェック
    std::ifstream ifs(imagepath);

    if (!ifs.read(header, 54)) {
        std::cout << "Not a BMP file." << std::endl;
    }

    if (header[0] != 'B' || header[1] != 'M') {
        std::cout << "Not a BMP file." << std::endl;;
        return 0;
    }

    // ヘッダーから情報取得
    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);

    // BMPファイルがミスフォーマットの場合、その情報を推測
    if (!imageSize) imageSize = width * height * 3;
    if (dataPos = 0) dataPos = 54;

    // データの読み込み
    data = new char[imageSize];
    ifs.read(data, imageSize);
    ifs.close();

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return textureID;
}

