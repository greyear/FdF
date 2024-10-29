/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:52:30 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/01 19:38:37 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/*
+ 1 arg, 3 args - "Invalid arguments", no leaks

+ non existing - "Error opening file: No such file or directory", no leaks

+ empty map - gives "Invalid map", no leaks

+ new lines(s) - gives "Invalid map", no leaks
+ repeating spaces - gives "Invalid map", no leaks

another kind of spaces - 

+ map with 1 point - draws dot, no leaks

+ 2 points - draws a line, no leaks

+ folder fdf - "Invalid map: is a directory", no leaks

+ just existing folder - "Invalid map", no leaks

+ not rectangular
specificly:
- with extra symbol - gives "Map is not rectangular", no leaks
- without symbol - gives "Map is not rectangular", no leaks

+ mars - draws, no leaks

+ map with letters instead of number
 - with colors - gives "Input data error", no leaks
 - without colors - gives "Input data error", no leaks

+ maps with wrong put color

 + map with >MAX_INT, <MIN_INT - give "Input data error", no leaks
*/