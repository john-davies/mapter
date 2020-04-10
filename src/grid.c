// grid.c - functions to manipulate the text grid
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
#include "grid.h"
#include "util.h"
#include "css.h"

// --------------------------------------------------------------------------
// add_row
//
// Adds a row into the grid at the specified position
//
// --------------------------------------------------------------------------

void add_row( app_widgets *app_wdgts, gint row )
{
  g_info( "grid.c / add_row");
  g_info( "  Position: %d", row );
  gtk_grid_insert_row( GTK_GRID( app_wdgts->w_text_grid ), row );
  // Insert the text boxes
  for( gint c=0; c<app_wdgts->current_grid_columns; c++ )
  {
    // Widgets for hierarchy of each cell
    GtkWidget *e_box = gtk_event_box_new();
    GtkWidget *w_frame = gtk_frame_new( NULL );
    GtkWidget *w_text = gtk_label_new( NULL );

    gtk_label_set_line_wrap( GTK_LABEL( w_text ), TRUE );
    gtk_label_set_width_chars( GTK_LABEL( w_text ), LABEL_WIDTH );
    gtk_container_add ( GTK_CONTAINER( w_frame ), w_text );
    gtk_container_add ( GTK_CONTAINER( e_box ), w_frame );
    g_signal_connect( e_box, "button-press-event", G_CALLBACK( text_grid_click ), app_wdgts );

    gtk_grid_attach( GTK_GRID( app_wdgts->w_text_grid ), e_box, c, row, 1, 1 );
  }
  app_wdgts->current_grid_rows++;
  g_info( "  New row count: %d", app_wdgts->current_grid_rows );
  gtk_widget_show_all( app_wdgts->w_text_grid );
  g_info( "grid.c / ~add_row");
}

// --------------------------------------------------------------------------
// add_row_above
//
// Adds a row into the grid at the row above the element that has been
// selected
//
// --------------------------------------------------------------------------

void add_row_above( GtkWidget *source, app_widgets *app_wdgts )
{
  g_info( "grid.c / add_row_above");
  add_row( app_wdgts, app_wdgts->edit_grid_row );
  g_info( "  Add row at: %d", app_wdgts->edit_grid_row );
  g_info( "grid.c / ~add_row_above");
}

// --------------------------------------------------------------------------
// add_row_below
//
// Adds a row into the grid at the row below the element that has been
// selected
//
// --------------------------------------------------------------------------

void add_row_below( GtkWidget *source, app_widgets *app_wdgts )
{
  g_info( "grid.c / add_row_below");
  add_row( app_wdgts, app_wdgts->edit_grid_row+1 );
  g_info( "  Add row at: %d", app_wdgts->edit_grid_row+1 );
  g_info( "grid.c / ~add_row_below");
}

// --------------------------------------------------------------------------
// delete_row
//
// Deletes the row of the element that has been selected
//
// --------------------------------------------------------------------------

void delete_row( GtkWidget *source, app_widgets *app_wdgts )
{
  g_info( "grid.c / delete_row");
  if( app_wdgts->current_grid_rows > 1 )
  {
    gtk_grid_remove_row( GTK_GRID( app_wdgts->w_text_grid ), app_wdgts->edit_grid_row );
    g_info( "  Delete row: %d", app_wdgts->edit_grid_row );
    app_wdgts->current_grid_rows--;
    g_info( "  New row count: %d", app_wdgts->current_grid_rows );
  }
  else
  {
    // Should never get here as it should have been stopped elsewhere
    // so just log an error
    g_info( "  ERROR: Can't delete last row" );
  }
  g_info( "grid.c / ~delete_row");
}

// --------------------------------------------------------------------------
// add_column
//
// Adds a column into the grid at the specified position
//
// --------------------------------------------------------------------------

