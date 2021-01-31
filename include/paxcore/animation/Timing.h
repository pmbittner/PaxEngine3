//
// Created by Paul Bittner on 31.01.2021.
//

#ifndef MESHFOLD_TIMING_H
#define MESHFOLD_TIMING_H

#include <chrono>

namespace PAX::Time {
    using Clock = std::chrono::high_resolution_clock;
    using Seconds = std::chrono::seconds;
    using Timespan = std::chrono::duration<double>;
    using Timepoint = std::chrono::time_point<Clock, Timespan>;

    Timespan Modulo(Timespan lhs, Timespan rhs);
}

#endif //MESHFOLD_TIMING_H
