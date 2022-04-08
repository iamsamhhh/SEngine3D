#pragma once
#include <iostream>
namespace SEngine_Internal{
class FrameBuffer
{
public:
  void create_buffers(int32_t width, int32_t height);
  void delete_buffers();
  void bind();
  void unbind();
  
  uint32_t get_texture();

private:
  uint32_t mFBO = 0;
  uint32_t mTexId = 0;
  int32_t mWidth = 0;
  int32_t mHeight = 0;
};
}