add_library(paxio
        Keyboard.cpp
        Mouse.cpp
        Window.cpp
        event/ResolutionChangedEvent.cpp
        properties/InputAbilityController.cpp Keys.cpp)
add_library(PaxEngine3::paxio ALIAS paxio)
target_link_libraries(paxio PUBLIC paxutil paxcore)
