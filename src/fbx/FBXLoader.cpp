//
// Created by Paul on 28.12.2017.
//

#include <fbx/FBXLoader.h>
#include <utility/io/FormatChecker.h>

namespace PAX {
    FBXLoader::FBXLoader() {

    }

    FBXLoader::~FBXLoader() {

    }

    bool FBXLoader::canLoad(const char *path) {
        return Util::FormatChecker({"FBX"}).check(path);
    }

    FBXModel * FBXLoader::load(const char *path) {
        return nullptr;
    }

    bool FBXLoader::free(FBXModel *res) {
        return false;
    }


#ifdef DPAX_WITH_FBX
    void FBXLoader::InitializeSdkObjects(FbxManager*& pManager)
    {
        //The first thing to do is to create the FBX Manager which is the object allocator for almost all the classes in the SDK
        pManager = FbxManager::Create();
        if (!pManager)
        {
            FBXSDK_printf("Error: Unable to create FBX Manager!\n");
            exit(1);
        }
        else FBXSDK_printf("Autodesk FBX SDK version %s\n", pManager->GetVersion());

        //Create an IOSettings object. This object holds all import/export settings.
        FbxIOSettings* ios = FbxIOSettings::Create(pManager, IOSROOT);
        pManager->SetIOSettings(ios);

        //Load plugins from the executable directory (optional)
        FbxString lPath = FbxGetApplicationDirectory();
        pManager->LoadPluginsDirectory(lPath.Buffer());

    }

    void FBXLoader::DestroySdkObjects(FbxManager* pManager, bool pExitStatus)
    {
        //Delete the FBX Manager. All the objects that have been allocated using the FBX Manager and that haven't been explicitly destroyed are also automatically destroyed.
        if (pManager) pManager->Destroy();
        if (pExitStatus) FBXSDK_printf("Program Success!\n");
    }
#endif
}