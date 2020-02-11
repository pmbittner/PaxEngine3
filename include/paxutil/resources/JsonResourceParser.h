//
// Created by paul on 06.01.20.
//

#ifndef PAXENGINE3_JSONRESOURCEPARSER_H
#define PAXENGINE3_JSONRESOURCEPARSER_H

#include <polypropylene/serialisation/json/JsonParser.h>
#include <paxutil/reflection/EngineFieldFlags.h>
#include <polypropylene/log/Errors.h>
#include <paxcore/service/Services.h>

namespace PAX {
    template<typename Resource>
    class JsonResourceParser : public Json::IJsonParser {
    public:
        void registerAt(Json::JsonParserRegister & parserRegister) {
            parserRegister.registerParser(paxtypeid(std::shared_ptr<Resource>), this);
        }

        PAX_NODISCARD bool loadIntoField(const nlohmann::json & j, Field &field) const override {
            if (field.flags & EngineFieldFlags::IsResource) {
                if (field.type.id == paxtypeid(std::shared_ptr<Resource>)) {
                    std::shared_ptr<Resource> resource = Services::GetResources().loadOrGetFromJson<Resource>(j);
                    *static_cast<std::shared_ptr<Resource>*>(field.data) = resource;
                    return true;
                } else {
                    PAX_THROW_RUNTIME_ERROR("The type of the given field (" << field.name << ") is not std::shared_ptr<" << paxtypeid(Resource).name() << "> but " << field.type.name());
                }
            } else {
                PAX_THROW_RUNTIME_ERROR("Given field \"" << field.name << "\" is not flagged with EngineFieldFlags::IsResource!");
            }
        }

        PAX_NODISCARD bool loadIntoJson(const Field & field, nlohmann::json & j) const override {
            if (field.flags & EngineFieldFlags::IsResource) {
                if (field.type.id == paxtypeid(std::shared_ptr<Resource>)) {
                    //j.emplace(field.name, static_cast<std::shared_ptr<Resource>*>(field.data)->get()->toJson());
                    PAX_NOT_IMPLEMENTED();
                    return true;
                } else {
                    PAX_THROW_RUNTIME_ERROR("The type of the given field \"" << field.name << "\" is not std::shared_ptr<" << paxtypeid(Resource).name() << "> but " << field.type.name());
                }
            } else {
                PAX_THROW_RUNTIME_ERROR("Given field \"" << field.name << "\" is not flagged with EngineFieldFlags::IsResource!");
            }
        }
    };
}

#endif //PAXENGINE3_JSONRESOURCEPARSER_H
