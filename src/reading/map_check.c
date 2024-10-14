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
+ empty map - gives "Invalid map", no leaks

+ new lines(s) - gives "Invalid map", no leaks
repeating spaces - gives "Input data error", no leaks

another kind of spaces - 

map with 1 point - draws dot, no leaks

2 points - draws a line, no leaks

folder fdf - "Invalid map: is a directory", no leaks

not rectangular - work, but is it okay?
specificly:
- with extra symbol - doesn't draw, no leaks
- without symbol - draws, no leaks

mars - 
*/