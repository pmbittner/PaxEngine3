//
// Created by Paul on 01.05.2017.
//

#ifndef PAXENGINE3_ENTITYCOMPONENTPOOL_H
#define PAXENGINE3_ENTITYCOMPONENTPOOL_H

#include <vector>

namespace PAX {
    template<class T>
    class EntityComponentPool {
    private:
        union ArrayElement {
        public:
            T _element;
            ArrayElement *_next;
        };

        std::vector<ArrayElement> _pool;
        ArrayElement *_firstFreeElement;

    protected:
        virtual T createElement() = 0;

    public:
        void initialize(int size) {
            _pool.reserve(size);

            for (int i = 0; i < size - 1; ++i) {
                _pool[i]._next = &_pool[i + 1];
            }

            _pool[size-1]._next = nullptr;
        }

        T *newElement() {
            ArrayElement* ship = _firstFreeElement;

            if (ship->_next) {
                _firstFreeElement = ship->_next;
            } else {
                // increase pool size
                int initialPoolSize = _pool.capacity();
                int numOfNewObjects = _pool.capacity();
                _pool.reserve(initialPoolSize + numOfNewObjects);

                for (int i = 0; i < numOfNewObjects - 1; ++i) {
                    _pool[initialPoolSize + i]._next = &_pool[initialPoolSize + i + 1];
                }

                _pool[initialPoolSize + numOfNewObjects - 1]._next = _firstFreeElement;
                _firstFreeElement = &_pool[initialPoolSize];
            }

            // initialize the element correctly as it may has suffered from being in a union
            ship->_element = createElement();
            return &ship->_element;
        }

        void freeElement(T *element) {
            ArrayElement *ship = reinterpret_cast<ArrayElement*>(element);
            ship->_next = _firstFreeElement;
            _firstFreeElement = ship;
        }
    };
}

#endif //PAXENGINE3_ENTITYCOMPONENTPOOL_H
