//
// Created by Bittner on 01/03/2019.
//

#ifndef PAXENGINE3_JSONPROPERTYCONTAINERPREFAB_H
#define PAXENGINE3_JSONPROPERTYCONTAINERPREFAB_H

#include <paxutil/property/construction/PropertyContainerPrefab.h>
#include <paxutil/json/JsonUtil.h>
#include <paxutil/io/Path.h>

#include <paxutil/property/Property.h>
#include <paxutil/math/json/JsonToTransformation.h>

#include "../ContentProvider.h"
#include "JsonPropertyContent.h"

namespace PAX {
    namespace Json {
        template<typename C>
        class JsonPropertyContainerPrefab;

        template<typename C>
        using JsonPropertyContainerPrefabElementParser = JsonElementParser<C &, JsonPropertyContainerPrefab<C> &>;

        template<typename C>
        class LambdaJsonPropertyContainerPrefabElementParser : public JsonPropertyContainerPrefabElementParser<C> {
        public:
            using Callback = std::function<void(nlohmann::json &, C &, JsonPropertyContainerPrefab<C> &)>;
        private:
            Callback callback;
        public:
            explicit LambdaJsonPropertyContainerPrefabElementParser(const Callback &function)
                    : JsonPropertyContainerPrefabElementParser<C>(), callback(function) {}

            ~LambdaJsonPropertyContainerPrefabElementParser() override = default;

            void parse(nlohmann::json &j, C &c, JsonPropertyContainerPrefab<C> &prefab) override {
                callback(j, c, prefab);
            }
        };

        template<typename C>
        class JsonProperyContainerPrefabElementParserRegister {
            std::map<std::string, JsonPropertyContainerPrefabElementParser<C> *> parsers;

        public:
            JsonProperyContainerPrefabElementParserRegister() = default;

            bool registerParser(const std::string &name, JsonPropertyContainerPrefabElementParser<C> *parser) {
                const auto &it = parsers.find(name);
                if (it == parsers.end()) {
                    parsers[name] = parser;
                    return true;
                }

                return false;
            }

            bool registerParser(const std::string &name,
                                const typename LambdaJsonPropertyContainerPrefabElementParser<C>::Callback &lambda) {
                return registerParser(name, new LambdaJsonPropertyContainerPrefabElementParser<C>(lambda));
            }

            bool unregisterParser(const std::string &name) {
                const auto &it = parsers.find(name);
                if (it != parsers.end()) {
                    parsers.erase(it);
                    return true;
                }

                return false;
            }

            const std::map<std::string, JsonPropertyContainerPrefabElementParser<C> *> &getRegister() {
                return parsers;
            }
        };

        template<typename C>
        class JsonPropertyContainerPrefab : public PropertyContainerPrefab<C> {
            using json = nlohmann::json;

            std::shared_ptr<json> rootNode;
            Path path;

            void parse(json &parent, const std::string &childname, C &c) {
                const auto &parserRegister = Parsers.getRegister();
                const auto &it = parserRegister.find(childname);
                if (it != parserRegister.end()) {
                    if (parent.count(childname) > 0) {
                        it->second->parse(parent[childname], c, *this);
                    }
                } else {
                    std::cerr << "[JsonPropertyContainerPrefab::parse] ignoring element " << childname
                              << " because no parser is registered for it!" << std::endl;
                }
            }

        public:
            static JsonProperyContainerPrefabElementParserRegister<C> Parsers;

            explicit JsonPropertyContainerPrefab(const std::shared_ptr<json> &file, const Path &path, Allocator * containerAllocator = nullptr)
                    : PropertyContainerPrefab<C>(containerAllocator), rootNode(file), path(path) {}

            virtual ~JsonPropertyContainerPrefab() = default;

