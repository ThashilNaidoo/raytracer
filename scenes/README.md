# Test scenes

Large mesh files are git-ignored. Download them into this folder:

| Scene | Used from | Source |
|---|---|---|
| Stanford Bunny | Week 2 | [Morgan McGuire's Computer Graphics Archive](https://casual-effects.com/data/) (`bunny`) |
| Crytek Sponza | Week 2–3 (benchmark scene) | [Morgan McGuire's Computer Graphics Archive](https://casual-effects.com/data/) (`sponza`) |

The Cornell box is simple enough to define in code (`src/scene/`), so it needs no download.

Expected layout:

```
scenes/
├── bunny/bunny.obj
└── sponza/sponza.obj (+ .mtl and textures/)
```
