#include <core/entity/Entity.h>
#include <generated/EntityComponentTypeHierarchy.h>
#include <utility/reflection/TypeHierarchy.h>

namespace PAX {
    namespace Generated {
        bool EntityComponentTypeHierarchy::checkMultiplicity(const std::type_index& type, TypeMap<bool> &isTypeMultiple) {
            Reflection::TypeHierarchyNode* node = Entity::EntityComponentTypes.getNodeOf(type);
            while (node != nullptr) {
                if (!isTypeMultiple.get(node->type))
                    return false;
                node = node->parent;
            }

            return true;
        }
    }
}
