//
// Created by Bittner on 18/01/2019.
//

#ifndef PAXENGINE3_DEFINITIONS_H
#define PAXENGINE3_DEFINITIONS_H

#define PAX_NON_CONST
#define PAX_IMPLICIT

#if PAX_CXX_STANDARD >= 17
#define PAX_CONSTEXPR_IF constexpr
#else
#define PAX_CONSTEXPR_IF
#endif


#endif //PAXENGINE3_DEFINITIONS_H
