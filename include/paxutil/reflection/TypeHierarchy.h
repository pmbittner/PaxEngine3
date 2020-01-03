//
// Created by Paul on 15.01.2018.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTTYPEHIERARCHY_H
#define PAXENGINE3_ENTITYCOMPONENTTYPEHIERARCHY_H

#include <vector>
#include <typeindex>
#include <polypropylene/stdutils/CollectionUtils.h>
#include <iostream>

namespace PAX {
    namespace Reflection {
        class TypeHierarchyNode {
        public:
            const std::type_index type;
            TypeHierarchyNode* parent;
            std::vector<TypeHierarchyNode*> children;

            TypeHierarchyNode(std::type_index type);
            void prettyPrint(std::string indent);
        };

        class TypeHierarchy {
            TypeHierarchyNode _root;

            TypeHierarchyNode* createChildOf(const std::type_index &type, TypeHierarchyNode* parentNode);

            bool isSubType(const std::type_index &type, const TypeHierarchyNode* parentNode);
            TypeHierarchyNode* getNodeOf(const std::type_index &type, TypeHierarchyNode *node);

        public:
            TypeHierarchy(std::type_index root);

            TypeHierarchyNode* getNodeOf(const std::type_index &type);
            bool isSubTypeOf(const std::type_index &type, const std::type_index &super);
            TypeHierarchyNode* add(const std::type_index &type, const std::type_index &parentType);
            void prettyPrint();
        };
    }
}

#endif //PAXENGINE3_ENTITYCOMPONENTTYPEHIERARCHY_H
