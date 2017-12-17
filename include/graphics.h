//
// Created by lopaidev on 17.12.17.
//

#ifndef LOGICON_GRAPHICS_H
#define LOGICON_GRAPHICS_H

#include <GL/gl.h>

#include <IL/il.h>

namespace Logicon {

    struct Texture {
        GLuint textureId;
        ILint width, height;
    };

    Texture load_texture(const char* filename);

};

#endif //LOGICON_GRAPHICS_H
