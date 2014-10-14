#ifndef SPRITEBATCH_H_INCLUDED
#define SPRITEBATCH_H_INCLUDED
#ifndef GLEW_BUILD
#define GLEW_BUILD
#endif // GLEW_BUILD
#include <GL/glew.h>
#include <algorithm>
#include "Vertex.h"

struct Glyph {
   GLuint texture;
   float depth;

   Vertex topLeft;
   Vertex topRight;
   Vertex bottomLeft;
   Vertex bottomRight;
};

enum class GlyphSortType {
   NONE,
   FRONT_TO_BACK,
   BACK_TO_FRONT,
   TEXTURE
};

class SpriteBatch {
   public:
      SpriteBatch();
      ~SpriteBatch();

      void init();
      void begin(GlyphSortType sortingType = GlyphSortType::TEXTURE);
      void end();
      void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color);
      void renderDraw();

   private:
      void sortGlyphs();

      static bool compareFrontToBack(Glyph* a, Glyph* b);
      static bool compareBackToFront(Glyph* a, Glyph* b);
      static bool compareTexture(Glyph* a, Glyph* b);

      GlyphSortType sortType;

      std::vector<Glyph> Glyphs;
      GLuint vboID;
      GLuint vaoID;
};


#endif // SPRITEBATCH_H_INCLUDED
