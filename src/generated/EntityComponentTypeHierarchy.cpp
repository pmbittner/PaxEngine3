#include <generated/EntityComponentTypeHierarchy.h>
#include <core/entity/event/EntityComponentAddedEvent.h>
#include <core/entity/event/EntityComponentRemovedEvent.h>
#include <core/entity/Entity.h>
#include <core/entity/component/Behaviour.h>
#include <core/entity/component/behaviours/NoClipControls.h>
#include <core/rendering/Graphics.h>
#include <core/rendering/camera/Camera.h>
#include <core/rendering/graphics/SceneGraphGraphics.h>
#include <core/rendering/graphics/SpriteGraphics.h>
#include <core/rendering/graphics/SpriteSheetGraphics.h>
#include <demo/Platformer/PlayerControls.h>
#include <demo/Platformer/PlayerSpriteAnimation.h>
#include <generation/terrain/Terrain.h>

namespace PAX {
    namespace Generated {
        TypeMap<void (*)(Entity*, EntityComponent*)> EntityComponentTypeHierarchy::OnEntityComponentAttached;
        TypeMap<void (*)(Entity*, EntityComponent*)> EntityComponentTypeHierarchy::OnEntityComponentDetached;
        
        class EntityComponentTypeHierarchyEventBroker {
        public:
            static void EntityComponentAttached(Entity* e, EntityComponent *c) {
                EntityComponentAddedEvent<EntityComponent> event(static_cast<EntityComponent*>(c), e);
                e->_localEventService(event);
            }
            static void EntityComponentDetached(Entity* e, EntityComponent *c) {
                EntityComponentRemovedEvent<EntityComponent> event(static_cast<EntityComponent*>(c), e);
                e->_localEventService(event);
            }
            static void BehaviourAttached(Entity* e, EntityComponent *c) {
                EntityComponentAddedEvent<Behaviour> event(static_cast<Behaviour*>(c), e);
                e->_localEventService(event);
            }
            static void BehaviourDetached(Entity* e, EntityComponent *c) {
                EntityComponentRemovedEvent<Behaviour> event(static_cast<Behaviour*>(c), e);
                e->_localEventService(event);
            }
            static void NoClipControlsAttached(Entity* e, EntityComponent *c) {
                EntityComponentAddedEvent<NoClipControls> event(static_cast<NoClipControls*>(c), e);
                e->_localEventService(event);
            }
            static void NoClipControlsDetached(Entity* e, EntityComponent *c) {
                EntityComponentRemovedEvent<NoClipControls> event(static_cast<NoClipControls*>(c), e);
                e->_localEventService(event);
            }
            static void GraphicsAttached(Entity* e, EntityComponent *c) {
                EntityComponentAddedEvent<Graphics> event(static_cast<Graphics*>(c), e);
                e->_localEventService(event);
            }
            static void GraphicsDetached(Entity* e, EntityComponent *c) {
                EntityComponentRemovedEvent<Graphics> event(static_cast<Graphics*>(c), e);
                e->_localEventService(event);
            }
            static void CameraAttached(Entity* e, EntityComponent *c) {
                EntityComponentAddedEvent<Camera> event(static_cast<Camera*>(c), e);
                e->_localEventService(event);
            }
            static void CameraDetached(Entity* e, EntityComponent *c) {
                EntityComponentRemovedEvent<Camera> event(static_cast<Camera*>(c), e);
                e->_localEventService(event);
            }
            static void SceneGraphGraphicsAttached(Entity* e, EntityComponent *c) {
                EntityComponentAddedEvent<SceneGraphGraphics> event(static_cast<SceneGraphGraphics*>(c), e);
                e->_localEventService(event);
            }
            static void SceneGraphGraphicsDetached(Entity* e, EntityComponent *c) {
                EntityComponentRemovedEvent<SceneGraphGraphics> event(static_cast<SceneGraphGraphics*>(c), e);
                e->_localEventService(event);
            }
            static void SpriteGraphicsAttached(Entity* e, EntityComponent *c) {
                EntityComponentAddedEvent<SpriteGraphics> event(static_cast<SpriteGraphics*>(c), e);
                e->_localEventService(event);
            }
            static void SpriteGraphicsDetached(Entity* e, EntityComponent *c) {
                EntityComponentRemovedEvent<SpriteGraphics> event(static_cast<SpriteGraphics*>(c), e);
                e->_localEventService(event);
            }
            static void SpriteSheetGraphicsAttached(Entity* e, EntityComponent *c) {
                EntityComponentAddedEvent<SpriteSheetGraphics> event(static_cast<SpriteSheetGraphics*>(c), e);
                e->_localEventService(event);
            }
            static void SpriteSheetGraphicsDetached(Entity* e, EntityComponent *c) {
                EntityComponentRemovedEvent<SpriteSheetGraphics> event(static_cast<SpriteSheetGraphics*>(c), e);
                e->_localEventService(event);
            }
            static void PlayerControlsAttached(Entity* e, EntityComponent *c) {
                EntityComponentAddedEvent<PlayerControls> event(static_cast<PlayerControls*>(c), e);
                e->_localEventService(event);
            }
            static void PlayerControlsDetached(Entity* e, EntityComponent *c) {
                EntityComponentRemovedEvent<PlayerControls> event(static_cast<PlayerControls*>(c), e);
                e->_localEventService(event);
            }
            static void PlayerSpriteAnimationAttached(Entity* e, EntityComponent *c) {
                EntityComponentAddedEvent<PlayerSpriteAnimation> event(static_cast<PlayerSpriteAnimation*>(c), e);
                e->_localEventService(event);
            }
            static void PlayerSpriteAnimationDetached(Entity* e, EntityComponent *c) {
                EntityComponentRemovedEvent<PlayerSpriteAnimation> event(static_cast<PlayerSpriteAnimation*>(c), e);
                e->_localEventService(event);
            }
            static void TerrainAttached(Entity* e, EntityComponent *c) {
                EntityComponentAddedEvent<Terrain> event(static_cast<Terrain*>(c), e);
                e->_localEventService(event);
            }
            static void TerrainDetached(Entity* e, EntityComponent *c) {
                EntityComponentRemovedEvent<Terrain> event(static_cast<Terrain*>(c), e);
                e->_localEventService(event);
            }
        };
        
