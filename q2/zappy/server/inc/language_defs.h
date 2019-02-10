/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   language_defs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgelbard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 00:27:22 by jgelbard          #+#    #+#             */
/*   Updated: 2018/10/01 00:27:22 by jgelbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LANGUAGE_DEFS_H
# define LANGUAGE_DEFS_H

# ifndef USE_FRENCH
#  define SERVER_STRING_WELCOME "WELCOME\n"
#  define SERVER_STRING_ADVANCE "advance"
#  define SERVER_STRING_RIGHT "right"
#  define SERVER_STRING_LEFT "left"
#  define SERVER_STRING_SEE "see"
#  define SERVER_STRING_INVENTORY "inventory"
#  define SERVER_STRING_TAKE "take"
#  define SERVER_STRING_PUT "put"
#  define SERVER_STRING_KICK "kick"
#  define SERVER_STRING_BROADCAST "broadcast"
#  define SERVER_STRING_INCANTATION "incantation"
#  define SERVER_STRING_FORK "fork"
#  define SERVER_STRING_CONNECT_NBR "connect_nbr"
#  define SERVER_STRING_FOOD "food"
#  define SERVER_STRING_PLAYER "player"
#  define SERVER_STRING_DEATH "death\n"
#  define SERVER_STRING_MOVING "moving <K>\n"
# endif

# ifdef USE_FRENCH
#  define SERVER_STRING_WELCOME "BIENVENUE\n"
#  define SERVER_STRING_ADVANCE "avance"
#  define SERVER_STRING_RIGHT "droite"
#  define SERVER_STRING_LEFT "gauche"
#  define SERVER_STRING_SEE "voir"
#  define SERVER_STRING_INVENTORY "inventaire"
#  define SERVER_STRING_TAKE "prend"
#  define SERVER_STRING_PUT "pose"
#  define SERVER_STRING_KICK "expulse"
#  define SERVER_STRING_BROADCAST "broadcast"
#  define SERVER_STRING_INCANTATION "incantation"
#  define SERVER_STRING_FORK "fork"
#  define SERVER_STRING_CONNECT_NBR "connect_nbr"
#  define SERVER_STRING_FOOD "nourriture"
#  define SERVER_STRING_PLAYER "joueur"
#  define SERVER_STRING_DEATH "mort\n"
#  define SERVER_STRING_MOVING "deplacement <K>\n"
# endif

#endif
