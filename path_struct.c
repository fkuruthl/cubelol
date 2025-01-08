/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:34:21 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/04 17:03:33 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cube.h"
int	ft_array_length(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	return (i);
}

static int is_map_empty(t_map *map) {
    return (!map->map);
}

static int is_end(int index, t_map *map) {
    int i = index + 1;
    while (map->map[i]) {
        if (ft_strlen(map->map[i]) > 0 && map->map[i][0] != ' ') {
            return 1; // Found a non-blank, non-empty line
        }
        i++;
    }
    return 0; // No additional valid map lines found
}



char **ft_dup_cpp(char **src, int len)
{
    char **dup;
    int i = 0;

    dup = (char **)malloc((len + 1) * sizeof(char *));
    if (!dup)
        return NULL;

    while (i < len && src[i])
    {
        dup[i] = ft_strdup(src[i]);
        if (!dup[i])
        {
            ft_free_pp((void **)dup);
            return NULL;
        }
        i++;
    }
    dup[i] = NULL;

    return dup;
}
char **skip_to_map(char **lines)
{
    char **map;
    int i = 0;
    int j = 0;
    size_t len;

    // Find the first valid map line
    while (lines[i])
    {
        // Ignore configuration lines and empty lines
        if (!ft_strncmp(lines[i], "NO", 2) || !ft_strncmp(lines[i], "SO", 2) || \
            !ft_strncmp(lines[i], "WE", 2) || !ft_strncmp(lines[i], "EA", 2) || \
            !ft_strncmp(lines[i], "F", 1) || !ft_strncmp(lines[i], "C", 1) || \
            ft_strlen(lines[i]) == 0)
        {
            i++;
            continue;
        }

        // If the line contains valid map characters, break
        if (ft_strchr(lines[i], '1') || ft_strchr(lines[i], '0') || \
            ft_strchr(lines[i], 'N') || ft_strchr(lines[i], 'E') || \
            ft_strchr(lines[i], 'W') || ft_strchr(lines[i], 'S'))
        {
            break;
        }

        i++;
    }

    // Ensure we found a valid starting point
    if (!lines[i])
    {
        perror_cube3d("Map section not found", 0);
        return NULL;
    }

    // Create a new array starting from the map part
    map = ft_dup_cpp(lines + i, ft_array_length(lines + i));
    if (!map)
    {
        perror_cube3d("Failed to allocate memory for the map", 0);
        return NULL;
    }

    // Trim trailing newlines from each line in the map
    j = 0;
    while (map[j])
    {
        len = ft_strlen(map[j]);
        if (len > 0 && map[j][len - 1] == '\n')
            map[j][len - 1] = '\0'; // Remove trailing newline
        j++;
    }

    return map;
}


static void formatmap(t_map *map) {
    int num_rows = 0, max_length = 0, length = 0;
    char **newmap;
    int i = 0, j;

    while (map->map[num_rows]) {
        length = ft_strlen(map->map[num_rows]);
        if (length > max_length)
            max_length = length;
        num_rows++;
    }

    newmap = (char **)malloc((num_rows + 1) * sizeof(char *));
    if (!newmap)
        exit(perror_cube3d("Memory allocation failed for formatted map", 0));
    newmap[num_rows] = NULL;

    for (i = 0; i < num_rows; i++) {
        newmap[i] = malloc(max_length + 1);
        if (!newmap[i]) {
            ft_free_pp((void **)newmap);
            exit(perror_cube3d("Memory allocation failed for row", 0));
        }
        strcpy(newmap[i], map->map[i]);
        length = ft_strlen(newmap[i]);
        for (j = length; j < max_length; j++)
            newmap[i][j] = ' ';
        newmap[i][max_length] = '\0';
    }

    ft_free_pp((void **)map->map);  // Free the original map
    map->map = newmap;  // Update map with formatted version
}


static int char_check(t_map *map) {
    int i = 0, j, player_count = 0;

    while (map->map[i]) {
        j = 0;
        while (map->map[i][j]) {
            char c = map->map[i][j];
            if (!ft_strchr(" 10NSWE\n", c)) {
                fprintf(stderr, "Invalid character '%c' found at [%d][%d]\n", c, i, j);
                return 0;
            }
            if (ft_strchr("NSWE", c)) {
                player_count++;
            }
            j++;
        }
        i++;
    }

    if (player_count != 1) {
        fprintf(stderr, "Invalid number of player starting positions: %d\n", player_count);
        return 0;
    }
    return 1;
}
static int is_closed(t_map *map, int i, size_t j) {
    if (map->map[i][j] == ' ') return 0;

    if (map->map[i][j] == '0') {
        if (i == 0 || j == 0 || !map->map[i + 1] || !map->map[i - 1]) {
            return 1; // Invalid boundary
        }
        if (map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' ' || 
            map->map[i][j - 1] == ' ' || map->map[i][j + 1] == ' ') {
            return 1; // Adjacent to space
        }
    }
    return 0;
}




static int check_isclosed(int i, t_map *map)
{
    size_t j = 0;

    while (map->map[i][j]) {
        if (is_closed(map, i, j)) {
            printf("Map closure validation failed at [%d][%zu]: '%c'\n", i, j, map->map[i][j]); // DEBUG
            return 1;
        }
        j++;
    }
    return 0;
}
int path_struct(t_map *map) {
    int i = 0;

    printf("%s", "inside path checker LOOOKING ");
    if (is_map_empty(map))
        exit(perror_cube3d("Map is empty", 0));

    formatmap(map);

    if (ft_array_length(map->map) < 3 || char_check(map) != 1)
        exit(perror_cube3d("Invalid map structure or player count", 0));

    while (map->map[i]) {
        if (ft_strlen(map->map[i]) == 0) {  // Blank line
            if (is_end(i, map)) {
                fprintf(stderr, "Unexpected blank line at row %d after map content\n", i);
                return 0;  // Invalid blank line after map
            }
            break;  // Valid blank line, stop processing further rows
        }

        if (check_isclosed(i, map)) {
            fprintf(stderr, "Validation failed at row %d\n", i);
            return 0;
        }
        i++;
    }

    printf("path checker LOOOKING DONE\n");
    return 1;
}
