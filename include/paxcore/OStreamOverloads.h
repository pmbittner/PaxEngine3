//
// Created by Paul Bittner on 31.01.2021.
//

#ifndef MESHFOLD_OSTREAMOVERLOADS_H
#define MESHFOLD_OSTREAMOVERLOADS_H

#include <paxutil/stdutils/OstreamOverloads.h>
#include "rendering/data/Shader.h"

std::ostream &operator<<(std::ostream &os, PAX::Shader::Flags const &flags);
std::ostream &operator<<(std::ostream &os, PAX::Shader::FileInfo const &fileInfo);

#endif //MESHFOLD_OSTREAMOVERLOADS_H
