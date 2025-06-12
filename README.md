# 🎨 OpenGL C++ Rendering Engine + JSON Map Loader
This is a personal graphics engine built in modern C++ using OpenGL, created as a learning project to better understand real-time rendering pipelines, game engine architecture, and file-based scene loading using custom JSON maps.

⚠️ Not production-ready — just a playground for experimenting and learning.

![ezgif-6b0b42fbc28102](https://github.com/user-attachments/assets/56000a06-3a3c-44c4-8004-4905257d5a28)

## ✨ Goals
- Learn modern OpenGL (3.3+)
- Build a flexible rendering pipeline from scratch
- Create a simple map/scene loader using JSON
- Experiment with camera movement, input, lighting, and shaders

## 🧱 Features So Far
- 🔺 Modern OpenGL rendering (VAOs, VBOs, shaders)
- 🗂️ Custom JSON-based map/scene loader
- 🧭 Basic first-person camera
- 🖼️ Texture loading (via stb_image)
- 🧪 Experimental shader system
  
## 📂 Folder Structure
```
.
├── assets
│   ├── maps
│   │   └── test_map.json
│   ├── models
│   └── textures
│       ├── ceiling.jpg
│       ├── crate.jpg
│       ├── floor.jpg
│       ├── wall.jpg
│       └── waltuh.jpg
├── include
│   ├── camera
│   │   └── camera.h
│   ├── core
│   │   ├── map.h
│   │   ├── renderer.h
│   │   ├── timer.h
│   │   └── window.h
│   ├── graphics
│   │   ├── mesh.h
│   │   ├── shader.h
│   │   └── texture.h
│   ├── lighting
│   │   └── light.h
│   ├── tools
│   │   ├── mesh_manager.h
│   │   ├── shader_manager.h
│   │   └── texture_manager.h
│   ├── utils
│   │   ├── gameobj.h
│   │   ├── geometry.h
│   │   ├── json_converter.h
│   │   └── transform.h
│   └── vendor
│       ├── glad
│       │   └── glad.h
│       ├── glad.c
│       ├── glm
│       │   └── ...
│       ├── json.hpp
│       ├── KHR
│       │   └── ...
│       └── stb_image.h
├── README.md
├── shaders
│   ├── cubes
│   │   ├── f_shader.glsl
│   │   └── v_shader.glsl
│   └── lightSource
│       ├── f_lightSource.glsl
│       └── v_lightSource.glsl
└── src
    ├── camera
    │   └── camera.cpp
    ├── core
    │   ├── map.cpp
    │   ├── renderer.cpp
    │   ├── timer.cpp
    │   └── window.cpp
    ├── graphics
    │   ├── mesh.cpp
    │   ├── shader.cpp
    │   └── texture.cpp
    ├── lighting
    │   └── light.cpp
    ├── main.cpp
    ├── tools
    │   ├── mesh_manager.cpp
    │   ├── shader_manager.cpp
    │   └── texture_manager.cpp
    └── utils
        ├── geometry.cpp
        ├── json_converter.cpp
        └── transform.cpp
```
        
## 🧩 Example JSON Map Format
```
[
  {
    "type": "wall",
    "position": [0, 0.5, -2.5],
    "rotation": [0.0, 90.0, 0.0],
    "scale": [0.1, 1, 5.0]
  },
  {
    "type": "wall",
    "position": [0, 0.5, 2.5],
    "rotation": [0.0, 90.0, 0.0],
    "scale": [0.1, 1, 5.0]
  },
  {
    "type": "lightSource",
    "position": [0.0, 1.0, 0.0],
    "rotation": [45.0, 45.0, 0.0],
    "scale": [1.0, 1.0, 1.0],
    "color": [1.0, 1.0, 1.0]
  }
]
```

## 🎮 Controls
Key	Action
W / A / S / D	Move camera
Mouse	Look around
ESC	Exit
P Polygon Mode

## 🧪 Notes
Built this mostly to get comfortable with raw OpenGL and engine architecture.
JSON scene loading was custom-built using nlohmann/json.
Things are still rough — lots of experimental code and TODOs.
Not optimized or modularized fully yet.

## 🛣️ Roadmap (Maybe Someday)
Shadow mapping
ECS-style entity system
UI/Debug overlays (ImGui?)
Model loading (e.g., OBJ/Assimp)

