//
// Created by Bittner on 01/03/2019.
//

#ifndef PAXENGINE3_JSONPROPERTYCONTAINERPREFAB_H
#define PAXENGINE3_JSONPROPERTYCONTAINERPREFAB_H

#include <paxutil/property/construction/PropertyContainerPrefab.h>
#include <paxutil/json/JsonUtil.h>
#include <paxutil/io/Path.h>

namespace PAX {
    template<typename C>
    using JsonPropertyContainerPrefabElementParser = JsonElementParser<C&>;

    template<typename C>
    class LambdaJsonPropertyContainerPrefabElementParser : public JsonPropertyContainerPrefabElementParser<C> {
    public:
        using Callback = std::function<void(nlohmann::json&, C&)>;
    private:
        Callback callback;
    public:
        explicit LambdaJsonPropertyContainerPrefabElementParser(const Callback & function) : callback(function) {}
        ~LambdaJsonPropertyContainerPrefabElementParser() override = default;
        void parse(nlohmann::json& j, C& c) override {
            callback(j, c);
        }
    };

    template<typename C>
    class JsonProperyContainerPrefabElementParserRegister {
        std::map<std::string, JsonPropertyContainerPrefabElementParser<C>*> parsers;

    public:
        JsonProperyContainerPrefabElementParserRegister() = default;
        bool registerParser(const std::string & name, JsonPropertyContainerPrefabElementParser<C> * parser) {
            const auto & it = parsers.find(name);
            if (it == parsers.end()) {
                parsers[name] = parser;
                return true;
            }

            return false;
        }
        bool registerParser(const std::string & name, const typename LambdaJsonPropertyContainerPrefabElementParser<C>::Callback & lambda) {
            return registerParser(name, new LambdaJsonPropertyContainerPrefabElementParser<C>(lambda));
        }
        bool unregisterParser(const std::string & name) {
            const auto & it = parsers.find(name);
            if (it != parsers.end()) {
                parsers.erase(it);
                return true;
            }

            return false;
        }
    };

    template<typename C>
    class JsonPropertyContainerPrefab : public PropertyContainerPrefab<C> {
        using json = nlohmann::json;

        json rootNode;

    public:
        static JsonProperyContainerPrefabElementParserRegister<C> Parsers;

        explicit JsonPropertyContainerPrefab(const json & file) : rootNode(file) {}

        virtual ~JsonPropertyContainerPrefab() = default;

        static void initialize() {
            // TODO: Some parsers like "transform" are only useful for C = Entity.
            //       Hence, outsource registration process and register the parsers only to their corresponding Prefab.
            Parsers.registerParser("transform", [](json & node, C & c){

            });

            Parsers.registerParser("properties", [](json & node, C & c){

            });
        }

        std::shared_ptr<C> create() override {
            // TODO: Investigate proper ways to instantiate the PropertyContainer.
            std::shared_ptr<C> c = std::make_shared<C>();



            return c;
        }
    };
}

#endif //PAXENGINE3_JSONPROPERTYCONTAINERPREFAB_H
