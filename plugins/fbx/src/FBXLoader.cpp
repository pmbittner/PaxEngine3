//
// Created by Paul on 28.12.2017.
//

#include <fbx/FBXLoader.h>
#include <utility/io/FormatChecker.h>

namespace PAX {
    FBXLoader::FBXLoader() {
        initializeSdkObjects();
    }

    FBXLoader::~FBXLoader() {
        destroySdkObjects();
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


    void FBXLoader::initializeSdkObjects()
    {
#ifdef PAX_WITH_FBX
        //The first thing to do is to create the FBX Manager which is the object allocator for almost all the classes in the SDK
        _fbxManager = FbxManager::Create();
        if (!_fbxManager)
        {
            FBXSDK_printf("Error: Unable to create FBX Manager!\n");
            exit(1);
        }
        else FBXSDK_printf("Autodesk FBX SDK version %s\n", _fbxManager->GetVersion());

        //Create an IOSettings object. This object holds all import/export settings.
        FbxIOSettings* ios = FbxIOSettings::Create(_fbxManager, IOSROOT);
        _fbxManager->SetIOSettings(ios);

        //Load plugins from the executable directory (optional)
        FbxString lPath = FbxGetApplicationDirectory();
        _fbxManager->LoadPluginsDirectory(lPath.Buffer());
#endif
    }

    void FBXLoader::destroySdkObjects()
    {
#ifdef PAX_WITH_FBX
        //Delete the FBX Manager. All the objects that have been allocated using the FBX Manager and that haven't been explicitly destroyed are also automatically destroyed.
        if (_fbxManager) _fbxManager->Destroy();
#endif
    }
}