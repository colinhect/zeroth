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
#include "StarSystemGeneratorSystem.h"

#include "Components/StarComponent.h"

using namespace zeroth;

StarSystemGeneratorSystem::StarSystemGeneratorSystem(Scene& scene) :
    System(scene),
    _star_archetype(scene, HECT_ASSET("Entities/Star.entity"))
{
}

void StarSystemGeneratorSystem::generate_star_system(RandomSeed seed)
{
    GeneratorInstance generator = create_generator(seed);
    create_star(generator);
}

StarSystemGeneratorSystem::GeneratorInstance StarSystemGeneratorSystem::create_generator(RandomSeed seed) const
{
    return GeneratorInstance(seed);
}

Entity& StarSystemGeneratorSystem::create_star(StarSystemGeneratorSystem::GeneratorInstance& generator)
{
    Entity& star_entity = _star_archetype->clone();

    Random random(generator);

    auto& star = star_entity.component<StarComponent>();
    star.absolute_magnitude = random.next(-10.0, 15.0);
    star.temperature = random.next(2000.0, 30000.0);

    star_entity.activate();
    return star_entity;
}
