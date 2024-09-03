#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

namespace Engine
{
    class AssetManager
    {
    public:
        // Deleted copy constructor and assignment operator to enforce Singleton property
        AssetManager(const AssetManager&) = delete;
        AssetManager& operator=(const AssetManager&) = delete;

        // Static method to get the single instance of the class
        static AssetManager& GetInstance();

        void AddTexture(int id, const std::string &filePath, bool wantRepeated = false);
        void AddFont(int id, const std::string &filePath);

        const sf::Texture &GetTexture(int id) const;
        const sf::Font &GetFont(int id) const;

    private:
        // Private constructor and destructor
        AssetManager();
        ~AssetManager();

        std::map<int, std::unique_ptr<sf::Texture>> textures;
        std::map<int, std::unique_ptr<sf::Font>> fonts;
    };
}

#endif // ASSETMANAGER_H
