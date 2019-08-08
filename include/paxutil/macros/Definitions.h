//
// Created by Bittner on 18/01/2019.
//

#ifndef PAXENGINE3_DEFINITIONS_H
#define PAXENGINE3_DEFINITIONS_H

#define PAX_NON_CONST
#define PAX_IMPLICIT

#ifdef UNREFERENCED_PARAMETER
#define PAX_UNREFERENCED_PARAMETER(P) UNREFERENCED_PARAMETER(P);
#else
#define PAX_UNREFERENCED_PARAMETER(P) (P);
#endif

#if PAX_CXX_STANDARD >= 17
#define PAX_CONSTEXPR_IF if constexpr
#else
#define PAX_CONSTEXPR_IF if
#endif

#define PAX_INTERNAL(name) _paxinternal_##name

#endif //PAXENGINE3_DEFINITIONS_H
