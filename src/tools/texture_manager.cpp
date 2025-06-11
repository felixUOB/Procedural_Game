#include "tools/texture_manager.h"
#include <iostream>
#include <unordered_map>
#include <vendor/glad/glad.h>

void TextureManager::registerTexture(const std::string &name,
                                     unsigned int texture) {
  std::cout << "Registering Texture: " << name << std::endl;

  avalibleTextures.emplace(name, texture);
}

void TextureManager::bindTexture(const std::string &name) {
  int maxSlots;
  glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxSlots);

  if (currentTextureSlot >= maxSlots) {
    currentTextureSlot = 0;
  }

  unsigned int texture = avalibleTextures.at(name);

  std::cout << "Binding Texture: " << name << " to " << currentTextureSlot
            << std::endl;
  glActiveTexture(GL_TEXTURE0 + currentTextureSlot);
  glBindTexture(GL_TEXTURE_2D, texture);

  currentTextureSlot++;
}