            static void initialize(Resources &resources) {
                Parsers.registerParser(
                        "Inherits",
                        [&resources](json &node, C &c, JsonPropertyContainerPrefab<C> &prefab) {
                            for (auto &el : node.items()) {
                                Path parentPath = prefab.path.getDirectory() + el.value();
                                std::shared_ptr<PropertyContainerPrefab<C>> parentPrefab;

                                const auto &it = prefab.parentPrefabs.find(parentPath);
                                if (it != prefab.parentPrefabs.end()) {
                                    parentPrefab = it->second;
                                } else {
                                    parentPrefab = resources.loadOrGet<PropertyContainerPrefab<C>>(
                                            parentPath);
                                    prefab.parentPrefabs[parentPath] = parentPrefab;
                                }

                                parentPrefab->addMyContentTo(c);
                            }
                        });

                Parsers.registerParser(
                        "Properties",
                        [&resources](json &node, C &c, JsonPropertyContainerPrefab<C> &prefab) {
                            std::vector<Property<C> *> props;

                            ContentProvider contentProvider(resources,
                                                            PropertyContainerPrefab<C>::PreDefinedVariables);

                            for (auto &el : node.items()) {
                                const std::string propTypeName = el.key();
                                IPropertyFactory<C> *propertyFactory = PropertyFactoryRegister<C>::getFactoryFor(
                                        propTypeName);

                                /*
                                std::cout
                                        << "[JsonPropertyContainerPrefab::parse(\"Properties\")] creating "
                                        << propTypeName << std::endl;
                                //*/
                                JsonPropertyContent content(el.value());
                                contentProvider.setContent(&content);

                                // If the container already has properties of the given type we wont create a new one,
                                // but instead overwrite the old ones with the newer settings.
                                const PAX::TypeHandle &propType = propertyFactory->getPropertyType();
                                bool isPropMultiple = propertyFactory->isPropertyMultiple();

                                if (c.has(propType, isPropMultiple)) {
                                    // Get the corresponding property/ies
                                    if (isPropMultiple) {
                                        const std::vector<Property<C> *> &existingProperties = c.getMultiple(
                                                propType);
                                        for (Property<C> *existingProperty : existingProperties) {
                                            propertyFactory->reinit(existingProperty, contentProvider);
                                        }
                                    } else {
                                        propertyFactory->reinit(c.getSingle(propType), contentProvider);
                                    }
                                } else {
                                    props.emplace_back(propertyFactory->create(contentProvider));
                                }

                                contentProvider.setContent(nullptr);
                            }

                            // Add the properties deferred to resolve their dependencies.
                            while (!props.empty()) {
                                size_t numOfPropsToAdd = props.size();

                                for (auto it = props.begin(); it != props.end(); ++it) {
                                    if ((*it)->areDependenciesMetFor(c)) {
                                        c.add(*it);
                                        props.erase(it);
                                        break;
                                    }
                                }

                                if (numOfPropsToAdd == props.size()) {
                                    // Not a single property could be added to the Entity because not a single dependency is met!
                                    std::cerr
                                            << "[JsonPropertyContainerPrefab::parse \"properties\"] Error during adding properties! Dependencies could not be met!"
                                            << std::endl;
                                    break;
                                }
                            }
                        });
            }

            std::shared_ptr<C> create() override {
                std::shared_ptr<C> c = nullptr;

                if (PropertyContainerPrefab<C>::allocator) {
                    void * mem = PropertyContainerPrefab<C>::allocator->allocate(sizeof(C));
                    c = std::shared_ptr<C>(
                            new (mem) C,
                            [this](C * c) {
                                delete c;
                                this->allocator->destroy(c);
                            });
                } else {
                    c = std::make_shared<C>();
                }

                addMyContentTo(*c.get());
                return c;
            }

            void addMyContentTo(C &c) override {
                std::vector<std::string> parseOrder = {
                        "Inherits"
                        "Properties"
                };

                for (const std::string & name : parseOrder) {
                    if (rootNode->count(name) > 0) {
                        parse(*rootNode.get(), "Inherits", c);
                    }
                }

                for (auto &el : rootNode->items()) {
                    if (!Util::vectorContains(parseOrder, el.key())) {
                        parse(*rootNode.get(), el.key(), c);
                    }
                }
            }
        };

        template<typename C>
        JsonProperyContainerPrefabElementParserRegister<C> JsonPropertyContainerPrefab<C>::Parsers;
    }
}

#endif //PAXENGINE3_JSONPROPERTYCONTAINERPREFAB_H
