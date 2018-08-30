//
// Created by Paul on 20.12.2017.
//

#ifndef PAXENGINE3_TUPLEPRINTER_H
#define PAXENGINE3_TUPLEPRINTER_H

#include <cstdlib>
#include <ostream>
#include <tuple>

#include <utility/stdutils/OstreamOverloads.h>

namespace PAX {
    namespace Util {
        template<class Tuple, std::size_t N>
        struct TuplePrinter {
            static void print(const Tuple& t, std::ostream &stream)
            {
                TuplePrinter<Tuple, N-1>::print(t, stream);
                stream << ", " << std::get<N-1>(t);
            }
        };

        template<class Tuple>
        struct TuplePrinter<Tuple, 1> {
            static void print(const Tuple& t, std::ostream &stream)
            {
                stream << std::get<0>(t);
            }
        };
    }
}

#endif //PAXENGINE3_TUPLEPRINTER_H