void add_column( app_widgets *app_wdgts, gint column )
{
  g_info( "grid.c / add_column");
  g_info( "  Position: %d", column );
  gtk_grid_insert_column( GTK_GRID( app_wdgts->w_text_grid ), column );
  // Insert the text boxes
  for( gint r=0; r<app_wdgts->current_grid_rows; r++ )
  {
    // Widgets for hierarchy of each cell
    GtkWidget *e_box = gtk_event_box_new();
    GtkWidget *w_frame = gtk_frame_new( NULL );
    GtkWidget *w_text = gtk_label_new( NULL );

    gtk_label_set_line_wrap( GTK_LABEL( w_text ), TRUE );
    gtk_label_set_width_chars( GTK_LABEL( w_text ), LABEL_WIDTH );
    gtk_container_add ( GTK_CONTAINER( w_frame ), w_text );
    gtk_container_add ( GTK_CONTAINER( e_box ), w_frame );
    g_signal_connect( e_box, "button-press-event", G_CALLBACK( text_grid_click ), app_wdgts );

    gtk_grid_attach( GTK_GRID( app_wdgts->w_text_grid ), e_box, column, r, 1, 1 );
  }
  app_wdgts->current_grid_columns++;
  g_info( "  New column count: %d", app_wdgts->current_grid_columns );
  gtk_widget_show_all( app_wdgts->w_text_grid );
  g_info( "grid.c / ~add_column");
}

// --------------------------------------------------------------------------
// add_column_left
//
// Adds a column into the grid at the column to the left of the element
// that has been selected
//
// --------------------------------------------------------------------------

void add_column_left( GtkWidget *source, app_widgets *app_wdgts )
{
  g_info( "grid.c / add_column_left");
  add_column( app_wdgts, app_wdgts->edit_grid_column );
  g_info( "  Add column at: %d", app_wdgts->edit_grid_column );
  g_info( "grid.c / ~add_column_left");
}

// --------------------------------------------------------------------------
// add_column_right
//
// Adds a column into the grid at the column to the right of the element
// that has been selected
//
// --------------------------------------------------------------------------

void add_column_right( GtkWidget *source, app_widgets *app_wdgts )
{
  g_info( "grid.c / add_column_left");
  add_column( app_wdgts, app_wdgts->edit_grid_column+1 );
  g_info( "  Add column at: %d", app_wdgts->edit_grid_column+1 );
  g_info( "grid.c / ~add_column_left");
}

// --------------------------------------------------------------------------
// delete_column
//
// Deletes the column of the element that has been selected
//
// --------------------------------------------------------------------------

void delete_column( GtkWidget *source, app_widgets *app_wdgts )
{
  g_info( "grid.c / delete_column");
  if( app_wdgts->current_grid_columns > 1 )
  {
    g_info( "  Delete column: %d", app_wdgts->edit_grid_column );
    gtk_grid_remove_column( GTK_GRID( app_wdgts->w_text_grid ), app_wdgts->edit_grid_column );
    app_wdgts->current_grid_columns--;
    g_info( "  New column count: %d", app_wdgts->current_grid_columns );
  }
  else
  {
    // Should never get here as it should have been stopped elsewhere
    // so just log an error
    g_info( "  ERROR: Can't delete last column" );
  }
  g_info( "grid.c / ~delete_column");
}

// --------------------------------------------------------------------------
// on_btn_edit_save_clicked
//
// Edited text is saved back to the grid and the window closed
//
// --------------------------------------------------------------------------

void on_btn_edit_save_clicked( GtkButton *button, app_widgets *app_wdgts )
{
  GtkTextIter start;
  GtkTextIter end;
  g_info( "grid.c / on_btn_edit_save_clicked");
  // Copy text from editor to text grid
  gtk_text_buffer_get_start_iter( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_edit_summary_view ) ), &start );
  gtk_text_buffer_get_end_iter( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_edit_summary_view ) ), &end );
  gtk_label_set_text( GTK_LABEL( app_wdgts->w_current_edit_text_element ),
                      gtk_text_buffer_get_text( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_edit_summary_view ) ),
                            &start,
                            &end,
                            FALSE ) );
  g_info( "grid.c / ~on_btn_edit_save_clicked");
}

// --------------------------------------------------------------------------
// on_btn_edit_closed_clicked
//
// Editing window is closed and any edits discarded
//
// --------------------------------------------------------------------------

void on_btn_edit_close_clicked( GtkButton *button, app_widgets *app_wdgts )
{
  g_info( "grid.c / on_btn_edit_close_clicked");
  gtk_widget_hide(app_wdgts->w_editor_window );
  g_info( "grid.c / ~on_btn_edit_close_clicked");
}

