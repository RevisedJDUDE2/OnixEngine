#pragma once
#include "Essentials.hpp"

namespace Onix {
    class Texture {
    private:
      std::string m_ImageFileName;
      int m_ImageWidth{}, m_ImageHeight{}, m_Channels{};
      unsigned char* m_ImageHandle{};
        unsigned int m_TextureHandle;
        GLenum m_Target;
        /*DEFAULT PARAMS*/
        bool UsingDefaultParamters = true;
    public:
      Texture(std::string filename);
        void SetParameter(GLenum Param, GLint Value);
        void Generate(GLint internalFormat, GLenum Format);
        void Bind(void);
        void Unbind(void);
        [[deprecated("Not implemented yet!")]]
        void DeleteTexture(void);
    };
}