add_subdirectory(paxutil)
add_subdirectory(paxcore)

set(PAX_INSTALLED_TARGETS paxutil paxio paxrendering paxcore ${PAX_INSTALLED_TARGETS} PARENT_SCOPE)
