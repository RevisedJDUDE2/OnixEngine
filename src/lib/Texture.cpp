#include "Texture.hpp"
#include "Texture.hpp"
#include "Texture.hpp"
#include "Texture.hpp"
#include "Onix.hpp"

//Onix::Texture::Texture(std::string filename) {
//    this->m_ImageFileName = filename;
//    glGenTextures(1, &this->m_TextureHandle);
//    glBindTexture(this->m_Target, this->m_TextureHandle);
//}

Onix::Texture::Texture(std::string filename) {
  this->m_ImageFileName = filename;
  glGenTextures(1, &this->m_TextureHandle);
  glBindTexture(this->m_Target, this->m_TextureHandle);
}

void Onix::Texture::SetParameter(GLenum Param, GLint Value) {
    this->UsingDefaultParamters = false;
    glTexParameteri(this->m_Target, Param, Value);
}
void Onix::Texture::Generate(GLint internalFormat, GLenum Format) {
    if(this->UsingDefaultParamters == true) {
        glTexParameteri(this->m_Target, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(this->m_Target, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(this->m_Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(this->m_Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    this->m_ImageHandle = stbi_load(this->m_ImageFileName.c_str(), &this->m_ImageWidth, &this->m_ImageHeight, &this->m_Channels, 0);
    if(this->m_ImageHandle) {
        glTexImage2D(this->m_Target, 0, internalFormat, this->m_ImageWidth, this->m_ImageHeight, 0, Format, GL_UNSIGNED_BYTE, this->m_ImageHandle);
        glGenerateMipmap(this->m_Target);
    } else {
        Onix::ThrowError("File (" + this->m_ImageFileName + ") Does not exist!");
    }
    stbi_image_free(this->m_ImageHandle);
}
void Onix::Texture::Bind(void) {
  glBindTexture(this->m_Target, this->m_TextureHandle);
}
void Onix::Texture::Unbind(void) {
  glBindTexture(this->m_Target, 0);
}
;