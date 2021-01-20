//
// Created by paul on 06.01.20.
//

#ifndef PAXENGINE3_JSONRESOURCEFIELDWRITER_H
#define PAXENGINE3_JSONRESOURCEFIELDWRITER_H

#include <polypropylene/serialisation/json/JsonParser.h>
#include <paxutil/reflection/EngineFieldFlags.h>
#include <polypropylene/log/Errors.h>
#include <paxcore/service/Services.h>

namespace PAX {
    template<typename Resource>
    class JsonResourceFieldWriter : public Json::IJsonFieldWriter {
    public:
        void registerAt(Json::JsonFieldWriterRegister & writerRegister) {
            writerRegister.registerWriter(paxtypeid(std::shared_ptr<Resource>), this);
        }

        PAX_NODISCARD Field::WriteResult loadIntoField(const nlohmann::json & j, Field &field) const override {
            if (field.flags & EngineFieldFlags::IsResource) {
                if (field.type.id == paxtypeid(std::shared_ptr<Resource>)) {
                    std::shared_ptr<Resource> resource = Services::GetResources().loadOrGetFromJson<Resource>(j);
                    *static_cast<std::shared_ptr<Resource>*>(field.data) = resource;
                    return Field::WriteResult::Success;
                } else {
                    std::stringstream ss;
                    ss << "The type of the given field (" << field.name << ") is not std::shared_ptr<" << paxtypeid(Resource).name() << "> but " << field.type.name();
                    return Field::WriteResult(Field::WriteResult::TypeMismatch, ss.str());
                }
            } else {
                std::stringstream ss;
                ss << "Given field \"" << field.name << "\" is not flagged with EngineFieldFlags::IsResource!";
                return Field::WriteResult(Field::WriteResult::Other, ss.str());
            }
        }

        PAX_NODISCARD Field::WriteResult loadIntoVector(const nlohmann::json &j, Field &field) const override {
            PAX_NOT_IMPLEMENTED_EXCEPTION();
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

#endif //PAXENGINE3_JSONRESOURCEFIELDWRITER_H