        void EntityComponentTypeHierarchy::initialize() {
            OnEntityComponentAttached.put(std::type_index(typeid(EntityComponent)), &EntityComponentTypeHierarchyEventBroker::EntityComponentAttached);
            OnEntityComponentDetached.put(std::type_index(typeid(EntityComponent)), &EntityComponentTypeHierarchyEventBroker::EntityComponentDetached);
            OnEntityComponentAttached.put(std::type_index(typeid(Behaviour)), &EntityComponentTypeHierarchyEventBroker::BehaviourAttached);
            OnEntityComponentDetached.put(std::type_index(typeid(Behaviour)), &EntityComponentTypeHierarchyEventBroker::BehaviourDetached);
            OnEntityComponentAttached.put(std::type_index(typeid(NoClipControls)), &EntityComponentTypeHierarchyEventBroker::NoClipControlsAttached);
            OnEntityComponentDetached.put(std::type_index(typeid(NoClipControls)), &EntityComponentTypeHierarchyEventBroker::NoClipControlsDetached);
            OnEntityComponentAttached.put(std::type_index(typeid(Graphics)), &EntityComponentTypeHierarchyEventBroker::GraphicsAttached);
            OnEntityComponentDetached.put(std::type_index(typeid(Graphics)), &EntityComponentTypeHierarchyEventBroker::GraphicsDetached);
            OnEntityComponentAttached.put(std::type_index(typeid(Camera)), &EntityComponentTypeHierarchyEventBroker::CameraAttached);
            OnEntityComponentDetached.put(std::type_index(typeid(Camera)), &EntityComponentTypeHierarchyEventBroker::CameraDetached);
            OnEntityComponentAttached.put(std::type_index(typeid(SceneGraphGraphics)), &EntityComponentTypeHierarchyEventBroker::SceneGraphGraphicsAttached);
            OnEntityComponentDetached.put(std::type_index(typeid(SceneGraphGraphics)), &EntityComponentTypeHierarchyEventBroker::SceneGraphGraphicsDetached);
            OnEntityComponentAttached.put(std::type_index(typeid(SpriteGraphics)), &EntityComponentTypeHierarchyEventBroker::SpriteGraphicsAttached);
            OnEntityComponentDetached.put(std::type_index(typeid(SpriteGraphics)), &EntityComponentTypeHierarchyEventBroker::SpriteGraphicsDetached);
            OnEntityComponentAttached.put(std::type_index(typeid(SpriteSheetGraphics)), &EntityComponentTypeHierarchyEventBroker::SpriteSheetGraphicsAttached);
            OnEntityComponentDetached.put(std::type_index(typeid(SpriteSheetGraphics)), &EntityComponentTypeHierarchyEventBroker::SpriteSheetGraphicsDetached);
            OnEntityComponentAttached.put(std::type_index(typeid(PlayerControls)), &EntityComponentTypeHierarchyEventBroker::PlayerControlsAttached);
            OnEntityComponentDetached.put(std::type_index(typeid(PlayerControls)), &EntityComponentTypeHierarchyEventBroker::PlayerControlsDetached);
            OnEntityComponentAttached.put(std::type_index(typeid(PlayerSpriteAnimation)), &EntityComponentTypeHierarchyEventBroker::PlayerSpriteAnimationAttached);
            OnEntityComponentDetached.put(std::type_index(typeid(PlayerSpriteAnimation)), &EntityComponentTypeHierarchyEventBroker::PlayerSpriteAnimationDetached);
            OnEntityComponentAttached.put(std::type_index(typeid(Terrain)), &EntityComponentTypeHierarchyEventBroker::TerrainAttached);
            OnEntityComponentDetached.put(std::type_index(typeid(Terrain)), &EntityComponentTypeHierarchyEventBroker::TerrainDetached);
            
            Reflection::TypeHierarchy &h = Entity::EntityComponentTypes;
            h.add(std::type_index(typeid(Behaviour)), std::type_index(typeid(EntityComponent)));
            h.add(std::type_index(typeid(Graphics)), std::type_index(typeid(EntityComponent)));
            h.add(std::type_index(typeid(SceneGraphGraphics)), std::type_index(typeid(Graphics)));
            h.add(std::type_index(typeid(PlayerControls)), std::type_index(typeid(Behaviour)));
            h.add(std::type_index(typeid(Terrain)), std::type_index(typeid(Graphics)));
            h.add(std::type_index(typeid(NoClipControls)), std::type_index(typeid(Behaviour)));
            h.add(std::type_index(typeid(SpriteGraphics)), std::type_index(typeid(SceneGraphGraphics)));
            h.add(std::type_index(typeid(PlayerSpriteAnimation)), std::type_index(typeid(Behaviour)));
            h.add(std::type_index(typeid(Camera)), std::type_index(typeid(EntityComponent)));
            h.add(std::type_index(typeid(SpriteSheetGraphics)), std::type_index(typeid(SpriteGraphics)));
        }
    }
}
