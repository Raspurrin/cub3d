/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legenda_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 01:14:49 by mialbert          #+#    #+#             */
/*   Updated: 2023/02/16 02:17:33 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*skip_spaces(char **file)
{
	size_t	end;

	end = 0;
	while (ft_isspace(**file))
		(*file)++;
	while (!ft_isspace((*file)[end]))
		end++;
	return (ft_substr(*file, 0, end));
}

/**
 * Extracting the string for the colour of the ceiling or the floor
 * and converting it to a usable integer.
 * @param colour_str example: "220,100,0"
 */
static void	extract_colour(t_data *data, char *colour_str, t_colour *colour)
{
	int32_t	i;
	int32_t	j;
	size_t	channel_count;
	uint8_t	colour_int;
	char	**channels;

	i = 2;
	j = 0;
	channels = ft_split(colour_str, ',');
	channel_count = ft_2darrlen(channels);
	if (channel_count != 3)
		errno(COLOUR, "", data);
	colour->a = 0;
	while (i >= 0)
	{
		colour_int = ft_atoi(channels[i]);
		if (colour_int < 0 || colour_int > 255)
			errno(COLOUR, "", data);
		colour->bgra[j] = colour_int;
		i--;
		j++;
	}
}

static void	legenda_check(t_data *data, char *word, char *path)
{
	if (!data->ceiling && ft_strcmp(word, "C") == 0)
	{
		data->ceiling = malloc(sizeof(t_colour));
		extract_colour(data, path, data->ceiling);
	}
	else if (!data->floor && ft_strcmp(word, "F") == 0)
	{
		data->floor = malloc(sizeof(t_colour));
		extract_colour(data, path, data->floor);
	}
	else if (!data->texture[NORTH].img->ptr && ft_strcmp(word, "NO") == 0)
		init_texture(data, &data->texture[NORTH], path);
	else if (!data->texture[SOUTH].img->ptr && ft_strcmp(word, "SO") == 0)
		init_texture(data, &data->texture[SOUTH], path);
	else if (!data->texture[WEST].img->ptr && ft_strcmp(word, "WE") == 0)
		init_texture(data, &data->texture[WEST], path);
	else if (!data->texture[EAST].img->ptr && ft_strcmp(word, "EA") == 0)
		init_texture(data, &data->texture[EAST], path);
	else
		errno(INV_CHAR, "", data);
}

void	element_check(t_data *data, char **file)
{
	size_t	len;
	char	*word;
	char	*path;
	size_t	i;

	i = 0;
	while (i < 6 && *file && **file)
	{
		word = skip_spaces(file);
		len = ft_strlen(word);
		if (len < 1 || len > 2)
			errno(INV_CHAR, "", data);
		*file += len;
		path = skip_spaces(file);
		legenda_check(data, word, path);
		*file += ft_strlen(path);
		i++;
	}
}