// --------------------------------------------------------------------------
// edit_cell
//
// Launches the editor on the selected cell
//
// --------------------------------------------------------------------------
void edit_cell( gint row, gint column, app_widgets *app_wdgts )
{
  g_info( "grid.c / edit_cell");
  g_info( "  Row: %d, Column: %d", row, column );
  GtkWidget *child = gtk_grid_get_child_at( GTK_GRID( app_wdgts->w_text_grid ),
                              column, row ); // GtkEventBox
  child = gtk_bin_get_child( GTK_BIN( child ) ); // GtkFrame
  app_wdgts->w_current_edit_text_element = gtk_bin_get_child( GTK_BIN( child ) ); // GtkTextView
  // Copy current text to edit window
  gtk_text_buffer_set_text( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_edit_summary_view ) ),
                        gtk_label_get_text( GTK_LABEL( app_wdgts->w_current_edit_text_element ) ),
                        -1 );
  // Show the Edit window
  gtk_widget_show( app_wdgts->w_editor_window );
  // Put the keyboard focus in the text window
  gtk_window_present( GTK_WINDOW( app_wdgts->w_editor_window ) );
  gtk_widget_grab_focus( app_wdgts->w_edit_summary_view );
  g_info( "grid.c / ~edit_cell");
}

// --------------------------------------------------------------------------
// get_cell_text
//
// Gets the text from the cell at row, column
// Can be limited to length or -1 for all text
// --------------------------------------------------------------------------

const gchar *get_cell_text( gint row, gint column, app_widgets *app_wdgts )
{
  g_info( "grid.c / get_cell_text");
  g_info( "  Row: %d, Column: %d", row, column );
  GtkWidget *child = gtk_grid_get_child_at( GTK_GRID( app_wdgts->w_text_grid ),
                              column, row ); // GtkEventBox
  child = gtk_bin_get_child( GTK_BIN( child ) ); // GtkFrame
  child = gtk_bin_get_child( GTK_BIN( child ) ); // GtkTextView
  g_info( "grid.c / ~get_cell_text");
  // Return pointer to label text
  return( gtk_label_get_text( GTK_LABEL( child ) ) );
}

// --------------------------------------------------------------------------
// text_grid_click
//
// Entry point for clicks on the text grid
//    Single click updates the highlight location
//    Double clicks are passed to the text editing functions
//    Right clicks are passed to the grid editing functions
//    Everything else is ignored
//
// --------------------------------------------------------------------------

void text_grid_click( GtkWidget *source, GdkEventButton *event, app_widgets *app_wdgts )
{
  gint row;
  gint column;

  g_info( "grid.c / text_grid_click");
  find_grid_coordinates( source, app_wdgts->w_text_grid, &row, &column );
  if( ( event->type == GDK_BUTTON_PRESS ) && ( event->button == 1 ) )
  {
    // Single click
    g_info( "  Single click: Row: %d, Column: %d", row, column );
    // Move the highlight if this is a different cell
    if( ( row != app_wdgts->edit_grid_row ) || ( column != app_wdgts->edit_grid_column ) )
    {
      highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                      row, column,
                      FALSE, app_wdgts );
      // Update the coordinates
      app_wdgts->edit_grid_row = row;
      app_wdgts->edit_grid_column = column;
    }
  }
  else if( ( event->type == GDK_DOUBLE_BUTTON_PRESS ) && ( event->button == 1 ) )
  {
    // Double click
    // Update editing coordinates
    app_wdgts->edit_grid_row = row;
    app_wdgts->edit_grid_column = column;
    g_info( "  Double click: Row: %d, Column: %d", row, column );
    edit_cell( row, column, app_wdgts );
  }
  else if( ( event->type == GDK_BUTTON_PRESS ) && ( event->button == 3 ) )
  {
    // Right click
    g_info( "  Right click: Row: %d, Column: %d", row, column );
    // Set up temporary editing coordinates
    app_wdgts->edit_grid_row = row;
    app_wdgts->edit_grid_column = column;
    // Show popup menu
    // For now this is built manually because of problems with the Glade version
    GtkWidget *option;
    GtkWidget *pmenu = gtk_menu_new();
    // Rows
    option = gtk_menu_item_new_with_label( "Add row above" );
    gtk_widget_show( option );
    g_signal_connect( G_OBJECT( option ), "activate", G_CALLBACK( add_row_above ), app_wdgts );
    gtk_menu_shell_append( GTK_MENU_SHELL( pmenu ), option );
    option = gtk_menu_item_new_with_label( "Add row below" );
    gtk_widget_show( option );
    g_signal_connect( G_OBJECT( option ), "activate", G_CALLBACK( add_row_below ), app_wdgts );
    gtk_menu_shell_append(GTK_MENU_SHELL( pmenu ), option );
    option = gtk_menu_item_new_with_label( "Delete row" );
    if( app_wdgts->current_grid_rows < 2 )
    {
      // Grey out if only one row left
      gtk_widget_set_sensitive( option, FALSE );
    }
    gtk_widget_show( option );
    g_signal_connect( G_OBJECT( option ), "activate", G_CALLBACK( delete_row ), app_wdgts );
    gtk_menu_shell_append( GTK_MENU_SHELL( pmenu ), option );
    // Separator
    option = gtk_separator_menu_item_new();
    gtk_widget_show( option );
    gtk_menu_shell_append( GTK_MENU_SHELL( pmenu ), option );
    // Columns
    option = gtk_menu_item_new_with_label( "Add column left" );
    gtk_widget_show( option );
    g_signal_connect( G_OBJECT( option ), "activate", G_CALLBACK( add_column_left ), app_wdgts );
    gtk_menu_shell_append( GTK_MENU_SHELL( pmenu ), option );
    option = gtk_menu_item_new_with_label( "Add column right" );
    gtk_widget_show( option );
    g_signal_connect( G_OBJECT( option ), "activate", G_CALLBACK( add_column_right ), app_wdgts );
    gtk_menu_shell_append(GTK_MENU_SHELL( pmenu ), option );
    option = gtk_menu_item_new_with_label( "Delete column" );
    if( app_wdgts->current_grid_columns < 2 )
    {
      // Grey out if only one row left
      gtk_widget_set_sensitive( option, FALSE );
    }
    gtk_widget_show( option );
    g_signal_connect( G_OBJECT( option ), "activate", G_CALLBACK( delete_column ), app_wdgts );
    gtk_menu_shell_append( GTK_MENU_SHELL( pmenu ), option );
    gtk_menu_popup( GTK_MENU( pmenu ), NULL, NULL, NULL, NULL,
        event->button, event->time );
  }
  g_info( "grid.c / ~text_grid_click");
}
// --------------------------------------------------------------------------
// highlight_cell
//
// Moves the highlight from the current cell to the new cell
// Move the scroll bars to match
//
// --------------------------------------------------------------------------

