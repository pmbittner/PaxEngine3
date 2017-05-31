//
// Created by Paul on 28.05.2017.
//

#ifndef PAXENGINE3_INHERITANCETEST_H
#define PAXENGINE3_INHERITANCETEST_H

namespace PAX {
    namespace TEST {
        namespace INHERITANCE {
            class Base {};
            class PublicDerived : public Base {};
            class PrivateDerived : private Base {};

            class Collection {
            public:
                void add(Base *b);
            };

            int test() {
                Collection c;

                Base b;
                PublicDerived pub;
                PrivateDerived priv;

                c.add(&b);
                c.add(&pub);
                //c.add(&priv); //impossible

                return 1;
            };
        }
    }
}

#endif //PAXENGINE3_INHERITANCETEST_H
