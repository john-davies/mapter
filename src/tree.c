// tree.c - functions to manipulate the notes tree
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

#include <gtk/gtk.h>
#include "main.h"

// --------------------------------------------------------------------------
// name
//
// Description
//
// --------------------------------------------------------------------------

void on_btn_add_heading_clicked( GtkWidget *widget, app_widgets *app_wdgts )
{
  g_info( "tree.c / on_btn_add_heading_clicked");
  GtkTreeIter iter;
  GtkTreeIter parent;
  GtkTreeIter new;
  GtkTreeModel *model;

  if( gtk_tree_selection_get_selected( GTK_TREE_SELECTION( app_wdgts->w_notes_treestore_selection ), &model, &iter ) != FALSE )
  {
    // Get parent
    if( gtk_tree_model_iter_parent( GTK_TREE_MODEL( app_wdgts->w_notes_treestore ), &parent, &iter ) == FALSE )
    {
      // Top Level
      gtk_tree_store_append( app_wdgts->w_notes_treestore, &new, NULL );
    }
    else
    {
      // Add as a new child of parent
      gtk_tree_store_append( app_wdgts->w_notes_treestore, &new, &parent );
    }
  }
  else
  {
    // Can't find currently selected row so tree is likely empty
    // Add new heading at the top level
    gtk_tree_store_append( app_wdgts->w_notes_treestore, &new, NULL );
  }
  // Insert data
  gtk_tree_store_set( app_wdgts->w_notes_treestore, &new, 0, "New heading", 1, "New text", -1);
  g_info( "tree.c / ~on_btn_add_heading_clicked");
}

// --------------------------------------------------------------------------
// name
//
// Description
//
// --------------------------------------------------------------------------

void on_btn_add_child_clicked( GtkWidget *widget, app_widgets *app_wdgts )
{
  GtkTreeIter iter;
  GtkTreeIter new;
  GtkTreeModel *model;

  g_info( "tree.c / on_btn_add_child_clicked");
  if( gtk_tree_selection_get_selected( GTK_TREE_SELECTION( app_wdgts->w_notes_treestore_selection ), &model, &iter ) != FALSE )
  {
    // Add as a new child of current level
    gtk_tree_store_append( app_wdgts->w_notes_treestore, &new, &iter );
    // Insert data
    gtk_tree_store_set( app_wdgts->w_notes_treestore, &new, 0, "New heading", 1, "New text", -1);
  }
  else
  {
    g_info( "ERROR: can't find selected row" );
  }
  g_info( "tree.c / ~on_btn_add_child_clicked");
}

// --------------------------------------------------------------------------
// name
//
// Description
//
// --------------------------------------------------------------------------

void on_btn_delete_heading_clicked( GtkWidget *widget, app_widgets *app_wdgts )
{
  GtkTreeIter iter;
  GtkTreeModel *model;

  g_info( "tree.c / on_btn_delete_heading_clicked");
  // Show warning message
  if( gtk_dialog_run( GTK_DIALOG( app_wdgts->w_dlg_delete ) ) == GTK_RESPONSE_OK )
  {
    // Delete node
    if( gtk_tree_selection_get_selected( GTK_TREE_SELECTION( app_wdgts->w_notes_treestore_selection ), &model, &iter ) != FALSE )
    {
      // Invalidate the current iterator
      app_wdgts->current_node_status = FALSE;
      // Remove node
      gtk_tree_store_remove( app_wdgts->w_notes_treestore, &iter );
    }
    else
    {
      g_print( "ERROR: can't find selected row" );
    }
  }
  gtk_widget_hide( app_wdgts->w_dlg_delete );
  g_info( "tree.c / ~on_btn_delete_heading_clicked");

}

// --------------------------------------------------------------------------
// name
//
// Description
//
// --------------------------------------------------------------------------

void on_notes_tree_section_r_edited( GtkCellRendererText *cell, gchar *path_string, gchar *new_text, app_widgets *app_wdgts )
{
  GtkTreeIter iter;

  g_info( "tree.c / on_notes_tree_section_r_edited");
  gtk_tree_model_get_iter_from_string( GTK_TREE_MODEL( app_wdgts->w_notes_treestore ), &iter, (const gchar *)path_string );
  gtk_tree_store_set( app_wdgts->w_notes_treestore, &iter, 0, new_text, -1 );
  g_info( "  Heading updated: %s", new_text );
  g_info( "tree.c / ~on_notes_tree_section_r_edited");

}

// --------------------------------------------------------------------------
// name
//
// Description
//
// --------------------------------------------------------------------------

void on_notes_treestore_selection_changed( GtkWidget *widget, app_widgets *app_wdgts )
{
  gchar *value;
  GtkTreeModel *model;
  GtkTextIter start;
  GtkTextIter end;

  g_info( "tree.c / on_notes_treestore_selection_changed");
  // Save the text from the previously selected node if it wasn't deleted
  if( app_wdgts->current_node_status == TRUE )
  {
    // Get the text buffer
    gtk_text_buffer_get_start_iter( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_notes_textview ) ), &start );
    gtk_text_buffer_get_end_iter( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_notes_textview ) ), &end );
      // Copy text to tree
    gtk_tree_store_set( app_wdgts->w_notes_treestore, &app_wdgts->current_node,
                  1, gtk_text_buffer_get_text( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_notes_textview ) ),
                              &start,
                              &end,
                              FALSE ),
                  -1 );
  }
  // Now show text of newly selected element
  if( gtk_tree_selection_get_selected( GTK_TREE_SELECTION( app_wdgts->w_notes_treestore_selection ), &model, &app_wdgts->current_node ) != FALSE )
  {
    // Copy text to text window
    gtk_tree_model_get( model, &app_wdgts->current_node, 1, &value, -1 );
    gtk_text_buffer_set_text( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_notes_textview ) ), value, -1 );
    // Validate the current iterator
    app_wdgts->current_node_status = TRUE;
    g_free( value );
  }
  else
  {
    // No nodes left so clear the text view
    gtk_text_buffer_set_text( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_notes_textview ) ), "", -1 );
  }

  g_info( "tree.c / ~on_notes_treestore_selection_changed");
}

// --------------------------------------------------------------------------
// name
//
// Description
//
// --------------------------------------------------------------------------

void import_single_header( gchar *text, app_widgets *app_wdgts )
{
  // Set up treestore
  gtk_tree_store_append( app_wdgts->w_notes_treestore, &app_wdgts->current_node, NULL);
  gtk_tree_store_set( app_wdgts->w_notes_treestore, &app_wdgts->current_node, 0, "Imported Text", 1, text, -1);
  app_wdgts->current_node_status = TRUE;
  // Update text view
  gtk_text_buffer_set_text( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_notes_textview ) ),
                        text,
                        -1 );
  // Set current iter

}