void highlight_cell( gint current_r, gint current_c, gint new_r, gint new_c, gboolean scroll, app_widgets *app_wdgts )
{
  GtkStyleContext *context;

  // Remove the current highlight - get the event box
  GtkWidget *child = gtk_grid_get_child_at( GTK_GRID( app_wdgts->w_text_grid ), current_c, current_r );
  // Now get the frame
  child = gtk_bin_get_child( GTK_BIN( child ) );
  context = gtk_widget_get_style_context( child );
  gtk_style_context_remove_class( context, "highlight" );

  // Add the new highlight, source is the event box
  // so find the child to find the frame
  child = gtk_grid_get_child_at( GTK_GRID( app_wdgts->w_text_grid ), new_c, new_r );
  // Set focus to the event box
  gtk_widget_grab_focus( child );
  child = gtk_bin_get_child( GTK_BIN( child ) );
  context = gtk_widget_get_style_context( child );
  gtk_style_context_add_class( context, "highlight" );
  // If required scroll to show the focus - move the scroll bars in the same proportion as
  // the current cell is to the grid
  if( scroll == TRUE )
  {
    // Horizontal
    GtkAdjustment *adjustment = gtk_scrolled_window_get_hadjustment( GTK_SCROLLED_WINDOW( app_wdgts->w_grid_container ) );
    gdouble lower = gtk_adjustment_get_lower( adjustment );
    gdouble upper = gtk_adjustment_get_upper( adjustment );
    gdouble page_size = gtk_adjustment_get_page_size( adjustment );
    gdouble range = upper - page_size - lower;
    gdouble value = ( ( (gdouble)new_c / ( (gdouble)app_wdgts->current_grid_columns - 1 ) ) * range ) + lower;
    gtk_adjustment_set_value( adjustment, value );
    // Vertical
    adjustment = gtk_scrolled_window_get_vadjustment( GTK_SCROLLED_WINDOW( app_wdgts->w_grid_container ) );
    lower = gtk_adjustment_get_lower( adjustment );
    upper = gtk_adjustment_get_upper( adjustment );
    page_size = gtk_adjustment_get_page_size( adjustment );
    range = upper - page_size - lower;
    value = ( ( (gdouble)new_r / ( (gdouble)app_wdgts->current_grid_rows - 1 ) ) * range ) + lower;
    gtk_adjustment_set_value( adjustment, value );
  }

  // Update the coordinate labels
  gtk_label_set_text( GTK_LABEL( app_wdgts->l_row_id_label ), get_cell_text( new_r, 0, app_wdgts ) );
  gtk_label_set_text( GTK_LABEL( app_wdgts->l_column_id_label ), get_cell_text( 0, new_c, app_wdgts ) );
}

