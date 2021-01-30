//
// Created by Paul Bittner on 29.01.2021.
//

#ifndef PAXENGINE3_STATEMACHINE_H
#define PAXENGINE3_STATEMACHINE_H

#include <vector>
#include <PaxEngineIncludes.h>

namespace PAX {
    class StateMachine {
    public:
        struct State {
//            std::function<State*()
        };

        struct StateChangedEvent {
            const State & previous;
            const State & now;
        };

    private:
        std::vector<State*> states;
        State currentState;

    public:
        const State initialState;
        const EventHandler<StateChangedEvent> OnStateChanged;

        explicit StateMachine(const State & initialState, const std::vector<State*> & states);
        PAX_NODISCARD const State & getCurrentState() const;
    };
}

#endif //PAXENGINE3_STATEMACHINE_H
