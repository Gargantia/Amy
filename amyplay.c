#include <gtk/gtk.h>

void show_about(GtkWidget *widget, gpointer data)
{

  //GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("battery.png", NULL);

  GtkWidget *dialog = gtk_about_dialog_new();
  gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), "Amy");
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "0.0.8"); 
  gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), 
      "(c) Gargantia Project");
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), 
     "AMY -((Advanced Media plaYer))- is a danmaku video client for the Gargantia Project");
  gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), 
      "http://github.com/Gargantia");
  //gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);
  //g_object_unref(pixbuf), pixbuf = NULL;
  gtk_dialog_run(GTK_DIALOG (dialog));
  gtk_widget_destroy(dialog);

}


int main( int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *vbox;

  GtkWidget *menubar;
  GtkWidget *filemenu;
  GtkWidget *file;
  GtkWidget *quit;
  GtkWidget *open_media;
  GtkWidget *open_comment;
  GtkWidget *connect_comment;
  GtkWidget *helpmenu;
  GtkWidget *help;
  GtkWidget *about;
  
  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
  gtk_window_set_title(GTK_WINDOW(window), "Amy - Danmaku Media Streamer");

  vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  menubar = gtk_menu_bar_new();
  filemenu = gtk_menu_new();
  helpmenu = gtk_menu_new();
  
  file = gtk_menu_item_new_with_label("File");
  open_media = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, NULL);//gtk_menu_item_new_with_label("Open Media...");
  open_comment = gtk_menu_item_new_with_label("Open Comment File...");
  connect_comment = gtk_menu_item_new_with_label("Connect Comment Server...");
  quit = gtk_menu_item_new_with_label("Quit");
  
  help = gtk_menu_item_new_with_label("Help");
  about = gtk_menu_item_new_with_label("About");
  
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open_media);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open_comment);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), connect_comment);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(help), helpmenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(helpmenu), about);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help);
  
  gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 3);

  g_signal_connect_swapped(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

  g_signal_connect(G_OBJECT(quit), "activate",
        G_CALLBACK(gtk_main_quit), NULL);
  
  g_signal_connect_swapped(G_OBJECT(window), "destroy",
     G_CALLBACK(gtk_main_quit), NULL);

  g_signal_connect(G_OBJECT(about), "activate", 
        G_CALLBACK(show_about), (gpointer) window); 
  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
