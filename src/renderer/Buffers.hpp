
#include <iterator>

#include "glad/glad.h"
class VertexBuffer {
 public:
  VertexBuffer() noexcept;
  void bind() const noexcept;
  template <class Container>
  void assign(Container container) const noexcept {
    glBufferData(GL_ARRAY_BUFFER, sizeof(container), std::data(container), GL_STATIC_DRAW);
  }

 private:
  GLuint id_;
};

class IndexBuffer {
 public:
  void bind() const noexcept;

 private:
  GLuint id_;
};

class VertexArray {
 public:
  void bind() const noexcept;

 private:
  GLuint id_;
};
