# Onix Engine
### Onix Library classes
```c++
namespace Onix {
    class Shader;
    class Window;
    class Buffer; //BROKEN
    class VertexArray; //BROKEN
    class Texture; //BROKEN
}
```
### For now the library uses:
- stb_image.h
- Imgui
- OpenGL -> For the renderer
- GLFW -> For window creation and input
- glad -> OpenGL extension
- glew -> if not on linux
- DirectX -> Soon...
### Features
- [x] Onix Library
- [ ] Onix Game Engine (Editor)
- [ ] Cross-platform