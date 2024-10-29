/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azinchen <azinchen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:55:18 by azinchen          #+#    #+#             */
/*   Updated: 2024/10/29 18:55:20 by azinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

void	pic_params(t_extr e, t_draw *pic)
{
	pic->mult = find_zoom(e, pic->image->width, pic->image->height) * pic->zoom;
	pic->of_x = (pic->image->width - pic->mult * (e.b_x - e.s_x)) / 2
		+ pic->mv_x;
	pic->of_y = (pic->image->height - pic->mult * (e.b_y - e.s_y)) / 2
		+ pic->mv_y;
}
