#include "spritebatch.h"

SpriteBatch::SpriteBatch() : vboID(0), vaoID(0) {
   ;
}

SpriteBatch::~SpriteBatch() {
   for(int i = 0; i < Glyphs.size(); i++) {
      delete Glyphs[i];
   }
}

void SpriteBatch::init() {
   if(vaoID == 0) {
      glGenVertexArrays(1, &vaoID)
   }
   glBindVertexArray(vaoID);
   if(vboID == 0) {
      glGenBuffers(1, &vboID);
   }
   glBindBuffer(GL_ARRAY_BUFFER, vboID);

   glEnableVertexAttribArray(0);
   glEnableVertexAttribArray(1);
   glEnableVertexAttribArray(2);

   glVertexAttribPointer(0, 3, GL_INT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
   glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
   glVertexAttribPointer(2, 2, GL_INT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));

   glBindVertexArray(0);
}

void SpriteBatch::begin(GlyphSortType sortingType) {
   sortType = sortingType;
}

void SpriteBatch::end() {
   sortGlyphs();
}

void SpriteBatch::draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color& color) {
   Glyph *temp = new Glyph;
   temp->depth = depth;
   temp->texture = texture;

   temp->bottomLeft.setPosition(destRect.x, destRect.y);
   temp->bottomLeft.setUV(uvRect.x, uvRect.y);
   temp->bottomLeft.setColor(color.r, color.g, color.b, color.a);

   temp->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
   temp->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
   temp->bottomRight.setColor(color.r, color.g, color.b, color.a);

   temp->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
   temp->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
   temp->topLeft.setColor(color.r, color.g, color.b, color.a);

   temp->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
   temp->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
   temp->topRight.setColor(color.r, color.g, color.b, color.a);

   Glyphs.push_back(temp);
   temp = nullptr;
}

void SpriteBatch::renderDraw() {

}

void SpriteBatch::sortGlyphs() {
   switch(sortType) {
      case GlyphSortType::BACK_TO_FRONT :
         std::stable_sort(Glyphs.begin(), Glyphs.end(), compareBackToFront);
         break;
      case GlyphSortType::FRONT_TO_BACK :
         std::stable_sort(Glyphs.begin(), Glyphs.end(), compareFrontToBack);
         break;
      case GlyphSortType::TEXTURE :
         std::stable_sort(Glyphs.begin(), Glyphs.end(), compareTexture);
         break;
   }

}

bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b) {
   return a->depth < b->depth;
}

bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b) {
   return a->depth > b->depth;
}

bool SpriteBatch::compareTexture(Glyph* a, Glyph* b) {
   return a->texture < b->texture;
}

