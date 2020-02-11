//
// Created by paul on 31.03.19.
//

#include <paxutil/resources/Resources.h>

namespace PAX {
    ResourceAlreadyCachedException::ResourceAlreadyCachedException(const std::string &res) {
        msg = std::string("The Resource ") + res + std::string(" is already cached!");
    }

    const char* ResourceAlreadyCachedException::what() const noexcept
    {
        return msg.c_str();
    }


    bool Resources::unregisterResource(const std::type_index type, PAX::ResourceHandle *handle) {
        auto deletedElementCount = _resourcesInUse.at(type).erase(handle);
        delete handle; // deletes its signature
        return deletedElementCount > 0;
    }

    void Resources::collectGarbage() {
        // TODO: Repeat the process until no deallocations happen because there might be dependencies between resources.
        for (std::pair<const std::type_index, std::unordered_set<ResourceHandle*>> &kv : _resourcesInUse) {
            std::unordered_set<ResourceHandle*> &handles = kv.second;
            std::unordered_set<ResourceHandle*> resourcesToDelete;

            for (ResourceHandle* handle : handles) {
                if (handle->getExternalReferenceCount() == 0) {
                    resourcesToDelete.insert(handle);
                }
            }

            for (ResourceHandle* handle : resourcesToDelete) {
                unregisterResource(kv.first, handle);
            }
        }
    }
}