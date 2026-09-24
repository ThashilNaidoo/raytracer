# raytracer

<!-- Replace with your hero render once you have one:
![Sponza, 1024 spp](docs/images/hero.png) -->

A multithreaded CPU path tracer in modern C++20, built for performance, with an SAH BVH, next event estimation and physically based materials.

![build](https://github.com/<your-username>/raytracer/actions/workflows/build.yml/badge.svg)

> **Status:** Week 1 in progress. Sections marked _TODO_ get filled in as the features land.

## Features

**Rendering**
- [ ] Path tracing with Russian roulette termination
- [ ] Lambertian, metal and dielectric materials (Schlick Fresnel)
- [ ] Positionable camera with depth of field
- [ ] Triangle meshes (OBJ)
- [ ] Emissive surfaces
- [ ] Next event estimation / multiple importance sampling
- [ ] Image textures
- [ ] _Stretch:_ GGX microfacet material

**Performance**
- [ ] SAH BVH with binned construction
- [ ] Flattened, cache-friendly BVH with iterative traversal
- [ ] Tile-based thread pool with per-thread RNG

## Results

_TODO (Week 3): fill these in with numbers from a Release build._

**Hardware:** _CPU model, core/thread count, RAM, OS / WSL2 or native_

| Scene | Triangles | Brute force | Midpoint BVH | SAH BVH | Speedup |
|---|---|---|---|---|---|
| Bunny | | | | | |
| Sponza | ~262k | | | | |

| Threads | 1 | 2 | 4 | 8 | max |
|---|---|---|---|---|---|
| Speedup | 1.0× | | | | |

## Design decisions

_TODO: write two or three short paragraphs covering why SAH, why a flattened BVH, why tile-based threading, and what you'd change next time._

## Gallery

_TODO: images with captions giving the samples per pixel (spp) and render time._

## Building

Requires CMake 3.21+, Ninja, and a C++20 compiler (GCC 13+, Clang 16+ or MSVC 19.36+).

```bash
cmake --preset release
cmake --build --preset release
ctest --preset release
./build/release/raytracer output/render.png
```

Other presets: `debug`, `asan` (AddressSanitizer + UBSan) and `ci` (portable, no `-march=native`).

## Project layout

```
src/math/       vec3, ray, aabb, orthonormal basis, rng
src/geometry/   sphere, triangle, mesh
src/accel/      BVH build + traversal
src/material/   BSDFs
src/render/     camera, integrator, thread pool, image output
src/scene/      OBJ loading, scene definitions
tests/          doctest unit tests
bench/          benchmark harness + results
```

## References

- Peter Shirley et al., [_Ray Tracing in One Weekend_ series](https://raytracing.github.io/)
- Pharr, Jakob & Humphreys, [_Physically Based Rendering_, 4th ed.](https://pbr-book.org/)
- Möller & Trumbore, _Fast, Minimum Storage Ray/Triangle Intersection_ (1997)
- Sean Barrett, [stb_image_write](https://github.com/nothings/stb) (public domain)

## Next steps

A real-time GPU renderer (OpenGL → Vulkan) implementing Frostbite-style PBR.
