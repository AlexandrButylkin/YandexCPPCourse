//
// Created by cobak on 24.01.2022.
//

#ifndef TASK_1_TEXTURES__TEXTURES_H
#define TASK_1_TEXTURES__TEXTURES_H

#include "Common.h"
#include <memory>

std::unique_ptr<ITexture> MakeTextureSolid(Size size, char pixel);

std::unique_ptr<ITexture> MakeTextureCheckers(Size size, char pixel1,
                                              char pixel2);

std::unique_ptr<ITexture> MakeTextureCow();



#endif //TASK_1_TEXTURES__TEXTURES_H
