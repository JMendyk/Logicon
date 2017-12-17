//
// Created by lopaidev on 17.12.17.
//

#include "graphics.h"

#include <iostream> // for error printing

#include <IL/ilu.h>


namespace Logicon {

    Texture load_texture(const char* filename) {
        /*
         * Based on: https://r3dux.org/tag/ilutglloadimage/
         */

        Texture loaded_texture;

        ILuint il_texture_id;
        ilGenImages(1, &il_texture_id);
        ilBindImage(il_texture_id);

        if (!ilLoadImage(filename)) {
            ILenum error = ilGetError();
            std::cerr << "Image load failed - IL reports error: "
                      << error << " - " << iluErrorString(error) << std::endl;
            exit(-1);
        }

        // If the image is flipped (i.e. upside-down and mirrored, flip it the right way up!)
        ILinfo ImageInfo;
        iluGetImageInfo(&ImageInfo);
        if (ImageInfo.Origin == IL_ORIGIN_LOWER_LEFT) {
            iluFlipImage();
        }

        // Convert the image into a suitable format to work with
        // NOTE: If your image contains alpha channel you can replace IL_RGB with IL_RGBA
        // Quit out if we failed the conversion
        if (!ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE)) {
            ILenum error = ilGetError();
            std::cerr << "Image conversion failed - IL reports error: "
                      << error << " - " << iluErrorString(error) << "\n";
            exit(-1);
        }

        // Generate a new texture
        glGenTextures(1, &loaded_texture.textureId);

        GLuint target = GL_TEXTURE_2D;

        // Bind the texture to a name
        glBindTexture(target, loaded_texture.textureId);

        // Set texture clamping method
        glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // Set texture interpolation method to use linear interpolation (no MIPMAPS)
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        loaded_texture.width = ilGetInteger(IL_IMAGE_WIDTH);
        loaded_texture.height = ilGetInteger(IL_IMAGE_HEIGHT);

        const ILint image_format = ilGetInteger(IL_IMAGE_FORMAT);

        glTexImage2D(target, 0, image_format,
                     loaded_texture.width,
                     loaded_texture.height,
                     0, image_format,
                     GL_UNSIGNED_BYTE, ilGetData());

        // Because we have already copied image data into texture data we can release memory used by image.
        ilDeleteImages(1, &il_texture_id);

        return loaded_texture;
    }

};
