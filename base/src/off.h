
#ifndef OFF_H
#define OFF_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>



typedef struct {
    float dimension[3];
} Vertex;
typedef struct {
    unsigned int vertrices[4];
} Faces;
typedef struct {
    float dimension[3];
} VertexNorm;

// PPM file structure type
struct OFF {
    Vertex * mVertex = nullptr;
    Faces * mFaces = nullptr;
    VertexNorm * mVertexNorm = nullptr;
    unsigned int nVertex;
    unsigned int nFace;
    unsigned int nEdge;
    char mType[3];
};

// Reads a OFF file from the disk.
OFF * loadPPM(const std::string & fileName) {
    std::ifstream imageFile;
    imageFile.open(fileName, std::fstream::in);

    if (!imageFile) {
        std::cout << "Error opening image file " << fileName << std::endl;
        return nullptr;
    }

    OFF * ppmImage = new OFF;

    imageFile >> ppmImage->mType;
    imageFile >> ppmImage->nVertex;
    imageFile >> ppmImage->nFace;
    imageFile >> ppmImage->nEdge;


    if (ppmImage->mVertex != nullptr) {
        delete ppmImage->mVertex;
    }
    if (ppmImage->mFaces != nullptr){
        delete ppmImage->mFaces;
    }

    ppmImage->mVertex = new Vertex[ppmImage->nVertex];
    ppmImage->mVertexNorm = new VertexNorm [ppmImage->nVertex];

    auto i = 0;
    while (i < (ppmImage->nVertex )) {
        float x, y, z;

        imageFile >> x;
        imageFile >> y;
        imageFile >> z;

        ppmImage->mVertex[i].dimension[0] = x;
        ppmImage->mVertex[i].dimension[1] = y;
        ppmImage->mVertex[i].dimension[2] = z;

        ++i;
    }

    ppmImage->mFaces = new Faces[ppmImage->nFace];

    auto j = 0;

    while (j < (ppmImage->nFace)) {
        unsigned int n, a, b, c;
        imageFile >> n;
        imageFile >> a;
        imageFile >> b;
        imageFile >> c;

        ppmImage->mFaces[j].vertrices[0] = n;
        ppmImage->mFaces[j].vertrices[1] = a;
        ppmImage->mFaces[j].vertrices[2] = b;
        ppmImage->mFaces[j].vertrices[3] = c;

        ++j;
    }

    imageFile.close();

    return ppmImage;
}

// Saves a PPM file.
void savePPM(const std::string & fileName, const OFF & ppmFile) {
    std::cout << "Saving file type off..." << std::endl;
    std::ofstream savePPMFile(fileName, std::ofstream::trunc);
    if (!savePPMFile) {
        std::cout << "Error opening image " << fileName << " to save." << std::endl;
        return;
    } else {
        savePPMFile << ppmFile.mType <<  std::endl;
        savePPMFile << ppmFile.nVertex << " " << ppmFile.nFace << std::endl;
        savePPMFile << ppmFile.nEdge << std::endl;
        for (auto i = 0; i < ppmFile.nVertex; ++i) {
            savePPMFile << static_cast<float>(ppmFile.mVertex[i].dimension[0]) << std::endl
                        << static_cast<float>(ppmFile.mVertex[i].dimension[1]) << std::endl
                        << static_cast<float>(ppmFile.mVertex[i].dimension[2]) << std::endl;
        }
        //TODO: add another to save the other half
        for (auto i = 0; i < ppmFile.nFace; ++i) {
            savePPMFile << static_cast<unsigned int>(ppmFile.mFaces[i].vertrices[0]) << std::endl;
            savePPMFile << static_cast<unsigned int>(ppmFile.mFaces[i].vertrices[1]) << std::endl;
            savePPMFile << static_cast<unsigned int>(ppmFile.mFaces[i].vertrices[2]) << std::endl;
        }
        savePPMFile.close();
    }
}

#endif