//
// Created by Paul Bittner on 29.01.2021.
//

#include <paxcore/state/StateMachine.h>

namespace PAX {
    StateMachine::StateMachine(const State & initialState, const std::vector <State*> &states)
    : initialState(initialState), states(states)
    {}

    const StateMachine::State & StateMachine::getCurrentState() const {
        return currentState;
    }
}