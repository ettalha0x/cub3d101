CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -O3
MLXFLAGS	=	 dependencies/packages/MLX/libmlx42.a -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
RM			=	rm -rf
NAME		=	cub3d

LIBFT		=	dependencies/packages/libft/libft.a

GNL			=	dependencies/packages/gnl/get_next_line.c dependencies/packages/gnl/get_next_line_utils.c

				
PARSING		=	dependencies/parsing/free2d.c dependencies/parsing/print_err.c\
				dependencies/parsing/safe_exit.c dependencies/parsing/read_file.c\
				dependencies/parsing/check_map.c dependencies/parsing/init_data.c\
				dependencies/parsing/valid_name.c dependencies/parsing/file_exist.c\
				dependencies/parsing/extract_assets.c dependencies/parsing/check_assets.c\
				dependencies/parsing/check_terrain.c dependencies/parsing/extract_player.c\
				dependencies/parsing/color_processing.c dependencies/parsing/refining_spaces.c


GRAPHICS	=	dependencies/graphics/init_game.c dependencies/graphics/player_movements.c\
				dependencies/graphics/3d_projection.c dependencies/graphics/init_projection.c\
				dependencies/graphics/get_intersection/get_intersection.c\
				dependencies/graphics/get_intersection/get_horz_intersection.c\
				dependencies/graphics/get_intersection/get_vert_intersection.c

BNS_GRAPHICS	=	bonus_dependencies/graphics/init_game.c bonus_dependencies/graphics/player_movements.c\
					bonus_dependencies/graphics/3d_projection.c bonus_dependencies/graphics/init_projection.c\
					bonus_dependencies/graphics/get_intersection/get_intersection.c\
					bonus_dependencies/graphics/get_intersection/get_horz_intersection.c\
					bonus_dependencies/graphics/get_intersection/get_vert_intersection.c\
					bonus_dependencies/graphics/draw_minimap.c

EXEC		=	main.c

PARSOBJ		=	$(PARSING:.c=.o)
GRPHOBJ		=	$(GRAPHICS:.c=.o)
BNSOBJ		=	$(BNS_GRAPHICS:.c=.o)
EXOBJ		=	$(EXEC:.c=.o)
GNLOBJ		=	$(GNL:.c=.o)



all			:	$(NAME)


$(NAME)		:	$(LIBFT) $(GNLOBJ) $(PARSOBJ) $(GRPHOBJ) $(EXOBJ)
	$(CC) $(CFLAGS) $(EXOBJ) $(PARSOBJ) $(GRPHOBJ) $(GNLOBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)


bonus		:	$(LIBFT) $(GNLOBJ) $(PARSOBJ) $(BNSOBJ) $(EXOBJ)
	$(CC) $(CFLAGS) $(EXOBJ) $(PARSOBJ) $(BNSOBJ) $(GNLOBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)


$(LIBFT)	:
	make -C dependencies/packages/libft


clean		:
	$(RM) $(MODOBJ) $(GNLOBJ) $(EXOBJ) $(PARSOBJ) $(GRPHOBJ) $(BNSOBJ)
	make -C dependencies/packages/libft clean


fclean		:	clean
	$(RM) $(NAME) $(LIBFT)


re			:	fclean all
