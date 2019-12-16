#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <map>
#include <string>
#include <memory>
#include "FrameWork/Asset.h"

// Asset Manager should have primary and secundary assets, primary assets are loaded when the Scene is loaded.
// Secundary assets are loaded when referenced and unloaded when all references are gone.
// There also should be a way to efficiently handle large world, either by having zones/chuks and load them depending on player position.
// Currently, I think the best way for big worlds is to have boxes that act as chunks, and those chunks would have colliders and when the camera enters one of those colliders
//  the chunk will start loading. Then there would be another collider where once entered, the chunk HAS to be loaded, and if it's not, a loading screen will be brought up.
// This way, you don't have to create multiple levels and switch between them. But I might take another route depending on how things turn out.

class AssetManager
{
public:
    AssetManager();
private:
    std::map<std::string, std::shared_ptr<Asset>> assets;
public:
    template <class T> std::shared_ptr<T> getAssetByPath(std::string path);
    bool addAssetByPtr(Asset *ptr);///< This will take ownership of the pointer.
};

template<class T>
std::shared_ptr<T> AssetManager::getAssetByPath(std::string path)
{
    return nullptr;
}

#endif // ASSETMANAGER_H
