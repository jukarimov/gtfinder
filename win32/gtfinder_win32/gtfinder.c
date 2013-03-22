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

#include "gtfinder.h"

char *query = NULL;
char result[10000][1000];
int iresult = 0;

void reset_result() {
    iresult = 0;
}
void push_result(char *line) {
    if (iresult >= 9999) {
       puts("Too many results...");
       return;
    }
    strcpy(result[iresult++], line);
}

void delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    gtk_main_quit();
    exit(0);
}

static void enter_callback_getquery(GtkWidget *widget,
                                    GtkWidget *entry)
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
  query = (char *)entry_text;
}

static void do_search(GtkWidget *widget,
                      GtkWidget *label)
{
    printf("search: %s\n", query);
    reset_result();
    FILE *fp = fopen("list.txt", "r");
    char line[1000];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, query)) {
            push_result(line);
            printf("search: match: %s\n", line);
        }
    }
    fclose(fp);
    char results[1000 * 1000 * 10];
    sprintf(results, "%d results\n", iresult);
    int i = 0;
    for (;i < iresult; i++) {
        strcat(results, result[i]);
    }

    gtk_label_set_text(GTK_LABEL(label), "");
    gtk_label_set_text(GTK_LABEL(label), results);
}

int main( int   argc,
          char *argv[] )
{
    GtkWidget *window;
    GtkWidget *entry;
    GtkWidget *button;
    GtkWidget *scroll;
    GtkWidget *table;
    GtkWidget *label;
    GtkWidget *label_results;

    gtk_init (&argc, &argv);

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
    table = gtk_table_new (7, 7, TRUE);

    /* Put the table in the main window */
    gtk_container_add(GTK_CONTAINER (window), table);

    label = gtk_label_new ("search:");
    //gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
    gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 0, 1);
    gtk_widget_show (label);

    /* Create first entry */
    entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry), 80);
    g_signal_connect(entry, "changed",
              G_CALLBACK (enter_callback_getquery),
              (gpointer) entry);

    /* Insert entry 1 into the upper left quadrant of the table */
    gtk_table_attach_defaults(GTK_TABLE (table), entry, 0, 5, 1, 2);
    gtk_widget_show(entry);

    /* Create "OK" button */
    button = gtk_button_new_with_label("OK");

    gtk_table_attach_defaults(GTK_TABLE(table), button, 5, 7, 1, 2);
    gtk_widget_show(button);

    scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_usize(scroll, 300, 350);
    gtk_table_attach_defaults(GTK_TABLE(table), scroll, 0, 5, 2, 5);
    gtk_widget_show(scroll);


    label_results = gtk_label_new("results");
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroll), label_results);

    gtk_label_set_selectable(GTK_LABEL(label_results), TRUE);
    gtk_table_attach_defaults(GTK_TABLE(table), label_results, 0, 5, 2, 5);
    gtk_widget_show(label_results);

    g_signal_connect(button, "clicked",
                     G_CALLBACK(do_search),
                     (gpointer) label_results);

    button = gtk_button_new_with_label ("index");
    g_signal_connect_swapped (button, "clicked",
                              G_CALLBACK (file_chooser),
                              NULL);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 5, 7, 3, 4);
    gtk_widget_show (button);

    /* Create "close" button */
    button = gtk_button_new_with_label ("close");

    /* When the button is clicked, we call the "calculate" function*/
    g_signal_connect_swapped (button, "clicked",
                              G_CALLBACK (delete_event),
                              window);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 5, 7, 4, 5);
    gtk_widget_show (button);

    button = gtk_button_new_with_label ("About");

    g_signal_connect (button, "clicked",
                      G_CALLBACK (box), NULL);

    /* Insert the quit button into the both
     * lower quadrants of the table */
    gtk_table_attach_defaults (GTK_TABLE (table), button, 5, 7, 6, 7);

    gtk_widget_show (button);
    gtk_widget_show (table);
    gtk_widget_show (window);

    gtk_main ();

    return 0;
}
