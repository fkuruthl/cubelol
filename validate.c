/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:36:29 by inkahar           #+#    #+#             */
/*   Updated: 2025/01/04 19:36:20 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <ctype.h>

void validate_file_format(char *filename) {
    char *line;
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        exit(perror_cube3d("Error opening file for format validation", 0));

    int config_lines = 0, map_started = 0;
    while ((line = get_next_line(fd))) {
        // Trim leading/trailing spaces for better matching
        char *trimmed_line = line;
        while (*trimmed_line && isspace(*trimmed_line)) trimmed_line++;  // Skip leading spaces
        if (*trimmed_line == '\0') {  // Skip empty lines
            free(line);
            continue;
        }

        if (is_valid_config_line(trimmed_line)) {
            if (map_started) {
                // If we have already started reading map lines, ignore any config lines after that
                free(line);
                continue;
            }
            config_lines++;  // Count configuration lines before the map starts
        } else if (is_valid_map_line(trimmed_line)) {
            map_started = 1;  // Map section starts here
        } else if (map_started) {
            // Ignore non-map lines after the map starts
            free(line);
            continue;
        } else {
            // If we encounter a non-config, non-map line before the map starts
            fprintf(stderr, "Error: Unexpected line before map section: '%s'\n", line);
            free(line);
            close(fd);
            exit(perror_cube3d("Unexpected line before map section", 0));
        }

        free(line);
    }

    if (config_lines != 6) {
        close(fd);
        exit(perror_cube3d("Missing or invalid configuration lines", 0));
    }

    close(fd);
}
