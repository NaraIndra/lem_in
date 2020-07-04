/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstokes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 22:39:16 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/26 22:39:18 by jstokes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include "lemin.h"
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL2_gfxPrimitives.h>

# define VIS_USAGE 	"./lem-in < map_name | ./vis"
# define WIDTH		2000
# define HEIGHT		1100
# define ROOM_SIZE	100

typedef struct	s_vis
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	TTF_Font		*font;
	SDL_Texture		*background;
	SDL_Rect		*backgr_dims;
	SDL_Texture		*start_end_rooms;
	SDL_Texture		*other_rooms;
	SDL_Texture		*ant;
	SDL_Texture		*reload;
	SDL_Texture		*next;
	char			close;
	char			ants_move;
	int				x_shift;
	int				y_shift;
	int				move;
}				t_vis;

t_vis			*create_vis(void);
SDL_Window		*create_window(t_vis *vis);
SDL_Renderer	*create_renderer(t_vis *vis);
SDL_Texture		*create_texture(t_vis *vis, char *name);
SDL_Texture		*create_sign(t_vis *vis, char *str, SDL_Color color);
SDL_Rect		*create_rect(int x, int y, int w, int h);

void			draw(t_lemin *lemin, t_vis *vis);
void			draw_ants(t_lemin *lemin, t_vis *vis, double num);

void			free_n_close(t_vis *vis);
void			vis_clean(t_vis **vis);

void			init_vis(t_vis *vis);

void			compute_shift(t_vis *vis, t_lemin *lemin);
SDL_Color		get_color(int red, int green, int blue, int alpha);
Uint32			color_to_uint(int red, int green, int blue, int alpha);

void			check_event(t_lemin *lemin, t_vis *vis);

void			update_ants_location(t_lemin *lemin, t_vis *vis);
void			init_ants_location(t_lemin *lemin);

#endif
