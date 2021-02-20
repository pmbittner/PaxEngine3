//
// Created by paul on 20.02.21.
//

#ifndef MESHFOLD_FUNCTIONAL_H
#define MESHFOLD_FUNCTIONAL_H

#define _PAX_FMAP(collection, f, eval) do { for (const auto& x : collection) { x eval f; } } while(0)
#define PAX_FMAP(collection, f) _PAX_FMAP(collection, f, .)
#define PAX_FMAP_ON_POINTERS(collection, f) _PAX_FMAP(collection, f, ->)

#endif //MESHFOLD_FUNCTIONAL_H
