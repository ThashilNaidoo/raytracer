# Benchmarks

The harness starts in Week 2. Conventions to keep the numbers trustworthy:

- **Release preset only** (`cmake --preset release`). Never quote Debug or ASan timings.
- Fixed scene, resolution, spp and RNG seed for every run.
- Report the **median of 5 runs**, and note the machine (CPU, cores, WSL2 or native).
- Append results to `results.csv` with the columns
  `date,commit,scene,triangles,accel,threads,width,height,spp,ms,mrays_per_s`.
- Close other heavy apps. On WSL2, check that `nproc` matches your core count.
