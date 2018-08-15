
set(HEADERS_FOR_CLION
        # Header files for CLion
        ../../include/test/EntityTest.h
        ../../include/test/SDLTestApplication.h
        ../../include/test/SDLTestApplication2.h
        ../../include/test/trials/enum.h
        ../../include/test/trials/GenericTest.h
        ../../include/test/trials/GenericTypesInMapTest.h
        ../../include/test/trials/TrafoUnionTest.h
        ../../include/test/trials/PrivateHackTest.h

        ../../include/test/EventServiceTest.h
        ../../include/test/trials/FriendTest.h
        ../../include/test/trials/InheritanceTest.h
        ../../include/test/SceneGraphTest.h
        ../../include/test/trials/DelegateTest.h
        ../../include/test/trials/StaticMember.h
        ../../include/test/trials/SpecializedFunctionWithDifferentReturType.h
        ../../include/test/trials/InvisibleMixinTest.h
        ../../include/test/ResourcesTest.h
        ../../include/test/trials/AllocatorConstructorTest.h
        ../../include/test/trials/InheritedTemplateTypeTest.h)

add_executable(ResTest ResourceTest.cpp ${HEADERS_FOR_CLION})