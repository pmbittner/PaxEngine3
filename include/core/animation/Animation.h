//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_ANIMATION_H
#define PAXENGINE3_ANIMATION_H

#include <chrono>

namespace PAX {
    template<typename T>
    class Animation {
        T _min, _max;
        T* _value = nullptr;

        std::chrono::duration<double> _seconds;
        std::chrono::high_resolution_clock::time_point startTime;
        std::chrono::high_resolution_clock::time_point pauseTime;

        bool _running = false;

    protected:
        double interpolate(std::chrono::high_resolution_clock::time_point time) {
            return (time - startTime) / _seconds;
        }

    public:
        Animation(T min, T max, double seconds, T* value) : _min(min), _max(max), _seconds(seconds), _value(value) {

        }

        void start() {
            startTime = std::chrono::high_resolution_clock::now();
            _running = true;
        }

        void stop() {
            _running = false;
        }

        void update() {
            if (_running) {
                *_value = interpolate(std::chrono::high_resolution_clock::now()) * (_max - _min) + _min;
            }
        }
    };
}

#endif //PAXENGINE3_ANIMATION_H
