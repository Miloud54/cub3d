# cub3D

A raycasting engine written in C, rendering a first-person 3D view of a 2D map with MiniLibX — inspired by the original Wolfenstein 3D. This is a project from the 42 core curriculum.

## 📋 Description

**cub3D** parses a custom `.cub` map/config file describing wall textures, floor/ceiling colors, and a 2D map layout, then renders it in real time from the player's point of view using raycasting (DDA algorithm). The player can move and rotate freely inside the map, with textured walls, a minimap, and — in the bonus part — doors and enemy sprites.

## 🎮 Features

- Real-time raycasting with wall textures depending on orientation (N/S/E/W)
- Player movement and rotation
- Strict `.cub` file parsing and map validation (closed map, valid characters, single player spawn, valid textures/colors)
- Minimap overlay
- **Bonus:** interactive doors and animated enemy sprites

## 🛠️ Build

```bash
make          # builds libft, minilibx and the cub3D executable
make clean    # cleans libft/minilibx object files and the objs directory
make fclean   # clean + removes the executable
make re       # fclean + make
```

## 🚀 Usage

```bash
./cub3D maps/valid/map1.cub
```

**Controls**
| Key | Action |
|---|---|
| `W` / `↑` | Move forward |
| `S` / `↓` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` / `→` | Rotate camera |
| `ESC` | Quit |
| Close button | Quit |

## 🗺️ Map file format (`.cub`)

| Identifier | Description |
|---|---|
| `NO` / `SO` / `WE` / `EA` | North/South/West/East wall texture paths |
| `F` | Floor color (R,G,B) |
| `C` | Ceiling color (R,G,B) |
| `0` | Empty walkable space |
| `1` | Wall |
| `N` `S` `E` `W` | Player spawn position and starting orientation |
| `D` | Door (bonus) |
| Digits (e.g. `2`) | Enemy spawn (bonus) |

## 📁 Project structure

```
cub3D/
├── inc/
│   └── cub3d.h              # Structs, prototypes, constants
├── libft/                    # Personal libft (includes ft_printf and get_next_line)
├── minilibx-linux/           # MiniLibX graphics library
├── maps/                     # Valid, invalid and bonus test maps
├── textures/                 # Wall/door/enemy XPM sprites
├── srcs/
│   ├── main.c                 # Entry point
│   ├── map_init.c             # Game/map structures initialization
│   ├── handle_input.c         # Keyboard input dispatch
│   ├── movement.c             # Player movement and rotation logic
│   ├── close.c                # Window close handling
│   ├── frees.c                # Memory and resource cleanup
│   ├── utils.c                # General helper functions
│   ├── parsing/
│   │   ├── check_extension.c        # Validates the .cub file extension
│   │   ├── check_file_existence.c   # Validates the map file can be opened
│   │   ├── parsing_colors.c         # Parses floor/ceiling RGB values
│   │   ├── parsing_colors_utils.c   # Color parsing helpers
│   │   ├── parsing_textures.c       # Parses NO/SO/WE/EA texture paths
│   │   ├── parsing_player.c         # Finds and validates player spawn/orientation
│   │   ├── parsing_enemies.c        # Parses enemy spawn positions (bonus)
│   │   ├── parsing_door_validation.c # Validates door placement (bonus)
│   │   ├── parsing_map_storage.c    # Reads the map lines into memory
│   │   ├── parsing_map_utils.c      # Map dimension/content helpers
│   │   ├── parsing_map_validation.c # Validates the map is closed and well-formed
│   │   ├── parsing_exterior_map.c   # Flood-fill check that the map has no openings
│   │   ├── parsing_exterior_utils.c # Exterior-check helpers
│   │   ├── parsing_scene.c          # Orchestrates full config + map parsing
│   │   ├── parsing_scene_map.c      # Separates config section from map section
│   │   └── parsing_utils.c          # General parsing helpers
│   └── render/
│       ├── render.c              # Main render loop, calls raycasting per frame
│       ├── raycast.c             # Ray setup per column
│       ├── raycast_dda.c         # DDA algorithm for wall detection
│       ├── raycast_draw.c        # Wall column drawing dispatcher
│       ├── raycast_draw1.c       # Wall drawing helpers (part 1)
│       ├── raycast_draw2.c       # Wall drawing helpers (part 2)
│       ├── raycast_utils.c       # Raycasting math helpers
│       ├── textures.c            # Texture loading
│       ├── textures2.c           # Additional texture handling
│       ├── minimap.c             # Minimap rendering
│       ├── door.c                # Door rendering and interaction (bonus)
│       ├── enemies.c             # Enemy logic (bonus)
│       └── enemies_render.c      # Enemy sprite rendering (bonus)
├── Makefile
└── README.md
```

## ⚙️ How it works

1. `main` validates the `.cub` file extension and launches parsing via `parsing_scene.c`.
2. The config section (`NO`, `SO`, `WE`, `EA`, `F`, `C`) is parsed and validated (`parsing_textures.c`, `parsing_colors.c`), then the map section is extracted and stored (`parsing_scene_map.c`, `parsing_map_storage.c`).
3. The map is validated: rectangular padding, fully enclosed by walls (`parsing_exterior_map.c` flood-fill), valid characters only, and exactly one player spawn (`parsing_player.c`).
4. `map_init.c` sets up the MiniLibX window and game state, and `render.c` starts the main render loop.
5. For each frame, `raycast.c` casts one ray per screen column, `raycast_dda.c` steps through the grid until it hits a wall, and `raycast_draw.c` computes the wall slice height and draws the correctly oriented, textured column.
6. `handle_input.c` and `movement.c` update the player's position/angle each frame based on key state before the next render pass.
7. **Bonus:** `door.c` handles opening/closing doors on interaction, and `enemies.c` / `enemies_render.c` manage and render enemy sprites within the 3D view.

## ✅ Norm

The project follows the **42 Norm** (Norminette).
