# Cub3D

This project is written in c using mini-libx Library, This old library has a little builtin-funcs.

## Project Roadmap
### Leaks
- [X] refining_spaces function has a heap-buffer-overflow.
### Parsing
- [x]   check if the user provided a map.
- [x]   check map is a .cub file.
- [x]   check if the map file exist.
- [x]   read data from map file.
- [x]   divide map file info on t_data.
- [x]   check if textures are unique.
- [x]   check that textures are .xpm files.
- [x]   check that textures are accesable.
- [x]   check the color value for both floor and ceiling.
- [x]   extract map dimentions.
- [X]   check map characters.
- [X]   check map is walled of.
- [X]   extract player location.
- [X]   set player starting angle.
- [x]   provide context in error msgs.
- [X]   write description for each functions in .h file.
- [X]   check norminette.
- [x]   check memory leaks.
### Graphics
- [X]   game init window.
- [X]   draw minimap.
- [X]   draw minimap grid.
- [X]   draw minimap player (filled circle).
- [X]   move player all directions.
- [X]   player must not walk into the wall.
- [X]   draw a direction line (to know where the player is looking).
- [X]   draw a vue angle by casting rays line by line (60 degree).
- [X]   3D projection.
- [X]   Fixing wall distortion.
- [X]   replacing ceiling and floor with their dedicated color.
- [X]   projecting textures on 3d walls.
- [X]   write description for each functions in .h file.
- [X]   check norminette.
- [X]	check valgrind.
### Error Testing
- [X]   no map provided.
- [X]   empty map file.
- [X]   missing texture.
- [X]   map not .cub file.
- [X]   missing texture path.
- [X]   textures not .png file.
- [X]   map file doesnt exist.
- [X]   missing RGB values.
- [X]   incorrect RGB values.
- [X]   same texture for more than one side.
- [X]   missing texture file.
- [X]   missing floor or ceiling.
- [X]   player doesnt exist.
- [X]   only one player on map.
- [X]   invalid map character.
- [X]   texture path are repeated but one uses absolute path.
- [X]   map not walled off.
- [X]	spaces in the middle of the map.
- [X]   missing map.
- [X]	map file with less than 6 lines in total.
- [X]   check valgrind with all errors.

## Authors

- Oussama Kamili [@oussamakami](https://github.com/oussamakami)

- Noureddine Ettalhaouy [@ettalha0x](https://github.com/ettalha0x)