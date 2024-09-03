#include "AssetManager.h"

namespace Engine
{
    // Private constructor
    AssetManager::AssetManager()
    {
    }

    // Private destructor
    AssetManager::~AssetManager()
    {
    }

    // Static method to get the single instance of the class
    AssetManager& AssetManager::GetInstance()
    {
        static AssetManager instance;
        return instance;
    }

    void AssetManager::AddTexture(int id, const std::string &filePath, bool wantRepeated)
    {
        auto texture = std::make_unique<sf::Texture>();

        if (texture->loadFromFile(filePath))
        {
            texture->setRepeated(wantRepeated);
            textures[id] = std::move(texture);
        }
    }

    void AssetManager::AddFont(int id, const std::string &filePath)
    {
        auto font = std::make_unique<sf::Font>();

        if (font->loadFromFile(filePath))
        {
            fonts[id] = std::move(font);
        }
    }

    const sf::Texture &AssetManager::GetTexture(int id) const
    {
        return *(textures.at(id).get());
    }

    const sf::Font &AssetManager::GetFont(int id) const
    {
        return *(fonts.at(id).get());
    }
}
