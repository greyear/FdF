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

empty map - gives "Invalid map: success", no leaks

new line - opens window without image, no leaks

map with 1 point,- opens window without image, but why? need to write separate function for 1 point

2 points - draws a line, no leaks

folder fdf - "Invalid map: is a directory", no leaks

not rectangular - work, but is it okay?
specificly:
- with extra symbol - doesn't draw, no leaks
- without symbol - draws, no leaks

mars - 
*/