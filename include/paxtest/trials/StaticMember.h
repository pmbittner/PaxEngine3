//
// Created by paul on 01.06.17.
//

#ifndef PAXENGINE3_STATICMEMBER_H
#define PAXENGINE3_STATICMEMBER_H

#include <vector>
#include <iostream>

namespace PAX {
    namespace Test {
        namespace StaticMember {
#define COMPONENTCLASS(name, multi) class name : public Super { \
            public: \
                const static bool Mult = multi;\
                virtual bool isMult() override { return multi; } \
            private:

            class Super {
            public:
                virtual bool isMult() = 0;
            };

            COMPONENTCLASS(DerivedTrue, true)

            };

            COMPONENTCLASS(DerivedFalse, false)

            };

#define PAXDOTTEST(name, args...) struct name { float args; };
PAXDOTTEST(TestClass, lol=1, rofl=3)

            int run() {
                TestClass t;
                std::cout << t.lol << " " << t.rofl << std::endl;

                std::vector<Super*> elements;

                elements.push_back(new DerivedFalse);
                elements.push_back(new DerivedTrue);

                for (Super* s : elements)
                    std::cout << s->isMult() << std::endl;
            };
        }
    }
}

#endif //PAXENGINE3_STATICMEMBER_H
