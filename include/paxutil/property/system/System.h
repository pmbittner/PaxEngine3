//
// Created by Paul on 24.03.2019.
//

#ifndef PAXENGINE3_PROPERTYCONTAINERSYSTEM_H
#define PAXENGINE3_PROPERTYCONTAINERSYSTEM_H

namespace PAX {
    template<typename Derived>
    class SystemManager;

    template<typename ManagerType>
    class System {
        friend class SystemManager<ManagerType>;
        ManagerType * manager = nullptr;

        void setManager(ManagerType * manager) {
            this->manager = manager;
        }

    public:
        System() = default;
        virtual ~System() = default;

        virtual void initialize(ManagerType*) {}
        virtual void terminate(ManagerType*) {}
        virtual void update() {}

        ManagerType * getManager() {
            return manager;
        }
    };
}

#endif //PAXENGINE3_PROPERTYCONTAINERSYSTEM_H
