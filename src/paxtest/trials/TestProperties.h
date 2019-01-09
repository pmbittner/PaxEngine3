//
// Created by paul on 06.01.19.
//

#ifndef PAXENGINE3_TESTPROPERTIES_H
#define PAXENGINE3_TESTPROPERTIES_H

#include <paxutil/property/PropertyContainer.h>
#include <paxutil/property/PropertyContainerPrefab.h>

namespace PAX {
    class ExampleContainer : public PropertyContainer<ExampleContainer> {};
    using ExampleProperty = Property<ExampleContainer>;

    class Bla : public ExampleProperty {
        PAX_PROPERTY(Bla)
        PAX_PROPERTY_DERIVES(ExampleProperty)
        PAX_PROPERTY_IS_SINGLE

        std::string secretMessage = "Abendblaeue";

    public:
        Bla();

        void bla();
    };
}

/*
 * New Idea for Property Creation:
 * If we don't know, what the property needs, let it ask for it!
 *
 * class Prefab : public IContentProvider {
 *     Entity create() {
 *         ...
 *         foreach (String propName : propsToConstruct) {
 *             Factory f = PropertyFactories.getForName(propName);
 *             Property p = f.create(this);
 *             entity.add(p);
 *         }
 *         ...
 *         return entity;
 *     }
 *
 *     // The provide function may become tricky. This needs some more research perhaps.
 *     // This won't work with polymorphism either (regarding IContentProvider).
 *
 *     template<typename T>
 *     T* provide() {
 *          read the next item from the file if possible
 *     }
 *
 *     template<>
 *     std::shared_ptr<Texture> provide() {
 *          Path tex = Services::GetPaths().getResourcePath() + fromXML.getTextureName();
 *          return Services::GetResources().loadOrGet<Texture>(texName);
 *     }
 * }
 *
 * template<class PropertyType>
 * PropertyType* Factory::create(Prefab & prefab) {
 *     PropertyType* property = PropertyType::constructFromProvider(prefab);
 *     ...
 *     return property;
 * }
 *
 * In Property type headers and cpp do something like this:
 *
 * -> make all constructors private! That way we can ensure, that the generated functions will be used
 *    and that all properties are then constructed the right way.
 *
 * SpriteGraphics * SpriteGraphics::constructFromProvider(IContentProvider & provider) {
 *     auto& tex = provider.provide<Texture>();
 *     return SpriteGraphics::create(tex);
 * }
 *
 * And then use some macro magic to generate this. This will allow constructing properties in code, too.
 * SpriteGraphics * SpriteGraphics::create(const std::shared_ptr<Texture> & tex) {
 *     SpriteGraphics * memory = Entity::GetAllocator().reserve(sizeof(SpriteGraphics)); // this needs refactoring, too
 *     return new (memory) SpriteGraphics(tex); // use std::forward here ?
 * }
 *
 * We could even delay the object creation to the end of Property::construct to allow any
 * type of constructor. *-*
 *
 * Test this in a suited environment before integrating this into the engine.
 */

#endif //PAXENGINE3_TESTPROPERTIES_H
