/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 03:17:15 by selbouka          #+#    #+#             */
/*   Updated: 2025/08/30 10:38:10 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


int set_texture(char **texture_ptr, char *path)
{
    if (*texture_ptr != NULL)
        return (0);
    // .xpm
    printf ("%s|\n", path);
    int fd = open(path, O_RDONLY);
    
    if (fd < 0)
        return (0);
    close(fd);

    *texture_ptr = ft_strdup(path);
    return (*texture_ptr != NULL);
}

int set_color(t_rgb *color, char *rgb)
{
    char    **rgb_tokens;
    
    if (color->r != -1)
        return (0);
    
    if (count_char(rgb, ',') != 2)
        return (0);
    
    rgb_tokens = ft_split(rgb, ',');
    if (!rgb_tokens || !rgb_tokens[0] || !rgb_tokens[1] || !rgb_tokens[2] || rgb_tokens[3])
        return (0);
    
    // Validate and convert RGB values
    if (!is_valid_rgb(rgb_tokens[0]) || 
        !is_valid_rgb(rgb_tokens[1]) || 
        !is_valid_rgb(rgb_tokens[2]))
    {
        return (0);
    }
    color->r = ft_atoi(rgb_tokens[0]);
    color->g = ft_atoi(rgb_tokens[1]);
    color->b = ft_atoi(rgb_tokens[2]);
    return (1);
}

int set_item(t_vars *var, char *key, char *value)
{
    if (!key || !value)
        return (0);
    if (ft_strcmp(key, "NO") == 0)
        return (set_texture(&var->tex.north, value));
    else if (ft_strcmp(key, "SO") == 0)
        return (set_texture(&var->tex.south, value));
    else if (ft_strcmp(key, "WE") == 0)
        return (set_texture(&var->tex.west, value));
    else if (ft_strcmp(key, "EA") == 0)
        return (set_texture(&var->tex.east, value));
    else if (ft_strcmp(key, "DO") == 0)
        return (set_texture(&var->tex.door, value));
// color
    else if (ft_strcmp(key, "F") == 0)
        return (set_color(&var->floor, value));
    else if (ft_strcmp(key, "C") == 0)
        return (set_color(&var->ceiling, value));
    
    return (0);
}

bool firstArg(char *key)
{
    if (!key)
        return (NULL);
    if (ft_strcmp(key, "NO") == 0)
        return (true);
    else if (ft_strcmp(key, "SO") == 0)
        return (true);
    else if (ft_strcmp(key, "WE") == 0)
        return (true);
    else if (ft_strcmp(key, "EA") == 0)
        return (true);
    else if (ft_strcmp(key, "DO") == 0)
        return (true);
    else if (ft_strcmp(key, "F") == 0)
        return (true);
    else if (ft_strcmp(key, "C") == 0)
        return (true);
    return (false);
}

char **splitarg(char *line)
{
    char **tokens;
    int i;
    int start;
    int len;

    i = 0;
    tokens = ft_malloc(sizeof(char *) * 3, 1);
    while (line[i] && line[i] == ' ')
        i++;
    start = i;
    while (line[i] && line[i] != ' ' && (i - start) < 2)
        i++;
    len = i - start;
    tokens[0] = ft_malloc(len + 1, 1);
    ft_strlcpy(tokens[0], line + start, len + 1);
    if (!firstArg(tokens[0]))
        return (write(2, "Invalid line format", 20), NULL);
    while (line[i] && line[i] == ' ')
        i++;
    tokens[1] = ft_strtrim(line + i);
    tokens[2] = NULL;

    return tokens;
}



int parse_header(t_vars *var)
{
    char    *line;
    char    **tokens;
    int     items_found = 0;
    
    while (items_found < 7)
    {
        line = get_next_line(var->fd);
        // printf ("%s\n", line);
        if (!line)
        {
            err("Missing header items");
            return (0);
        }
        if (ft_strlen(line) == 0 || is_whitespace_only(line))
        {
            line = NULL;
            continue ;
        }
        // if (line[ft_strlen(line) - 1] == '\n')
        //     line[ft_strlen(line) - 1] = 0;
            
        // tokens = ft_split(line, ' ');
        tokens = splitarg(line);
        
        if (!tokens || !tokens[0] || !tokens[1] || tokens[2]) 
        {
            // printf ("{%s} | {%s} | {|%s|} \n", tokens[0], tokens[1], tokens[2]);
            return (err("Invalid line format"), 0);
        }
        
        if (set_item(var, tokens[0], tokens[1]))
            items_found++;
        else
        {
            // printf  ("\n(%s)          |      {%s}\n", tokens[0], tokens[1]);
            return (err("Invalid or duplicate item"), 0);
        }
    }
    return (1);
}