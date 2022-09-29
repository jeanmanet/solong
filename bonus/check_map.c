/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanet <jmanet@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:08:55 by jmanet            #+#    #+#             */
/*   Updated: 2022/09/28 18:00:46 by jmanet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/solong_bonus.h"

int	spread_p(char **map, int x, int y)
{
	int	spread;

	spread = 0;
	if (map[y][x - 1] != '1' && map[y][x - 1] != 'P')
	{
		map[y][x - 1] = 'P';
		spread++;
	}
	if (map[y][x + 1] != '1' && map[y][x + 1] != 'P')
	{
		map[y][x + 1] = 'P';
		spread++;
	}
	if (map[y - 1][x] != '1' && map[y - 1][x] != 'P')
	{
		map[y - 1][x] = 'P';
		spread++;
	}
	if (map[y + 1][x] != '1' && map[y + 1][x] != 'P')
	{
		map[y + 1][x] = 'P';
		spread++;
	}
	return (spread);
}

int	final_check_map(char **map, t_data *session)
{
	int		check;
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	check = 1;
	while (y < session->maph)
	{
		if (map[y][x] == 'E')
			check = 0;
		if (map[y][x] == 'C')
			check = 0;
		if (map[y][x] == '\n')
		{
			x = 0;
			y++;
		}
		x++;
	}
	free_map(map);
	return (check);
}

int	map_path_verif(t_data *session)
{
	char	**temp_map;
	int		spread;
	size_t	x;
	size_t	y;

	temp_map = ft_importmap(session);
	spread = -1;
	while (spread)
	{
		spread = 0;
		x = 0;
		y = 0;
		while (y < session->maph)
		{
			if (temp_map[y][x] == 'P')
				spread += spread_p(temp_map, x, y);
			x++;
			if (temp_map[y][x] == '\n')
			{
				x = 0;
				y++;
			}
		}
	}
	return (final_check_map(temp_map, session));
}

void	check_map_is_rectangular(t_data *session)
{
	session->x = 0;
	session->y = 0;
	while (session->y < session->maph)
	{
		if ((ft_strlen(session->map[session->y])) != session->mapw)
			ft_exit_maperror(1, session);
		if ((session->y == 0 || session->y == session->maph - 1)
			&& session->map[session->y][session->x] != '1')
			ft_exit_maperror(2, session);
		if ((session->x == 0 || session->x == session->mapw - 1)
			&& session->map[session->y][session->x] != '1')
			ft_exit_maperror(2, session);
		session->x++;
		if (session->map[session->y][session->x] == '\n')
		{
			session->x = 0;
			session->y++;
		}
	}
}

void	check_map(t_data *session)
{
	check_map_is_rectangular(session);
	parsing_map(session);
	if (session->nbplayer != 1)
		ft_exit_maperror(3, session);
	if (session->nbcollect < 1)
		ft_exit_maperror(4, session);
	if (session->nbexit < 1)
		ft_exit_maperror(5, session);
	if (!map_path_verif(session))
		ft_exit_maperror(6, session);
}
