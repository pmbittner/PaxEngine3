//
// Created by Paul on 02.03.2019.
//

#ifndef PAXENGINE3_JSONCONTENTPROVIDER_H
#define PAXENGINE3_JSONCONTENTPROVIDER_H

#include <paxutil/property/construction/ContentProvider.h>
#include <paxutil/json/Json.h>

namespace PAX {
    class JsonContentProvider : public ContentProvider {
        nlohmann::json node;

    protected:
        std::any provide(const std::string & name, const TypeHandle & type) override;
        std::any provideEncapsulated(const std::string & name, const TypeHandle & elementType, const TypeHandle & containerType) override;

    public:
        explicit JsonContentProvider(const nlohmann::json & node);
        ~JsonContentProvider() override;
    };
}

#endif //PAXENGINE3_JSONCONTENTPROVIDER_H
