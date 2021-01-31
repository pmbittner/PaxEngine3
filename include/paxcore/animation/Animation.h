//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_ANIMATION_H
#define PAXENGINE3_ANIMATION_H

#include "Timing.h"
#include "AnimationBehaviour.h"

namespace PAX {
    template<typename T>
    class Animation {
        T min, max;
        T* value = nullptr;

        Time::Timespan seconds;
        Time::Timepoint startTime;

        bool running = false;

    protected:
        double interpolate(Time::Timepoint time) {
            return (time - startTime) / seconds;
        }

    public:
        AnimationBehaviour overflowBehaviour = AnimationBehaviour::LOOP;

        Animation(T min, T max, double seconds, T* value, AnimationBehaviour overflowBehaviour = AnimationBehaviour::LOOP) :
                min(min), max(max),
                seconds(seconds),
                value(value),
                overflowBehaviour(overflowBehaviour)
        {

        }

        void start() {
            *value = min;
            startTime = Time::Clock::now();
            running = true;
        }

        void stop() {
            //*value = min;
            running = false;
        }

        void update() {
            if (running) {
                double i = interpolate(Time::Clock::now());
                if (i > 1) {
                    switch (overflowBehaviour) {
                        case AnimationBehaviour::PINGPONG: {
                            T temp = max;
                            max = min;
                            min = temp;
                            // no break;
                        }

                        case AnimationBehaviour::LOOP: {
                            --i;
                            startTime += seconds;
                            break;
                        }

                        case AnimationBehaviour::ONCE: {
                            stop();
                            return;
                        }
                    }
                }
                *value = T(i * (max - min)) + min;
            }
        }
    };
}

#endif //PAXENGINE3_ANIMATION_H
