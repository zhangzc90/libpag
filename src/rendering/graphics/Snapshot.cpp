/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Tencent is pleased to support the open source community by making libpag available.
//
//  Copyright (C) 2021 THL A29 Limited, a Tencent company. All rights reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
//  except in compliance with the License. You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  unless required by applicable law or agreed to in writing, software distributed under the
//  license is distributed on an "as is" basis, without warranties or conditions of any kind,
//  either express or implied. see the license for the specific language governing permissions
//  and limitations under the license.
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "Snapshot.h"
#include "base/utils/MatrixUtil.h"
#include "gpu/Surface.h"
#include "rendering/caches/RenderCache.h"

namespace pag {
bool Snapshot::hitTest(RenderCache* cache, float x, float y) const {
  Point local = {x, y};
  if (!MapPointInverted(matrix, &local)) {
    return false;
  }
  auto surface = Surface::Make(cache->getContext(), 1, 1);
  if (surface == nullptr) {
    return false;
  }
  auto canvas = surface->getCanvas();
  canvas->setMatrix(Matrix::MakeTrans(-local.x, -local.y));
  canvas->drawTexture(texture.get());
  return surface->hitTest(0, 0);
}
}  // namespace pag