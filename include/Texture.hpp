#pragma once
#include "Essentials.hpp"

namespace Onix {
    class Texture {
    private:
        std::string m_ImageFileName;
        int m_ImageWidth, m_ImageHeight, m_Channels;
        unsigned char* m_ImageHandle;
        unsigned int m_TextureHandle;
        GLenum m_Target;
        /*DEFAULT PARAMS*/
        bool UsingDefaultParamters = true;
    public:
        Texture(std::string filename) {
            this->m_ImageFileName = filename;
            glGenTextures(1, &this->m_TextureHandle);
            glBindTexture(this->m_Target, this->m_TextureHandle);
        };
        void SetParameter(GLenum Param, GLint Value);
        void Generate(GLint internalFormat, GLenum Format);
    };
}