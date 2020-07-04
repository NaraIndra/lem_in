/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstygg <mstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:46:12 by jstokes           #+#    #+#             */
/*   Updated: 2019/10/22 17:55:52 by mstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# define MAX_INT 2147483647
# define MIN_INT -2147483648
# include "../libft_t/includes/libft.h"
# include <fcntl.h>

# define NET_IS_BLOCKED 0
# define NET_IS_OPEN 1

typedef struct	s_path
{
	t_list			*list;
	size_t			len;
	struct s_path	*next;
}				t_path;

typedef struct	s_lemin
{
	t_hash_map	*map;
	t_list		*input;
	t_list		*list;
	t_list		*start;
	t_list		*end;
	t_list		*deleted_rooms;
	char		start_fl;
	char		end_fl;
	size_t		rooms;
	int			ants;
	t_list		*tmp_bfs_lev;
	t_list		*next_bfs_lev;
	t_path		*best_paths;
	t_path		*paths;
	t_list		**moves;
	t_list		**moves_start;
	int			*paths_num;
	int			moves_num;
	int			*for_ants_moves;
}				t_lemin;

/*
** READING_FUNCS
*/
t_lemin			*read_from_file(char *str);
t_lemin			*read_from_fd(int fd, int i);
char			**get_rooms(t_lemin *lemin, int fd);
void			get_connections(t_lemin *lemin, int fd, char **tmp, int j);
void			analize_command(t_lemin *lemin, char **tmp, int fd);
void			get_moves(t_lemin *lemin);
int				check_str(char *str, int j, int num);
int				check_link(t_list *lst, char *name);
void			add_line_to_input(t_lemin *lemin, char **line, int fd);

/*
** ALGO_FUNCS
*/
void			work_with_map(t_lemin *lemin);
void			reverse_path(t_lemin *lemin);
void			return_shortest_paths(t_lemin *lemin);
void			return_oriented_edges(t_lemin *lemin);
void			augmenting_reverse_paths(t_lemin *lemin);
void			return_all_other_edges(t_lemin *lemin);
int				compare_paths(t_lemin *lemin, int j);
char			new_bfs_augmenting_indexing(t_lemin *lemin);
int				bfs_index_layers_basic(t_lemin *lemin);
int				bfs_index_layers_augmentate(t_lemin *lemin);
void			augmenting_new_paths(t_lemin *lemin);
int				add_elem_n_choose_path(t_lemin *lemin,
								t_path *path, void *prev, void *tmp);

/*
** DELETE_FUNCS
*/
void			delete_unuseful_rooms(t_lemin *lemin);
int				delete_dead_ends(t_lemin *lemin);
void			delete_room(void *key, t_cont *key_cont, t_lemin *lemin);
void			delete_link(t_cont *cont, void *name);

/*
** PRINT_FUNCS
*/
void			print_usage(void);
void			print_error(void);
void			print_all_paths(t_path *path);
void			print_rooms_n_links(t_lemin *lemin);
void			print_input(t_lemin *lemin);
void			print_solution(t_lemin *lemin);

/*
**	CLEAN_FUNCS
*/
void			clean_lemin(t_lemin **lemin);
void			clean_n_error(t_lemin *lemin, char **mem, int fd);
void			strspl_cl_n_err(char **tmp, t_lemin *lemin,
							char **mem, int fd);
void			free_part(char ***tmp);

/*
** FT_LST_FUNCS
*/
char			**ft_strsplitest(char const *s);
void			ft_strsplitdel(char ***arr);
void			ft_lstdelstr(t_list **alst);
void			ft_lstaddend(t_list **alst, t_list *new);
size_t			ft_lstlen(t_list *alst);
void			ft_lstdelmid(t_list **lst, t_list **targ);
void			ft_lstprint(t_list *lst);
t_list			*ft_lstrelink(t_list *prev, t_list *tmp);

/*
** GRAPH_UTILITIES
*/
void			flush_levels_visits(t_lemin *lemin);
void			flush_visits(t_lemin *lemin);
void			put_next_short(t_lemin *lemin);
int				time_to_stop(t_lemin *lemin);
void			print_additional_path(t_lemin *lemin);
void			return_bfs_augm_index_edges(t_lemin *lemin);
void			bfs_indexing(t_lemin *lemin);
void			orientate_links(t_lemin *lemin);

t_cont			*create_cont(int x, int y);
void			delete_cont(t_cont **cont);
void			clean_all_cont(t_lemin *lemin);
t_lemin			*init_lemin(int fd);

/*
** T_PATH_FUNCS
*/
t_path			*new_path(void);
void			path_add_end(t_path **paths, t_path *path);
void			add_new_path(t_lemin *lemin);
void			del_path(t_path **path);
void			sort_paths(t_path **path);
int				check_verts(t_lemin *lemin);
char			is_sorted(t_path *path);
int				get_path_len(t_path *paths, int i);

/*
**DINIC_FORM_NET
*/
void			dinic_build_residual_network(t_lemin *lemin, int net_state);

/*
**DINIC_FIND_PATHS
*/
int				bfs_shortest(t_lemin *lemin);
int				bfs_augmenting(t_lemin *lemin);
int				bfs_index_layers(t_lemin *lemin);
int				bfs_del_layers(t_lemin *lemin);
void			bfs_erase_layers(t_lemin *lemin, void	*cont_i_name);
void			bfs_orientate(t_lemin *lemin);
void			bfs_erase_orient(t_lemin *lemin, void	*cont_i_name);
int				overflow_alert(t_lemin *lemin, void *testing_vertice_name);

/*
**NEW LST FUNCS
*/
t_list			*lst_create(void *content, size_t content_size);
t_list			*lst_push_front(t_list **lst, t_list *tmp);
t_list			*lst_push_back(t_list **lst, t_list *tmp);
t_list			*lst_pop_front(t_list **lst);
t_list			*lst_pop_back(t_list **lst);
void			lst_move_from_to(t_list **src, t_list **dst, void *name);
t_list			*lst_find_elem(t_list *src, void *name);
t_list			*lst_find_elem(t_list *src, void *name);
void			lst_del(t_list **lst);
t_list			*lst_push_back_void(t_list **lst, void *name);
t_list			*lst_push_front_void(t_list **lst, void *name);
void			*lst_pop_front_void(t_list **lst);
void			*lst_pop_back_void(t_list **lst);
void			lst_move_all_from_to(t_list **src, t_list **dst);
void			lst_p_b_v_pr(t_list **lst, void *name, t_lemin *lemin);

/*
** OTHER_FT_FUNCS
*/
int				ft_numabs(int i);
int				ft_nummax(int i, int j);
int				ft_nummin(int i, int j);

#endif
