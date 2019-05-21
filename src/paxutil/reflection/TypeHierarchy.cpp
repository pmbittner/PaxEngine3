//
// Created by Paul on 15.01.2018.
//

#include <paxutil/reflection/TypeHierarchy.h>
#include <paxutil/log/Log.h>

namespace PAX {
    namespace Reflection {
        TypeHierarchyNode::TypeHierarchyNode(std::type_index type) : type(type) {

        }

        void TypeHierarchyNode::prettyPrint(std::string indent) {
            std::cout << indent.c_str() << type.name() << std::endl;
            std::string childIndent = indent + "\t";
            for (TypeHierarchyNode * child : children) {
                child->prettyPrint(childIndent);
            }
        }

        TypeHierarchy::TypeHierarchy(std::type_index root) : _root(root) {

        }

        TypeHierarchyNode* TypeHierarchy::createChildOf(const std::type_index &type, TypeHierarchyNode* parentNode) {
            TypeHierarchyNode* node = new TypeHierarchyNode(type);
            parentNode->children.push_back(node);
            node->parent = parentNode;
            return node;
        }

        TypeHierarchyNode* TypeHierarchy::getNodeOf(const std::type_index &type, TypeHierarchyNode *node) {
            if (type == node->type)
                return node;
            else {
                TypeHierarchyNode* nodeOfType = nullptr;
                for (TypeHierarchyNode* subTree : node->children) {
                    nodeOfType = getNodeOf(type, subTree);
                    if (nodeOfType)
                        return nodeOfType;
                }
            }

            return nullptr;
        }

        TypeHierarchyNode* TypeHierarchy::getNodeOf(const std::type_index &type) {
            return getNodeOf(type, &_root);
        }

        bool TypeHierarchy::isSubType(const std::type_index &type, const TypeHierarchyNode *parentNode) {
                if (parentNode) {
                    for (TypeHierarchyNode* child : parentNode->children) {
                        if (child->type == type || isSubType(type, child))
                            return true;
                    }
                }
                return false;
        }

        bool TypeHierarchy::isSubTypeOf(const std::type_index &type, const std::type_index &super) {
            return isSubType(type, getNodeOf(super));
        }

        TypeHierarchyNode* TypeHierarchy::add(const std::type_index &type, const std::type_index &parentType) {
            TypeHierarchyNode* node = getNodeOf(type);
            TypeHierarchyNode* parentNode = getNodeOf(parentType);

            if (!node) {
                node = new TypeHierarchyNode(type);

                if (!parentNode)
                    parentNode = createChildOf(parentType, &_root);
            } else {
                if (node->parent != &_root) {
                    // CONFLICT: Two supertypes but dont know which to use! node already has a parent!
                    Log::out.err() << "TypeHierarchy::add: Ambiguity in types " << parentType.name() << " and " << node->parent->type.name() << "! Both are supertypes of " << type.name() << "! The new parent " << parentType.name() << " will be ignored!" << std::endl;
                    return node;
                }

                if (!parentNode) {
                    Util::removeFromVector(node->parent->children, node);
                    parentNode = createChildOf(parentType, node->parent);
                }
            }

            parentNode->children.push_back(node);
            node->parent = parentNode;

            return node;
        }

        void TypeHierarchy::prettyPrint() {
            _root.prettyPrint("");
        }
    }
}