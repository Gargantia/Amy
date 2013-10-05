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

#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <errno.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include "gtkplayer.h"

/* forward declarations */
void        	 change_size		(GtkWidget *widget,
                                         GtkAllocation *allocation,
                                         gpointer user_data);

void		 gtk_player_restart	(GtkPlayer	*player);

/* constructor */
GtkPlayer 	*gtk_player_new		(gchar		*file)
{
	GtkPlayer *p;
	GtkWidget *w; 
	GtkWidget *s;
	gchar     *f;
	
	p = g_new0(GtkPlayer,1);
	w = gtk_vbox_new(FALSE,0);
	s = gtk_socket_new();
	f = g_strdup(file);
	
	gtk_signal_connect(GTK_OBJECT(w), "size-allocate", change_size, p);
	gtk_container_add (GTK_CONTAINER(w), s);
	
	p->widget   = w;
	p->mySocket = s;
	p->file     = f;
	p->vo       = "x11";
	p->ready    = FALSE;
	p->childpid = -1;
	p->timer    = 0;
	return p;
}

/* waits for size changes and restarts */
void change_size (GtkWidget *widget, GtkAllocation *allocation, gpointer user_data)
{
	GtkPlayer *p = (GtkPlayer *) user_data;
	int status;
	p->width  = allocation->width;
	p->height = allocation->height;
	printf("W:%d H:%d", allocation->width, allocation->height);
	if (p->ready)
		gtk_player_restart(p);
}

/* return the integrable widget */
GtkWidget 	*gtk_player_get_widget	(GtkPlayer 	*player)
{
	return player->widget;
}

/* init */
void gtk_player_init (GtkPlayer	*player)
{
	gtk_widget_realize(player->mySocket);
	player->xid = GDK_WINDOW_XWINDOW(player->mySocket->window);
	gtk_widget_show(player->mySocket);
}

/* show */
void gtk_player_show (GtkPlayer	*player)
{
	gtk_widget_show(player->widget);
}	

/* start reading */
void gtk_player_start (GtkPlayer *player)
{
	player->ready = TRUE;
}

/* helper to launch mplayer
 * Thanks to the GNU's system manpage ;-)
 */
int my_system (GtkPlayer *player, const char *command) {
	int pid, status;
	extern char **environ;
	if (command == 0)
		return 1;
	pid = fork();
	if (pid == -1)
		return -1;
	if (pid == 0) {
		char *argv[4];
		argv[0] = "sh";
		argv[1] = "-c";
		argv[2] = g_strdup(command);
		argv[3] = 0;
		execve("/bin/sh", argv, environ);
		exit(127);
		g_free(argv[0]);
		g_free(argv[1]);
		g_free(argv[2]);
		g_free(argv[3]);
	}
	do {
		if (waitpid(pid, &status, 0) == -1) {
			if (errno != EINTR)
				return -1;
		} else {
			player->childpid=pid+1; /*FIXME that's a hack, race condition could occur ? */
			return status;
		}
	} while(1);
}

/* stop player */
void gtk_player_stop (GtkPlayer	*player)
{
	if (player->childpid > 0) {
		kill(player->childpid, SIGINT);
		kill(player->childpid+1, SIGINT);
		player->childpid = -1;
	}
}

/* check for end of film (and relaunch mplayer) */
gint 		 check_pid		(gpointer 	 data) 
{
	GtkPlayer *player = (GtkPlayer *)data;
	gchar *path = g_strdup_printf("/proc/%d",player->childpid);
	FILE *fp = NULL;
	player->timer = gtk_timeout_add(1000, check_pid, player);
	if ((fp = fopen(path,"r")) == NULL)
		gtk_player_restart(player);
	else
		fclose(fp);
	g_free(path);
	
}

/* check if player runs */

gboolean	 gtk_player_is_running	(GtkPlayer	*player)
{
	if (!player->ready && player->childpid > 0)
		return TRUE;
	return FALSE;
}

/* restart film */
void		 gtk_player_restart	(GtkPlayer	*player)
{
	gchar *cmd;
	if (gtk_player_is_running(player)) {
		gtk_player_stop(player);
		player->ready = TRUE;
	}
	if (player->ready) {
		if (player->timer) {
			gtk_timeout_remove(player->timer);
			player->timer = 0;
		}

		cmd = g_strdup_printf("mplayer -vo %s -vf scale=%d:-3 -wid %d %s &", player->vo , player->width,player->xid, player->file);	
		player->ready = FALSE;
		player->timer = gtk_timeout_add(1000, check_pid, player);
		my_system(player,cmd);
		g_free(cmd);
	}
}

void		 gtk_player_open_file	(GtkPlayer	*player,
					 gchar		*file)
{
	player->file = g_strdup(file);
	if (gtk_player_is_running(player)) {
		gtk_player_restart(player);
	}
}
