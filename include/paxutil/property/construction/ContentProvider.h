//
// Created by Bittner on 10/01/2019.
//

#ifndef PAXENGINE3_CONTENTPROVIDER_H
#define PAXENGINE3_CONTENTPROVIDER_H

#include <string>
#include <sstream>
#include <memory>
#include <optional>
#include <any>
#include <iostream>
#include <paxutil/resources/Resources.h>

#include "paxutil/StringVariables.h"
#include "paxutil/macros/Definitions.h"
#include "paxutil/reflection/TypeHandle.h"

// FIXME: Remove these includes.
#include "paxutil/json/Json.h"
#include "paxutil/json/JsonParser.h"

namespace PAX {
    namespace Internal {
        class PropertyContent {
        protected:
            virtual std::string getValue(const std::string & key, const VariableRegister & variables) = 0;
            virtual std::vector<std::string> getValues(const std::string & key, const VariableRegister & variables) = 0;

        public:
            PropertyContent() = default;
            virtual ~PropertyContent() = default;

            virtual bool has(const std::string & name) = 0;
            virtual VariableHierarchy getResourceParametersFor(const std::string & name) = 0;

            template<typename T>
            T get(const std::string & name, const VariableRegister & variables) {
                // FIXME: This is a hack! We should not refer to Json here but the subclass should!
                return Json::tryParse<T>(StringToJson(getValue(name, variables)));
            }

            template<typename T>
            std::vector<T> getList(const std::string & name, const VariableRegister & variables) {
                std::vector<std::string> str_values = getValues(name, variables);
                std::vector<T> values;

                for (size_t i = 0; i < str_values.size(); ++i) {
                    // FIXME: This is a hack! We should not refer to Json here but the subclass should!
                    values.push_back(Json::tryParse<T>(StringToJson(str_values[i])));
                }

                return values;
            }
        };
    }

    class ContentProvider {
        Internal::PropertyContent * content = nullptr;
        Resources & resources;
        const VariableRegister & variables;

    public:
        explicit ContentProvider(Resources & resources, const VariableRegister & variables)
        : resources(resources), variables(variables) {}

        virtual ~ContentProvider() = default;

        void setContent(Internal::PropertyContent * content) {
            this->content = content;
        }

        template<typename T>
        std::optional<T> get(const std::string & name) {
            //std::cout << "[ContentProvider::get<" << paxtypeid(T).name() << ">] " << name << std::endl;
            if (content->has(name)) {
                return content->get<T>(name, this->variables);
            }
            return {};
        }

        template<typename T>
        T require(const std::string & name) noexcept(false) {
            //std::cout << "[ContentProvider::require<" << paxtypeid(T).name() << ">] " << name << std::endl;
            std::optional<T> opt = get<T>(name);

            if (opt.has_value()) {
                //std::cout << "[ContentProvider::require<" << paxtypeid(T).name() << ">] got " << opt.value() << std::endl;
                return opt.value();
            }

            PAX_THROW_RUNTIME_ERROR("Variable " << name <<  " could not be obtained!");
        }

        template<typename T>
        std::optional<std::shared_ptr<T>> getResource(const std::string & name) {
            //std::cout << "[ContentProvider::getResource<" << paxtypeid(T).name() << ">] " << name << std::endl;
            VariableHierarchy params = content->getResourceParametersFor(name);
            VariableResolver::resolveAllInHierarchy(params, variables);
            return resources.loadOrGetFromVariableRegister<T>(params);
        }

        template<typename T>
        std::shared_ptr<T> requireResource(const std::string & name) noexcept(false) {
            //std::cout << "[ContentProvider::requireResource<" << paxtypeid(T).name() << ">] " << name << std::endl;

            std::optional<std::shared_ptr<T>> opt = getResource<T>(name);

            if (opt.has_value())
                return opt.value();

            PAX_THROW_RUNTIME_ERROR("Variable " << name <<  " could not be obtained!");
        }

        template<typename T>
        std::optional<std::vector<T>> getList(const std::string & name) {
            if (content->has(name)) {
                return content->getList<T>(name, this->variables);
            }
            return {};
        }

        template<typename T>
        std::vector<T> requireList(const std::string & name) {
            auto list = getList<T>(name);

            if (list.has_value())
                return list.value();

            PAX_THROW_RUNTIME_ERROR("Variable " << name <<  " could not be obtained!");
        }
    };
}

#endif //PAXENGINE3_CONTENTPROVIDER_H
