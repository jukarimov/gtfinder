/*
    This file is a part of GTFinder
    Copyright (C) 2012 Jalil Karimov <jukarimov@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <gtk/gtk.h>
#include "gtfinder.h"

GtkWidget *window;

void shutdown_file_chooser()
{
    gtk_widget_destroy(window);
    gtk_main_quit();
    return;
}

void file_chooser( int   argc,
          char *argv[] )
{
    GtkWidget *button;
    GtkWidget *table;
    GtkWidget *label;
    GtkWidget *chooser;

    gtk_init (&argc, &argv);

    /* Create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_widget_set_size_request(GTK_WIDGET (window), 450, 300);

    /* Set the window title */
    gtk_window_set_title (GTK_WINDOW (window), "Index directory");

    /* Set a handler for delete_event that immediately
     * exits GTK. */
    g_signal_connect (window, "delete-event",
                      G_CALLBACK (shutdown_file_chooser), NULL);

    /* Sets the border width of the window. */
    gtk_container_set_border_width (GTK_CONTAINER (window), 20);

    /* Create a 2x2 table */
    table = gtk_table_new (6, 6, TRUE);

    /* Put the table in the main window */
    gtk_container_add(GTK_CONTAINER (window), table);

    /* create a new label. */
    label = gtk_label_new ("Select folder to index files in");

    chooser = gtk_file_chooser_dialog_new(
        "Pick directory",
        GTK_WINDOW(window),
        GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
        GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
        GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
        NULL);

    int file_count = 0;
    char *dirname = NULL;
    if (gtk_dialog_run(GTK_DIALOG(chooser)) == GTK_RESPONSE_ACCEPT)
    {
        dirname = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chooser));
        printf("file_chooser: selected: '%s'\n", dirname);
	file_count = list_files(dirname);
    }

    gtk_widget_destroy(chooser);

    char labbuf[100];
    sprintf(labbuf, "%s: %d files found", dirname, file_count);
    label = gtk_label_new (labbuf);

    //gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults(GTK_TABLE (table), label, 0, 5, 0, 1);

    /* Create "Quit" button */
    button = gtk_button_new_with_label ("close");

    /* When the button is clicked, we call the "calculate" function*/
    g_signal_connect_swapped (button, "clicked",
                  G_CALLBACK (shutdown_file_chooser),
                  window);

    /* Insert the quit button into the both
     * lower quadrants of the table */
    gtk_table_attach_defaults (GTK_TABLE (table), button, 5, 7, 6, 8);

    gtk_widget_show (label);
    gtk_widget_show (button);
    gtk_widget_show (table);
    gtk_widget_show (window);

    gtk_main ();
}

