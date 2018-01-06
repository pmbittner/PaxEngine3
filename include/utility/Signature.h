//
// Created by Paul on 03.10.2017.
//

#ifndef PAXENGINE3_SIGNATURE_H
#define PAXENGINE3_SIGNATURE_H

#include <tuple>
#include <string>
#include <sstream>
#include <utility/stdutils/TuplePrinter.h>

namespace PAX {
    class ISignature {
    public:
        virtual bool equals(ISignature *other) const = 0;
        virtual std::string toString() const = 0;
    };

    template<typename... S>
    class Signature : public ISignature {
    public:
        std::tuple<S...> _values;

        Signature(std::tuple<S...> values)
                : _values(values) {}

        Signature(S... values)
                : Signature<S...>(std::forward_as_tuple(values...)) {}

        Signature(Signature<S...> &toCopy)
                : Signature<S...>(toCopy._values) {}

        virtual std::string toString() const {
            std::stringstream ss;
            Util::TuplePrinter<decltype(_values), sizeof...(S)>::print(_values, ss);
            return ss.str();
        };

        bool equals(Signature<S...> const& rhs) const {
            return _values._Equals(rhs._values);
        }

        bool equals(S const&... rhs) const {
            // forward here to produce a tuple<S const&...> and avoid an unnecessary copy
            return _values == std::forward_as_tuple(rhs...);
        }

        virtual bool equals(ISignature *other) const override {
            Signature<S...> *concreteSignature = dynamic_cast<Signature<S...>*>(other);

            if (concreteSignature) {
                return Signature<S...>::equals(*concreteSignature);
            }

            return false;
        }
    };
}

#endif //PAXENGINE3_SIGNATURE_H
