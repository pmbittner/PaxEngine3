//
// Created by Paul on 29.04.2017.
//

#include <typeindex>

#include <paxcore/entity/Entity.h>
#include <paxcore/entity/EntityComponent.h>
#include <paxcore/service/Services.h>

#include <easylogging++.h>

namespace PAX {
    const std::vector<EntityComponent*> Entity::EmptyEntityComponentVector(0);
    EntityComponentReflectionData Entity::entityComponentReflectionData = EntityComponentReflectionData();
    std::type_index Entity::EntityComponentType = typeid(EntityComponent);

    Entity::Entity() {
        OnParentChanged.add<EventService, &EventService::fire<EntityParentChangedEvent>>(&_localEventService);
    }

    Entity::~Entity() {
        for (const std::pair<EntityComponent* const, Reflection::TypeHierarchyNode*>& kv : _componentTypes) {
            Services::GetEntityComponentService().free(kv.second->type, kv.first);
        }

        _componentTypes.clear();
        _multipleComponents.clear();
        _singleComponents.clear();
    }

    Transformation& Entity::getTransformation() {
        return _transform;
    }

    void Entity::setParent(Entity *parent) {
        Entity *oldParent = _parent;//#PRANT
        _parent = parent;

        if (oldParent) {
            Util::removeFromVector(parent->_children, this);
        }

        Transformation *parentTransform = nullptr;
        if (_parent) {
            parentTransform = &_parent->_transform;
            _parent->_children.push_back(this);
        }
        _transform.setParent(parentTransform);

        EntityParentChangedEvent e(this, oldParent, parent);
        OnParentChanged(e);
    }

    Entity* Entity::getParent() const {
        return _parent;
    }

    const std::vector<Entity*>& Entity::getChildren() const {
        return _children;
    }

    WorldLayer* Entity::getWorldLayer() const {
        return _worldLayer;
    }

    EventService& Entity::getEventService() {
        return _localEventService;
    }

    void Entity::registerComponent(EntityComponent *component) {
        component->_owner = this;
        component->attached(*this);
    }

    void Entity::unregisterComponent(EntityComponent *component) {
        _componentTypes.erase(component);

        component->_owner = nullptr;
        component->detached(*this);
    }

    void Entity::onEntityComponentAttached(EntityComponent *component, const std::type_index& type) {
        entityComponentReflectionData.entityComponentAttachedHandlers.get(type)(this, component);
    }

    void Entity::onEntityComponentDetached(EntityComponent *component, const std::type_index& type) {
        entityComponentReflectionData.entityComponentDetachedHandlers.get(type)(this, component);
    }

    bool Entity::isValid(EntityComponent *component) {
        if (component->_owner) {
            LOG(WARNING) << "The component is already assigned to an Entity!";
            return false;
        }

        return component->areDependenciesMetFor(*this);
    }

    bool Entity::addComponentAsTypeSingle(EntityComponent *component, const std::type_index &type) {
        if (_singleComponents.contains(type)) {
            LOG(ERROR) << "Trying to add instance of " << type.name() << ", that does not allow multiple instances!";
            return false;
        }
        _singleComponents.put(type, component);
        return true;
    };

    bool Entity::addComponentAsTypeMultiple(EntityComponent *component, const std::type_index &type) {
        _multipleComponents[type].push_back(component);
        return true;
    }

    bool Entity::addComponentAsAllOfItsTypes(EntityComponent *component, Reflection::TypeHierarchyNode *typeNode) {
        bool addSuccess;

        if (entityComponentReflectionData.isMultiple.get(typeNode->type))
            addSuccess = addComponentAsTypeMultiple(component, typeNode->type);
        else
            addSuccess = addComponentAsTypeSingle(component, typeNode->type);

        if (addSuccess) {
            onEntityComponentAttached(component, typeNode->type);
            if (typeNode->parent->type == EntityComponentType)
                return true;
            return addComponentAsAllOfItsTypes(component, typeNode->parent);
        }
        return false;
    }

    bool Entity::add(EntityComponent *component) {
        if (isValid(component)) {
            registerComponent(component);
            auto typeNode = entityComponentReflectionData.entityComponentTypeHierarchy.getNodeOf(component->getClassType());
            _componentTypes[component] = typeNode;
            return addComponentAsAllOfItsTypes(component, typeNode);
        }

        return false;
    }

    bool Entity::removeComponentAsTypeSingle(EntityComponent *component, const std::type_index &type) {
        if (_singleComponents.get(type) != component) { // The given component is not the component, that is registered in this Entity for the given type
            std::cout << "\tFailed! Another component was found" << std::endl;
            return false;
        }

        _singleComponents.erase(type);
        return true;
    }

    bool Entity::removeComponentAsTypeMultiple(EntityComponent *component, const std::type_index &type) {
        std::vector<EntityComponent*> &result = _multipleComponents.get(type);
        if (!Util::removeFromVector(result, component)) {
            return false;
        }

        // Remove vector if no components of type ComponentClass remain
        if (result.empty()) {
            _multipleComponents.erase(type);
        }

        return true;
    }

    bool Entity::removeComponentAsAllOfItsTypes(EntityComponent *component, Reflection::TypeHierarchyNode *typeNode) {
        bool removeSuccess;

        if (entityComponentReflectionData.isMultiple.get(typeNode->type))
            removeSuccess = removeComponentAsTypeMultiple(component, typeNode->type);
        else
            removeSuccess = removeComponentAsTypeSingle(component, typeNode->type);

        if (removeSuccess) {
            onEntityComponentDetached(component, typeNode->type);
            if (typeNode->parent->type == EntityComponentType)
                return true;
            return removeComponentAsAllOfItsTypes(component, typeNode->parent);
        }

        return false;
    }

    bool Entity::remove(EntityComponent *component) {
        bool ret  = removeComponentAsAllOfItsTypes(component, _componentTypes[component]);
        unregisterComponent(component);
        return ret;
    }
}