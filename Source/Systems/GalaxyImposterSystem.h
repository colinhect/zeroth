///////////////////////////////////////////////////////////////////////////////
// This source file is part of Zeroth.
//
// Copyright (c) 2017 Colin Hill
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Hect.h>
using namespace hect;

#include "Export.h"

namespace zeroth
{

/// \system
class ZEROTH_EXPORT GalaxyImposterSystem :
    public System<GalaxyImposterSystem>
{
public:
    GalaxyImposterSystem(Scene& scene);

    void initialize();

    void adapt_to_observer(Vector3 position, Quaternion rotation);

private:
    Entity::Iterator create_cell(Vector3 local_position, double size, Entity::Iterator parent_cell = Entity::Iterator());

    std::vector<Entity::Handle> _root_cells;

    // The maximum visibility distance; set to the radius of the obserable
    // universe in megaparsecs
    const double _max_visibility_distance { 14000.0 };

    const double _root_cell_size { 1000.0 };
};

}
