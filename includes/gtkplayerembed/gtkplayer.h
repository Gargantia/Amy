/*
 * GtkPlayer -- a GTK+ mplayer's embedder
 * Copyright (C) 2002 Colin Leroy <colin@colino.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __GTKPLAYER_H__
#define __GTKPLAYER_H__
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct _GtkPlayer GtkPlayer;

struct _GtkPlayer {
	GtkWidget	*widget;	/*the integrable widget */
	GtkWidget	*mySocket;	/*the socket (internal) */
	gchar  		*file;		/*filename (internal */
	guint32		xid;		/*X window handle (internal)*/
	int		    width;		/*widget's width*/
	int		    height;	    /*widget's height*/
	char        *vo;        /* player's mplayer video output device */
	gboolean	ready;		/*is the player ready (internal)*/
	int		    childpid;	    /*mplayer's pid (internal)*/
	guint		timer;		/*timer (internal)*/
};

/* create player */
GtkPlayer 	*gtk_player_new		(gchar		*file);
/*get integrable widget */
GtkWidget 	*gtk_player_get_widget	(GtkPlayer 	*player);
/*init player */
void		 gtk_player_init	(GtkPlayer	*player);
/* show player */
void		 gtk_player_show	(GtkPlayer	*player);
/* start player */
void		 gtk_player_start	(GtkPlayer	*player);
/* stop player */
void		 gtk_player_stop	(GtkPlayer	*player);
/* change played file */
void		 gtk_player_open_file	(GtkPlayer	*player,
					 gchar		*file);
/* check if player runs */
gboolean	 gtk_player_is_running	(GtkPlayer	*player);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
