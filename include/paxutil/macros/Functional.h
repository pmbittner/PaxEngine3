//
// Created by paul on 20.02.21.
//

#ifndef MESHFOLD_FUNCTIONAL_H
#define MESHFOLD_FUNCTIONAL_H

#define _PAX_FORALL(collection, f, eval) do { for (const auto& x : collection) { x eval f; } } while(0)
#define PAX_FORALL(collection, f) _PAX_FORALL(collection, f, .)
#define PAX_FORALL_ON_POINTERS(collection, f) _PAX_FORALL(collection, f, ->)

#endif //MESHFOLD_FUNCTIONAL_H
