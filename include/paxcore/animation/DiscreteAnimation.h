//
// Created by Paul Bittner on 31.01.2021.
//

#ifndef MESHFOLD_DISCRETEANIMATION_H
#define MESHFOLD_DISCRETEANIMATION_H

#include <vector>
#include <polypropylene/log/Errors.h>
#include "Timing.h"
#include "AnimationBehaviour.h"

namespace PAX {
    template<typename T>
    class DiscreteAnimation {
    public:
        struct KeyFrame {
            T value;
            Time::Timespan duration;

            KeyFrame(const T& val, double seconds)
            : value(val), duration(seconds) {}
        };

    private:
        std::vector<KeyFrame> frames;
        Time::Timespan totalDuration;
        // I wanted to make these const but then move and copy constructors are deleted.
        AnimationBehaviour behaviour;
        Time::Timepoint startTime;

    public:
        explicit DiscreteAnimation(const std::vector<KeyFrame> & frames, AnimationBehaviour behaviour = AnimationBehaviour::LOOP)
        : frames(frames), behaviour(behaviour), totalDuration(0) {
            for (const KeyFrame & frame : frames) {
                totalDuration += frame.duration;
            }
        }

        void start() {
            startTime = Time::Clock::now();
        }

        const T & getValue() {
            Time::Timespan timePassed = Time::Clock::now() - startTime;

            bool reverse = false;

            switch (behaviour) {
                case AnimationBehaviour::ONCE: {
                    if (timePassed >= totalDuration) {
                        return frames.back().value;
                    }
                    break;
                }
                case AnimationBehaviour::LOOP: {
                    timePassed = Time::Modulo(timePassed, totalDuration);
                    break;
                }
                case AnimationBehaviour::PINGPONG: {
                    // Let i describe the ith time we repeat the animation.
                    // When i is odd, we have to reverse.
                    reverse = int(timePassed / totalDuration) % 2 == 1;
                    break;
                }
                default: {
                    PAX_NOT_IMPLEMENTED_EXCEPTION();
                }
            }

            // Avoid the duplicate loop body here is hard because we cannot abstract
            // over iterators rbegin() and begin(). :/
            if (reverse) {
                for (auto it = frames.rbegin(); it != frames.rend(); ++it) {
                    if (timePassed <= it->duration) {
                        return it->value;
                    }
                    timePassed -= it->duration;
                }
            } else {
                for (auto it = frames.begin(); it != frames.end(); ++it) {
                    if (timePassed <= it->duration) {
                        return it->value;
                    }
                    timePassed -= it->duration;
                }
            }
        }

        PAX_NODISCARD const std::vector<KeyFrame> & getFrames() const {
            return frames;
        }

        PAX_NODISCARD const AnimationBehaviour & getBehaviour() const {
            return behaviour;
        }
    };
}

#endif //MESHFOLD_DISCRETEANIMATION_H
