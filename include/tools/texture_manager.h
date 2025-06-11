#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <unordered_map>

class TextureManager {
public:
  void registerTexture(const std::string &name, unsigned int texture);
  void bindTexture(const std::string &name);

private:
  std::unordered_map<std::string, unsigned int> avalibleTextures;
  int currentTextureSlot = 0;
};

#endif