/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_in_thread.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/18 19:00:39 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/26 18:42:51 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEM_IN_THREAD
# define LEM_IN_THREAD
# include "lem_in.h"
# include <pthread.h>

typedef struct		s_info_thread
{
	UINT			rooms;
	UINT			tubes;
}					t_info_thread;

typedef struct		s_thread
{
	pthread_t		pth;
	unsigned int	id;
	char			*file_line;
	UINT			section;
	t_data			*data;
	t_info_thread	*thread;
}					t_thread;

t_bool				multithread_get_room(char *file_line, t_data *data,
		t_info_thread *t);
void				get_room_thread_main(char *file_line, t_data *data,
		t_thread thread);
void				multithread_get_tube(char *file_line, t_data *data,
		t_info_thread *t);
void				get_tube_thread_main(char *file_line, t_data *data,
		t_thread tube, char *line);
void				launch_check_tube_thread(t_thread (*thread)[NB_THREAD],
		t_data *data);
t_bool				multithread_malloc_nodes(t_data *data);
t_bool				multithreading_get_nodes(t_data *data);
void				get_nodes_thread_main(t_data *data, UINT start, UINT end,
		UINT max_room);
char				*scan_line_line_for_threading(char *s, unsigned int id);
t_bool				skip_ants_number_for_threading(char *s, UINT id);
char				*skip_room_for_multithreading(char *s, UINT id);
#endif
