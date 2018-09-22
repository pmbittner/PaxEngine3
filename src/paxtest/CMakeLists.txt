
set(HEADERS_FOR_CLION
        # Header files for CLion
        ../../include/paxtest/EntityTest.h
        ../../include/paxtest/SDLTestApplication.h
        ../../include/paxtest/SDLTestApplication2.h
        ../../include/paxtest/trials/enum.h
        ../../include/paxtest/trials/GenericTest.h
        ../../include/paxtest/trials/GenericTypesInMapTest.h
        ../../include/paxtest/trials/TrafoUnionTest.h
        ../../include/paxtest/trials/PrivateHackTest.h

        ../../include/paxtest/EventServiceTest.h
        ../../include/paxtest/trials/FriendTest.h
        ../../include/paxtest/trials/InheritanceTest.h
        ../../include/paxtest/SceneGraphTest.h
        ../../include/paxtest/trials/DelegateTest.h
        ../../include/paxtest/trials/StaticMember.h
        ../../include/paxtest/trials/SpecializedFunctionWithDifferentReturType.h
        ../../include/paxtest/trials/InvisibleMixinTest.h
        ../../include/paxtest/trials/AllocatorConstructorTest.h
        ../../include/paxtest/trials/InheritedTemplateTypeTest.h
        )

add_executable(NewTrafoTest newTrafoTest.cpp ${HEADERS_FOR_CLION})
target_link_libraries(NewTrafoTest paxutil)

add_executable(PathTest pathTest.cpp)
target_link_libraries(PathTest paxutil)

add_executable(GenericPropertiesTest trials/genericProperties.cpp)