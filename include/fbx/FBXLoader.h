//
// Created by Paul on 28.12.2017.
//

#ifndef PAXENGINE3_FBXLOADER_H
#define PAXENGINE3_FBXLOADER_H

#include <core/io/resources/ResourceLoader.h>
#include "FBXModel.h"

#ifdef DPAX_WITH_FBX
#include <fbxsdk.h>
#endif

namespace PAX {
    class FBXLoader : ResourceLoader<FBXModel, const char*> {
#ifdef DPAX_WITH_FBX
        FbxManager _fbxManager;
#endif
    public:
        FBXLoader();
        ~FBXLoader();

        bool free(FBXModel *res) override;
        bool canLoad(const char * path) override;
        FBXModel *load(const char * path) override;

    private:
#ifdef DPAX_WITH_FBX
        void FBXLoader::InitializeSdkObjects(FbxManager*& pManager);
        void FBXLoader::DestroySdkObjects(FbxManager* pManager, bool pExitStatus);
#endif
    };
}

#endif //PAXENGINE3_FBXLOADER_H
