/*
    This file is a part of GTQalc
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

#include "gtqalc.h"

void delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    gtk_main_quit ();
    exit(0);
}

static void enter_callback_set_a(GtkWidget *widget,
                            GtkWidget *entry )
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
  //printf("set a: %s\n", entry_text);
  a = atof((char *)entry_text);
  //printf("a now: %f\n", a);
}

static void enter_callback_set_b(GtkWidget *widget,
                            GtkWidget *entry )
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
  //printf("set b: %s\n", entry_text);
  b = atof((char *)entry_text);
  //printf("b now: %f\n", b);
}

static void enter_callback_set_c(GtkWidget *widget,
                            GtkWidget *entry )
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
  //printf("set c: %s\n", entry_text);
  c = atof((char *)entry_text);
  //printf("c now: %f\n", c);
}

static gboolean calculate( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    d = b * b - 4 * a * c;
    x1 = (-b + sqrt(d)) / (2 * a);
    x2 = (-b - sqrt(d)) / (2 * a);

    buf = g_strdup_printf ("D = %f", d);
    gtk_entry_set_text (GTK_ENTRY (entry_d), buf);
    g_free(buf);

    buf = g_strdup_printf ("X1 = %f", x1);
    gtk_entry_set_text (GTK_ENTRY (entry_x1), buf);
    g_free(buf);

    buf = g_strdup_printf ("X2 = %f", x2);
    gtk_entry_set_text (GTK_ENTRY (entry_x2), buf);
    g_free(buf);

    return FALSE;
}

int main( int   argc,
          char *argv[] )
{
    GtkWidget *window;
    GtkWidget *entry;
    GtkWidget *button;
    GtkWidget *table;
    GtkWidget *label;

    gtk_init (&argc, &argv);

    a = b = c = 0;

    /* Create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_widget_set_size_request(GTK_WIDGET (window), 350, 300);

    /* Set the window title */
    gtk_window_set_title (GTK_WINDOW (window), "GTQalc");

    /* Set a handler for delete_event that immediately
     * exits GTK. */
    g_signal_connect (window, "delete-event",
                      G_CALLBACK (delete_event), NULL);

    /* Sets the border width of the window. */
    gtk_container_set_border_width (GTK_CONTAINER (window), 20);

    /* Create a 6x6 table */
    table = gtk_table_new (6, 6, TRUE);

    /* Put the table in the main window */
    gtk_container_add(GTK_CONTAINER (window), table);

    label = gtk_label_new ("a");
    //gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 0, 1);
    gtk_widget_show (label);

    label = gtk_label_new ("b");
    //gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 1, 2, 0, 1);
    gtk_widget_show (label);

    label = gtk_label_new ("c");
    //gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 2, 3, 0, 1);
    gtk_widget_show (label);

    /* Create first entry */
    entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry), 10);
    g_signal_connect(entry, "changed",
		      G_CALLBACK (enter_callback_set_a),
		      (gpointer) entry);

    /* Insert entry 1 into the upper left quadrant of the table */
    gtk_table_attach_defaults (GTK_TABLE (table), entry, 0, 1, 1, 2);
    gtk_widget_show (entry);

    /* Create second entry */
    entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry), 10);
    g_signal_connect(entry, "changed",
		      G_CALLBACK (enter_callback_set_b),
		      (gpointer) entry);


    /* Insert entry 2 into the upper right quadrant of the table */
    gtk_table_attach_defaults (GTK_TABLE (table), entry, 1, 2, 1, 2);

    gtk_widget_show (entry);

    /* Create third entry */
    entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry), 10);
    g_signal_connect(entry, "changed",
		      G_CALLBACK (enter_callback_set_c),
		      (gpointer) entry);


    /* Insert entry 3 into the upper right quadrant of the table */
    gtk_table_attach_defaults (GTK_TABLE (table), entry, 2, 3, 1, 2);

    gtk_widget_show (entry);

    /* Create fourth entry */
    entry_d = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry_d), 20);

    /* Insert entry 4 into the table */
    gtk_table_attach_defaults (GTK_TABLE (table), entry_d, 0, 3, 2, 3);

    gtk_widget_show (entry_d);

    /* Create fifth entry */
    entry_x1 = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry_x1), 20);

    /* Insert entry 5 into the table */
    gtk_table_attach_defaults (GTK_TABLE (table), entry_x1, 0, 3, 3, 4);

    gtk_widget_show (entry_x1);

    /* Create sixth entry */
    entry_x2 = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry_x2), 20);

    /* Insert entry 6 into the table */
    gtk_table_attach_defaults (GTK_TABLE (table), entry_x2, 0, 3, 4, 5);

    gtk_widget_show (entry_x2);

    /* Create "OK" button */
    button = gtk_button_new_with_label ("OK");

    /* When the button is clicked, we call the "calculate" function*/
    g_signal_connect (button, "clicked",
                      G_CALLBACK (calculate), NULL);

    /* Insert the quit button into the both
     * lower quadrants of the table */
    gtk_table_attach_defaults (GTK_TABLE (table), button, 4, 5, 1, 2);
    gtk_widget_show (button);

    /* Create "close" button */
    button = gtk_button_new_with_label ("close");

    /* When the button is clicked, we call the "calculate" function*/
    g_signal_connect_swapped (button, "clicked",
			      G_CALLBACK (delete_event),
			      window);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 4, 5, 4, 5);
    gtk_widget_show (button);

    button = gtk_button_new_with_label ("About");

    g_signal_connect (button, "clicked",
                      G_CALLBACK (box), NULL);

    /* Insert the quit button into the both
     * lower quadrants of the table */
    gtk_table_attach_defaults (GTK_TABLE (table), button, 5, 6, 4, 5);

    gtk_widget_show (button);
    gtk_widget_show (table);
    gtk_widget_show (window);

    gtk_main ();

    return 0;
}
