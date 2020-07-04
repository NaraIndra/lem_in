# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jstokes <jstokes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/03 14:20:02 by jstokes           #+#    #+#              #
#    Updated: 2019/10/27 22:44:03 by jstokes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = srcs/clean_funcs.c srcs/ft_lstaddend.c srcs/ft_lstdelstr.c srcs/ft_lstlen.c \
		srcs/ft_strsplitdel.c srcs/ft_strsplitest.c srcs/t_cont_funcs.c \
		srcs/print_funcs.c srcs/read_from_fd.c srcs/read_from_file.c srcs/get_rooms.c \
		srcs/reading_tools.c srcs/work_with_map.c srcs/bfs.c srcs/get_connections.c \
		srcs/ft_lstdelmid.c srcs/delete_unuseful_rooms.c srcs/delete_dead_ends.c \
		srcs/orientate_links.c srcs/ft_lstprint.c srcs/ft_lstrelink.c \
		srcs/t_path_funcs.c srcs/sort_paths.c srcs/dinic_find_paths.c \
		srcs/input_keep.c srcs/dinic_build_network.c srcs/bfs_layers.c \
		srcs/dinic_restruct_graph.c srcs/dinic_graph_utilities.c  \
		srcs/lst_funcs1.c srcs/lst_funcs2.c srcs/get_moves.c srcs/lst_funcs3.c \
		srcs/reverse_path.c srcs/return_shortest_paths.c srcs/augmenting_new_paths.c \
		srcs/augmenting_reverse_paths.c srcs/compare_paths.c \
		srcs/new_bfs_augmenting_indexing.c srcs/add_elem_n_choose_path.c \
		srcs/print_solution.c \
		srcs/create_vis.c srcs/vis_clean.c srcs/ft_nummin.c srcs/ft_nummax.c \
		srcs/ft_numabs.c srcs/get_color.c \
		srcs/create_window.c srcs/create_renderer.c srcs/create_texture.c \
		srcs/compute_shift.c srcs/init_vis.c srcs/create_sign.c srcs/create_rect.c \
		srcs/draw.c srcs/check_event.c srcs/ants_location.c srcs/draw_ants.c

OBJ = $(SRC:.c=.o)
LIB = l
NAME = lem-in
NAME_VIS = vis

LIBFT_SRC = ./libft_t/libft.a
SDL_LIBRARY = $(HOME)/.brew/lib
SDL_HEADERS = $(HOME)/.brew/include

HEADERS_DIR = ./includes/

CFLAGS = -Wall -Werror -Wextra

LIBRARIES = -L$(SDL_LIBRARY) -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_gfx

all: $(LIB) $(NAME_VIS) $(NAME)

$(LIB):
	make -C libft_t/

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@ -I$(SDL_HEADERS)

$(NAME): $(OBJ) srcs/lemin.o
	gcc $(CFLAGS) $(LIBRARIES) $(LIBFT_SRC) -I$(HEADERS_DIR) -I$(SDL_HEADERS) $(OBJ) srcs/lemin.o -o $(NAME)

$(NAME_VIS): $(OBJ) srcs/visual.o
	gcc $(CFLAGS) $(LIBRARIES) $(LIBFT_SRC) -I$(HEADERS_DIR) -I$(SDL_HEADERS) $(OBJ) srcs/visual.o -o $(NAME_VIS)

clean:
	/bin/rm -rf *.o
	/bin/rm -rf ./srcs/*.o
	/bin/rm -rf ./libft_t/*.o

fclean: clean
	/bin/rm -rf $(NAME)
	/bin/rm -rf $(NAME_VIS)
	/bin/rm -rf $(LIBFT_SRC)

re:	fclean all
