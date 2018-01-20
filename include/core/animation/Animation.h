//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_ANIMATION_H
#define PAXENGINE3_ANIMATION_H

#include <chrono>

namespace PAX {
    template<typename T>
    class Animation {
        typedef std::chrono::duration<double> Timespan;
        typedef std::chrono::time_point<std::chrono::high_resolution_clock, Timespan> Timepoint;
        typedef std::chrono::high_resolution_clock Clock;

        T _min, _max;
        T* _value = nullptr;

        Timespan _seconds;
        Timepoint startTime;

        bool _running = false;

    protected:
        double interpolate(Timepoint time) {
            return (time - startTime) / _seconds;
        }

    public:
        Animation(T min, T max, double seconds, T* value) :
                _min(min), _max(max),
                _seconds(seconds),
                _value(value) {

        }

        void start() {
            *_value = _min;
            startTime = Clock::now();
            _running = true;
        }

        void stop() {
            *_value = _min;
            _running = false;
        }

        void update() {
            if (_running) {
                double i = interpolate(Clock::now());
                if (i > 1) { // LOOP behaviour
                    --i;
                    startTime += _seconds;
                }
                *_value = i * (_max - _min) + _min;
            }
        }
    };
}

#endif //PAXENGINE3_ANIMATION_H
