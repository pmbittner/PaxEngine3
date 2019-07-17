//
// Created by Paul on 24.03.2019.
//

#ifndef PAXENGINE3_PROPERTYCONTAINERSYSTEM_H
#define PAXENGINE3_PROPERTYCONTAINERSYSTEM_H

#include <paxcore/function/Updateable.h>

namespace PAX {
    template<typename Derived>
    class SystemManager;

    template<typename ManagerType>
    class System : public Updateable {
        friend class SystemManager<ManagerType>;
        ManagerType * manager = nullptr;

        void setManager(ManagerType * manager) {
            this->manager = manager;
        }

    public:
        System() = default;
        ~System() override = default;

        virtual void initialize(ManagerType*) {}
        virtual void terminate(ManagerType*) {}

        ManagerType * getManager() {
            return manager;
        }
    };
}

#endif //PAXENGINE3_PROPERTYCONTAINERSYSTEM_H
