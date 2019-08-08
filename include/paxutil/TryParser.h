//
// Created by Bittner on 08.08.2019.
//

#ifndef PAXENGINE3_TRYPARSER_H
#define PAXENGINE3_TRYPARSER_H

namespace PAX {
    template<class From, class To>
    class TryParser {
    public:
        [[nodiscard]] static To tryParse(const From & f) {
            return f;
        }
    };
}

#endif //PAXENGINE3_TRYPARSER_H
