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
#include <gtksourceview/gtksourceview.h>
#include <gtkspell/gtkspell.h>
#include <time.h>
#include "main.h"
#include "file.h"
#include "grid.h"
#include "util.h"
#include "css.h"
#include "config.h"
#include "gui.h"

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

    g_type_ensure( GTK_SOURCE_TYPE_VIEW );
    //builder = gtk_builder_new_from_file("glade/window_main.glade");
    builder = gtk_builder_new_from_string( glade_definition, -1 );

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
    widgets->w_edit_search_entry = GTK_WIDGET(gtk_builder_get_object(builder, "edit_search_entry"));
    widgets->check_btn_edit_case = GTK_WIDGET(gtk_builder_get_object(builder, "check_btn_edit_case"));
    widgets->m_save = GTK_WIDGET( gtk_builder_get_object(builder, "save") );
    widgets->w_notes_textview = GTK_WIDGET(gtk_builder_get_object(builder, "notes_textview"));
    widgets->w_notes_treeview = GTK_TREE_VIEW( gtk_builder_get_object( builder, "notes_treeview" ));
    widgets->w_notes_treestore = GTK_TREE_STORE( gtk_builder_get_object( builder, "notes_treestore" ));
    widgets->w_notes_treestore_selection = GTK_TREE_SELECTION( gtk_builder_get_object( builder, "notes_treestore_selection" ));
    widgets->w_notes_tree_section = GTK_TREE_VIEW_COLUMN( gtk_builder_get_object( builder, "notes_tree_section" ));
    widgets->w_notes_tree_section_r = GTK_CELL_RENDERER( gtk_builder_get_object( builder, "notes_tree_section_r" ));
    widgets->w_notes_tree_text = GTK_TREE_VIEW_COLUMN( gtk_builder_get_object( builder, "notes_tree_text" ));
    widgets->w_notes_tree_text_r = GTK_CELL_RENDERER( gtk_builder_get_object( builder, "notes_tree_text_r" ));
    widgets->w_dlg_delete = GTK_WIDGET(gtk_builder_get_object( builder, "dlg_delete_warning" ) );
    widgets->current_node_status = FALSE;
    widgets->stop_node_processing = FALSE;
    widgets->w_dlg_export_options = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_export_options"));
    widgets->b_chkbtn_export_title = GTK_WIDGET(gtk_builder_get_object(builder, "chkbtn_export_title"));
    widgets->b_chkbtn_export_dup_cr = GTK_WIDGET(gtk_builder_get_object(builder, "chkbtn_export_dup_cr"));
    widgets->w_dlg_export = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_export"));
    widgets->b_chkbtn_export_series = GTK_WIDGET(gtk_builder_get_object(builder, "chkbtn_export_series"));
    widgets->l_row_id_label  = GTK_WIDGET(gtk_builder_get_object(builder, "row_id_label"));
    widgets->l_column_id_label  = GTK_WIDGET(gtk_builder_get_object(builder, "column_id_label"));

     // Widgets pointer are passed to all widget handler functions as the user_data parameter
    gtk_builder_connect_signals( builder, widgets );

    g_object_unref( builder );

    g_info( "main.c / main" );

    // Attach the renderers to the tree store columns
    gtk_tree_view_column_add_attribute( widgets->w_notes_tree_section, widgets->w_notes_tree_section_r, "text", 0);
    gtk_tree_view_column_add_attribute( widgets->w_notes_tree_text, widgets->w_notes_tree_text_r, "text", 1);

    // Attach a spell checker to the various text views
    GtkSpellChecker* notes_spell = gtk_spell_checker_new();
    if( gtk_spell_checker_set_language( notes_spell, NULL, NULL ) == FALSE )
    {
        g_info( "ERROR - Failed to set language for \"notes\" spell checker\n");
    }
    else
    {
      if( gtk_spell_checker_attach( notes_spell, GTK_TEXT_VIEW( widgets->w_notes_textview ) ) == FALSE )
      {
        g_info( "ERROR - Failed to attach \"notes\" spell checker\n");
      }
    }

    GtkSpellChecker* summary_spell = gtk_spell_checker_new();
    if( gtk_spell_checker_set_language( summary_spell, NULL, NULL ) == FALSE )
    {
        g_info( "ERROR - Failed to set language for \"summary\" spell checker\n");
    }
    else
    {
      if( gtk_spell_checker_attach( summary_spell, GTK_TEXT_VIEW( widgets->w_edit_summary ) ) == FALSE )
      {
        g_info( "ERROR - Failed to attach \"summary\" spell checker\n");
      }
    }

    GtkSpellChecker* heading_spell = gtk_spell_checker_new();
    if( gtk_spell_checker_set_language( heading_spell, NULL, NULL ) == FALSE )
    {
        g_info( "ERROR - Failed to set language for \"heading\" spell checker\n");
    }
    else
    {
      if( gtk_spell_checker_attach( heading_spell, GTK_TEXT_VIEW( widgets->w_edit_heading ) ) == FALSE )
      {
        g_info( "ERROR - Failed to attach \"heading\" spell checker\n");
      }
    }

    GtkSpellChecker* body_spell = gtk_spell_checker_new();
    if( gtk_spell_checker_set_language( body_spell, NULL, NULL ) == FALSE )
    {
        g_info( "ERROR - Failed to set language for \"body\" spell checker\n");
    }
    else
    {
      if( gtk_spell_checker_attach( body_spell, GTK_TEXT_VIEW( widgets->w_edit_body ) ) == FALSE )
      {
        g_info( "ERROR - Failed to attach \"body\" spell checker\n");
      }
    }

    // Add an accelerator group to the main window
    widgets->right_click_accel_group = gtk_accel_group_new();
    gtk_window_add_accel_group( GTK_WINDOW (window), widgets->right_click_accel_group );

    // Update file names & titles etc
    strncpy( widgets->app_name, gtk_window_get_title( GTK_WINDOW( window ) ), APP_NAME_SIZE-1 );
    widgets->app_name[APP_NAME_SIZE] = '\0';
    widgets->current_file_path[0] = '\0';
    widgets->current_file_name[0] = '\0';

    // Load cached file ( if any )
    load_config( widgets );

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
