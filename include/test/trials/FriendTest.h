//
// Created by Paul on 27.05.2017.
//

#include <string>
#include <iostream>

namespace PAX {
    namespace TEST {
        class Base {
            friend class Friend;
            virtual std::string getName() {
                return "Base";
            }
        };

        class Derived : public Base {
            virtual std::string getName() override {
                return "Derived";
            }
        };

        class Friend {
        public:
            void run(Base *base) {
                std::cout << base->getName() << std::endl;
            }
        };

        int FriendTest() {
            Derived d;
            Base *b = &d;
            Friend f;

            f.run(&d);
            f.run(b);

            return 1;
        }
    }
}