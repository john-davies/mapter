// main.c - main entry point
//          part of the mapter program
// Copyright (C) 2020 John Davies
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h>
#include "main.h"
#include "file.h"
#include "grid.h"
#include "util.h"
#include "css.h"

// --------------------------------------------------------------------------
// on_window_main_destroy
//
// Called on "Quit" command from menu
//
// --------------------------------------------------------------------------

void on_window_main_destroy()
{
    gtk_main_quit();
}

// --------------------------------------------------------------------------
// main
//
// Main entry point, initial setup and launch of main window
//
// --------------------------------------------------------------------------

int main( int argc, char *argv[] )
{
    GtkBuilder      *builder;
    GtkWidget       *window;
    // Instantiate structure, allocating memory for it
    app_widgets     *widgets = g_slice_new(app_widgets);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("glade/window_main.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    // Pointers to widgets here
    widgets->w_window_main = window;
    widgets->w_grid_container  = GTK_WIDGET(gtk_builder_get_object(builder, "grid_container"));
    widgets->w_grid_viewport  = GTK_WIDGET(gtk_builder_get_object(builder, "grid_viewport"));
    widgets->w_dlg_open = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_open"));
    widgets->w_dlg_save_as = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_save_as"));
    widgets->w_dlg_get_row_col = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_get_row_col"));
    widgets->w_dlg_about = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_about"));
    widgets->w_spin_rows = GTK_WIDGET(gtk_builder_get_object(builder, "spin_rows"));
    widgets->w_spin_columns = GTK_WIDGET(gtk_builder_get_object(builder, "spin_columns"));
    widgets->w_grid_right_click_menu = GTK_WIDGET(gtk_builder_get_object(builder, "grid_right_click_menu"));
    widgets->w_editor_window = GTK_WIDGET(gtk_builder_get_object(builder, "editor_window"));
    widgets->w_edit_summary = GTK_WIDGET(gtk_builder_get_object(builder, "edit_summary"));
    widgets->w_edit_heading = GTK_WIDGET(gtk_builder_get_object(builder, "edit_heading"));
    widgets->w_edit_body = GTK_WIDGET(gtk_builder_get_object(builder, "edit_body"));
    widgets->w_notes_textview = GTK_WIDGET(gtk_builder_get_object(builder, "notes_textview"));
    widgets->w_dlg_export_options = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_export_options"));
    widgets->b_chkbtn_export_title = GTK_WIDGET(gtk_builder_get_object(builder, "chkbtn_export_title"));
    widgets->b_rdbtn_row = GTK_WIDGET(gtk_builder_get_object(builder, "rdbtn_row"));
    widgets->w_dlg_export = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_export"));
    widgets->b_chkbtn_export_series = GTK_WIDGET(gtk_builder_get_object(builder, "chkbtn_export_series"));
    widgets->l_row_id_label  = GTK_WIDGET(gtk_builder_get_object(builder, "row_id_label"));
    widgets->l_column_id_label  = GTK_WIDGET(gtk_builder_get_object(builder, "column_id_label"));

     // Widgets pointer are passed to all widget handler functions as the user_data parameter
    gtk_builder_connect_signals( builder, widgets );

    g_object_unref( builder );

    g_info( "main.c / main" );

    // Update file names & titles etc
    strncpy( widgets->app_name, gtk_window_get_title( GTK_WINDOW( window ) ), APP_NAME_SIZE-1 );
    widgets->app_name[APP_NAME_SIZE] = '\0';
    widgets->current_file_path[0] = '\0';
    widgets->current_file_name[0] = '\0';

    // Set up default grid if no input file was specified
    if( argc == 1 )
    {
      g_info( "  No input file specified" );
      fill_grid( DEFAULT_ROWS, DEFAULT_COLUMNS, widgets );
    }
    else
    {
      // Open the specified file
      g_info( "  Input file: %s", argv[1] );
      open_file( argv[1], widgets );
    }

    gtk_widget_show_all(window);

    // Set up CSS
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    GError *error = NULL;

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen( display );
    gtk_style_context_add_provider_for_screen( screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION );
    gtk_css_provider_load_from_data( provider, mapter_CSS, -1, &error );
    if( error != NULL )
    {
      g_info( "  Error loading CSS: %s", error->message );
    }
    g_object_unref( provider );

    gtk_main();
    // Free up widget structure memory
    g_slice_free( app_widgets, widgets );

    return EXIT_SUCCESS;
}
