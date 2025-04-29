#pragma once

#include <raylib.h>
#include <filesystem>
#include <unordered_map>

class TextureManager {
public:
  static TextureManager& Instance() {
    static TextureManager* instance = new TextureManager();
    return *instance;
  }

  virtual ~TextureManager() { UnloadAll(); }

  /**
   * @brief get texture, if not loaded, load it.
   *
   * @param path
   * @return reference of texture 2d
   */
  Texture2D& GetTexture(const std::filesystem::path& path);

private:
  TextureManager() {}
  std::unordered_map<std::filesystem::path, Texture2D> textures_;

  void UnloadAll();

  /** @brief used this texture when loading texture failed */
  Texture2D CreateDefaultTexture();
};
