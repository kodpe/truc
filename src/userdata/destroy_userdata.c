/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_userdata.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:11:51 by sloquet           #+#    #+#             */
/*   Updated: 2022/11/29 20:14:35 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	destroy_userdata(t_userdata *ud)
{
	free(ud->name);
	free(ud->personal_user_photo);
	free(ud->str_date);
	ft_memset(ud, 0, sizeof(t_userdata));
}

/* procedure

1. GET UD
2. play a game .. and add pieces_catch, sp_tiles_use, etc...
3. UPDATE UD with 1/0 and game_time_sec
4. SAVE UD
5. go to profil ..
6. GET UD with all updates , last date, etc...
*/