// --------------------------------------------------------------------------
// text_grid_keypress
//
// Processes the keyboard presses on the text grid
//
// --------------------------------------------------------------------------

void text_grid_keypress( GtkWidget *source, GdkEventKey *event, app_widgets *app_wdgts )
{
  gint row;
  gint column;

  find_grid_coordinates( source, app_wdgts->w_text_grid, &row, &column );
  g_print( "text_grid_click, row: %d, column: %d, current_row: %d, current_column: %d\n",
            row, column, app_wdgts->edit_grid_row, app_wdgts->edit_grid_column );
  switch( event->keyval )
  {
    case GDK_KEY_Return:
      g_print( "Open editor on row: %d, column: %d\n", app_wdgts->edit_grid_row, app_wdgts->edit_grid_column );
      // Show the Edit window
      edit_cell( row, column, app_wdgts );
      break;

    case GDK_KEY_Left:
      if( app_wdgts->edit_grid_column > 0 )
      {
        if( ( event->state & GDK_SHIFT_MASK ) == 0 )
        {
          // No shift key so just move left
          g_print( "Left\n" );
          highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                          app_wdgts->edit_grid_row, app_wdgts->edit_grid_column-1,
                          TRUE, app_wdgts );
          app_wdgts->edit_grid_column--;
        }
        else
        {
          // Shift key so move to column 0
          g_print( "Shift Left\n" );
          highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                          app_wdgts->edit_grid_row, 0,
                          TRUE, app_wdgts );
          app_wdgts->edit_grid_column = 0;
        }
      }
      break;
    case GDK_KEY_Up:
      if( app_wdgts->edit_grid_row > 0 )
      {
        if( ( event->state & GDK_SHIFT_MASK ) == 0 )
        {
          // No shift key so just move up
          g_print( "Up\n" );
          highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                          app_wdgts->edit_grid_row-1, app_wdgts->edit_grid_column,
                          TRUE, app_wdgts );
          app_wdgts->edit_grid_row--;
        }
        else
        {
          // Shift key so move to row 0
          g_print( "Shift Up\n" );
          highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                          0, app_wdgts->edit_grid_column,
                          TRUE, app_wdgts );
          app_wdgts->edit_grid_row = 0;
        }
      }
      break;
    case GDK_KEY_Right:
      if( app_wdgts->edit_grid_column < app_wdgts->current_grid_columns-1 )
      {
        if( ( event->state & GDK_SHIFT_MASK ) == 0 )
        {
          // No shift key so just move right
          g_print( "Right\n" );
          highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                          app_wdgts->edit_grid_row, app_wdgts->edit_grid_column+1,
                          TRUE, app_wdgts );
          app_wdgts->edit_grid_column++;
        }
        else
        {
          // Shift key so move to last column
          g_print( "Shift Right\n" );
          highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                          app_wdgts->edit_grid_row, app_wdgts->current_grid_columns - 1,
                          TRUE, app_wdgts );
          app_wdgts->edit_grid_column = app_wdgts->current_grid_columns - 1;
        }
      }
      break;
    case GDK_KEY_Down:
      if( app_wdgts->edit_grid_row < app_wdgts->current_grid_rows-1 )
      {
        if( ( event->state & GDK_SHIFT_MASK ) == 0 )
        {
          // No shift key so just move down
          g_print( "Down\n" );
          highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                          app_wdgts->edit_grid_row+1, app_wdgts->edit_grid_column,
                          TRUE, app_wdgts );
          app_wdgts->edit_grid_row++;
        }
        else
        {
          // Shift key so move to bottom row
          g_print( "Shift Down\n" );
          highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                          app_wdgts->current_grid_rows-1, app_wdgts->edit_grid_column,
                          TRUE, app_wdgts );
          app_wdgts->edit_grid_row = app_wdgts->current_grid_rows - 1;
        }
      }
      break;
    case GDK_KEY_Home:
      g_print( "Home\n" );
      highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                      0, 0,
                      TRUE, app_wdgts );
      app_wdgts->edit_grid_row = 0;
      app_wdgts->edit_grid_column = 0;
      break;
    case GDK_KEY_End:
      g_print( "End\n" );
      highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                      app_wdgts->current_grid_rows - 1, app_wdgts->current_grid_columns - 1,
                      TRUE, app_wdgts );
      app_wdgts->edit_grid_row = app_wdgts->current_grid_rows - 1;
      app_wdgts->edit_grid_column = app_wdgts->current_grid_columns - 1;
      break;
    default:
      break;
  }
}

