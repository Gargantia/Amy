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
#include "gtkplayer.h"

static gint quit(GtkWidget *widget, GdkEventAny *event, gpointer data)
{
	GtkPlayer * p = (GtkPlayer *)data;
	gtk_player_stop(p);
	gtk_main_quit();
	exit(0);
}

int main(int argc,char *argv[])
{
	/*we need a window*/
	GtkWidget *main_window, *box;
	/*and a player*/
	GtkPlayer *player;
	
	if(argc < 2) {
		printf("usage: %s file\n",argv[0]);
		exit(-1);
	}
	/*standard gtk stuff*/
	gtk_init(&argc,&argv);
	main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	box = gtk_vbox_new(FALSE,2);
	/*create player and integrate it*/
	player = gtk_player_new(argv[1]);
	
	gtk_container_add(GTK_CONTAINER(main_window), box);
	/* you could also don't use a box 
	 * or use gtk_container_add(GTK_CONTAINER(box), player->widget);
	 */
	gtk_box_pack_start(GTK_BOX(box), player->widget,TRUE,TRUE,0);
	 
    gtk_signal_connect(GTK_OBJECT(main_window), "delete_event", GTK_SIGNAL_FUNC(quit), player);
                           
	g_signal_connect_swapped(G_OBJECT(main_window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);
	/*init player*/
	gtk_player_init(player);
	gtk_widget_show(main_window);
	gtk_widget_show(box);
	/*show player (the parent tree has to show)*/
	gtk_player_show(player);
	/*start player*/
	gtk_player_start(player);
	gtk_main();
}
