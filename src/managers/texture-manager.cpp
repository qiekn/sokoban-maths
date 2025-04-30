#include "managers/texture-manager.h"

Texture2D& TextureManager::GetTexture(const std::filesystem::path& path) {
  auto it = textures_.find(path);
  if (it == textures_.end()) {
    Texture2D texture = LoadTexture(path.c_str());
    if (texture.id == 0) {
      texture = CreateDefaultTexture();
    }
    textures_[path] = texture;
    return textures_[path];
  }
  return it->second;
}

void TextureManager::UnloadAll() {
  for (const auto& pair : textures_) {
    UnloadTexture(pair.second);
  }
  textures_.clear();
}

Texture2D TextureManager::CreateDefaultTexture() {
  Image image = GenImageColor(32, 32, MAGENTA);
  Texture2D texture = LoadTextureFromImage(image);
  UnloadImage(image);
  return texture;
}