// --------------------------------------------------------------------------
// fill_grid
//
// Deletes the current text grid and create a new one of the specified
// dimensions
//
// --------------------------------------------------------------------------

void fill_grid( gint new_rows, gint new_columns, app_widgets *app_wdgts )
{
  g_info( "grid.c / fill_grid");
  // Clear anything in the viewport
  GList *children = gtk_container_get_children( GTK_CONTAINER( app_wdgts->w_grid_viewport ) );
  if( children != NULL )
  {
    gtk_widget_destroy( children->data );
  }
  // Get viewport
  if( app_wdgts->w_grid_viewport != NULL )
  {
    // Viewport found, check that it's empty
    GList *children = gtk_container_get_children( GTK_CONTAINER( app_wdgts->w_grid_viewport ) );
    if( children != NULL )
    {
      g_info( "  ERROR: viewport found but not empty ( %s )", gtk_widget_get_name( children->data ) );
    }
    else
    {
      g_info( "  Adding grid ( Rows: %d, Columns: %d )", new_rows, new_columns );
      // Create grid and attach to viewport
      app_wdgts->w_text_grid = gtk_grid_new();
      if( app_wdgts->w_text_grid != NULL )
      {
        gtk_container_add( GTK_CONTAINER( app_wdgts->w_grid_viewport ),
                           app_wdgts->w_text_grid );
        gtk_grid_set_row_homogeneous( GTK_GRID( app_wdgts->w_text_grid ), TRUE );
        gtk_grid_set_column_homogeneous( GTK_GRID( app_wdgts->w_text_grid ), TRUE );
        // Add text windows into grid
        for( gint r=0; r<new_rows; r++ )
        {
          for( gint c=0; c<new_columns; c++ )
          {
            // Widgets for hierarchy of each cell
            GtkWidget *e_box = gtk_event_box_new();
            GtkWidget *w_frame = gtk_frame_new( NULL );
            GtkWidget *w_text = gtk_label_new( NULL );

            gtk_label_set_line_wrap( GTK_LABEL( w_text ), TRUE );
            gtk_label_set_width_chars( GTK_LABEL( w_text ), LABEL_WIDTH );
            gtk_container_add ( GTK_CONTAINER( w_frame ), w_text );
            gtk_container_add ( GTK_CONTAINER( e_box ), w_frame );
            g_signal_connect( e_box, "button-press-event", G_CALLBACK( text_grid_click ), app_wdgts );
            g_signal_connect( e_box, "key-press-event", G_CALLBACK( text_grid_keypress ), app_wdgts );
            // Make the event box focussable for the navigation highlight
            gtk_widget_set_can_focus( e_box, TRUE );

            GtkStyleContext *context;
            context = gtk_widget_get_style_context( w_frame );
            // Set the initial highlight to the top left hand corner
            if( ( r == INITIAL_ROW_HIGHLIGHT ) && ( c == INITIAL_COLUMN_HIGHLIGHT ) )
            {
              gtk_style_context_add_class( context, "highlight" );
              gtk_widget_grab_focus( e_box );
              app_wdgts->edit_grid_row = INITIAL_ROW_HIGHLIGHT;
              app_wdgts->edit_grid_column = INITIAL_COLUMN_HIGHLIGHT;
            }
            // And add to the grid
            gtk_grid_attach( GTK_GRID( app_wdgts->w_text_grid ), e_box, c, r, 1, 1 );
          }
        }
        gtk_widget_show_all( app_wdgts->w_text_grid );
      }
      else
      {
        g_info( "  ERROR: could not create grid" );
      }
    }
  }
  else
  {
    g_info( "  ERROR: viewport not found");
  }
  app_wdgts->current_grid_rows = new_rows;
  app_wdgts->current_grid_columns = new_columns;

  g_info( "grid.c / ~fill_grid");
}
