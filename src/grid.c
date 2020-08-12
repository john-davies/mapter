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
#include "list.h"
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
  // Add a row in the linked lists
  list_insert_row( HEADER_LIST, row, app_wdgts );
  list_insert_row( BODY_LIST, row, app_wdgts );
  // Update the setting
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
  // Update the position of the highlighted cell
  app_wdgts->edit_grid_row++;
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
  gint delete_row = app_wdgts->edit_grid_row;
  if( app_wdgts->current_grid_rows > 1 )
  {
    g_info( "  Delete row: %d", app_wdgts->edit_grid_row );
    // Move the highlight. If this is row 0 then move down
    // otherwise move up
    if( app_wdgts->edit_grid_row == 0 )
    {
      highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                      app_wdgts->edit_grid_row + 1, app_wdgts->edit_grid_column,
                      TRUE, app_wdgts );
    }
    else
    {
      highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                      app_wdgts->edit_grid_row - 1, app_wdgts->edit_grid_column,
                      TRUE, app_wdgts );
      // Correct the highlight location
      app_wdgts->edit_grid_row--;
    }
    gtk_grid_remove_row( GTK_GRID( app_wdgts->w_text_grid ), delete_row );
    // Delete a row from the linked lists
    list_delete_row( HEADER_LIST, delete_row, app_wdgts );
    list_delete_row( BODY_LIST, delete_row, app_wdgts );
    // Update settings
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
  // Add a row in the linked lists
  list_insert_column( HEADER_LIST, column, app_wdgts );
  list_insert_column( BODY_LIST, column, app_wdgts );
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
  // Update the position of the highlighted cell
  app_wdgts->edit_grid_column++;
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
  gint delete_column = app_wdgts->edit_grid_column;
  if( app_wdgts->current_grid_columns > 1 )
  {
    g_info( "  Delete column: %d", app_wdgts->edit_grid_column );
    // Move the highlight. If this is column 0 then move to the right
    // otherwise move to the left
    if( app_wdgts->edit_grid_column == 0 )
    {
      highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                      app_wdgts->edit_grid_row, app_wdgts->edit_grid_column + 1,
                      TRUE, app_wdgts );
    }
    else
    {
      highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                      app_wdgts->edit_grid_row, app_wdgts->edit_grid_column - 1,
                      TRUE, app_wdgts );
      // Correct the highlight location
      app_wdgts->edit_grid_column--;
    }
    gtk_grid_remove_column( GTK_GRID( app_wdgts->w_text_grid ), delete_column );
    // Delete a column from the linked lists
    list_delete_column( HEADER_LIST, delete_column, app_wdgts );
    list_delete_column( BODY_LIST, delete_column, app_wdgts );

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
// get_cell_background
//
// Gets the current selected cell background colour
//
// --------------------------------------------------------------------------
background_colour_type get_cell_background( app_widgets *app_wdgts )
{
  GtkStyleContext *context;
  background_colour_type cell_colour;
  g_info( "grid.c / get_cell_background");
  GtkWidget *e_box = gtk_grid_get_child_at( GTK_GRID( app_wdgts->w_text_grid ), app_wdgts->edit_grid_column, app_wdgts->edit_grid_row );
  // Now get the frame
  GtkWidget *child = gtk_bin_get_child( GTK_BIN( e_box ) );
  // Then the text view
  child = gtk_bin_get_child( GTK_BIN( child ) );
  context = gtk_widget_get_style_context( child );
  // Get current background
  if( gtk_style_context_has_class( context, "high_background" ) )
  {
    g_info( "  Current background: high_background" );
    cell_colour = HIGH;
  }
  else if( gtk_style_context_has_class( context, "medium_background" ) )
  {
    g_info( "  Current background: medium_background" );
    cell_colour = MEDIUM;
  }
  else if( gtk_style_context_has_class( context, "low_background" ) )
  {
    g_info( "  Current background: medium_background" );
    cell_colour = LOW;
  }
  else if( gtk_style_context_has_class( context, "neutral_background" ) )
  {
    g_info( "  Current background: neutral_background" );
    cell_colour = NEUTRAL;
  }
  else
  {
    g_info( "  Current background: no_background" );
    cell_colour = NONE;
  }
  g_info( "grid.c / ~set_cell_background");
  return cell_colour;
}

// --------------------------------------------------------------------------
// set_cell_background
//
// Sets the cell background to the specified colour
//
// --------------------------------------------------------------------------
void set_cell_background( background_colour_type colour, app_widgets *app_wdgts )
{
  GtkStyleContext *context;
  g_info( "grid.c / set_cell_background");
  GtkWidget *e_box = gtk_grid_get_child_at( GTK_GRID( app_wdgts->w_text_grid ), app_wdgts->edit_grid_column, app_wdgts->edit_grid_row );
  // Now get the frame
  GtkWidget *child = gtk_bin_get_child( GTK_BIN( e_box ) );
  // Then the text view
  child = gtk_bin_get_child( GTK_BIN( child ) );
  context = gtk_widget_get_style_context( child );
  // Clear the current CSS classes - quicker to do it this way than
  // try to read each class
  gtk_style_context_remove_class( context, "no_background" );
  gtk_style_context_remove_class( context, "high_background" );
  gtk_style_context_remove_class( context, "medium_background" );
  gtk_style_context_remove_class( context, "low_background" );
  gtk_style_context_remove_class( context, "neutral_background" );
  // Set background
  switch( colour )
  {
    case HIGH:
      gtk_style_context_add_class( context, "high_background" );
      break;
    case MEDIUM:
      gtk_style_context_add_class( context, "medium_background" );
      break;
    case LOW:
      gtk_style_context_add_class( context, "low_background" );
      break;
    case NEUTRAL:
      gtk_style_context_add_class( context, "neutral_background" );
      break;
    default:
      // Everything else default to none
      gtk_style_context_add_class( context, "no_background" );
      break;
  }
  g_info( "grid.c / ~set_cell_background");
}

// --------------------------------------------------------------------------
// set_cell_background_none
//
// Clears any cell background colour
//
// --------------------------------------------------------------------------
void set_cell_background_none( GtkWidget *source, app_widgets *app_wdgts )
{
  background_colour_type colour = NONE;
  g_info( "grid.c / set_cell_background_none");
  set_cell_background( colour, app_wdgts );
  g_info( "grid.c / ~set_cell_background_none");
}

// --------------------------------------------------------------------------
// set_cell_background_high
//
// Sets the cell background to be high priority
// Defined by CSS ".high_background"
//
// --------------------------------------------------------------------------
void set_cell_background_high( GtkWidget *source, app_widgets *app_wdgts )
{
  background_colour_type colour = HIGH;
  g_info( "grid.c / set_cell_background_high");
  set_cell_background( colour, app_wdgts );
  g_info( "grid.c / ~set_cell_background_high");
}

// --------------------------------------------------------------------------
// set_cell_background_medium
//
// Sets the cell background to be medium priority
// Defined by CSS ".medium_background"
//
// --------------------------------------------------------------------------
void set_cell_background_medium( GtkWidget *source, app_widgets *app_wdgts )
{
  background_colour_type colour = MEDIUM;
  g_info( "grid.c / set_cell_background_medium");
  set_cell_background( colour, app_wdgts );
  g_info( "grid.c / ~set_cell_background_medium");
}

// --------------------------------------------------------------------------
// set_cell_background_low
//
// Sets the cell background to be low
// Defined by CSS ".low_background"
//
// --------------------------------------------------------------------------
void set_cell_background_low( GtkWidget *source, app_widgets *app_wdgts )
{
  background_colour_type colour = LOW;
  g_info( "grid.c / set_cell_background_low");
  set_cell_background( colour, app_wdgts );
  g_info( "grid.c / ~set_cell_background_low");
}

// --------------------------------------------------------------------------
// set_cell_background_neutral
//
// Sets the cell background to be neutral
// Defined by CSS ".neutral_background"
//
// --------------------------------------------------------------------------
void set_cell_background_neutral( GtkWidget *source, app_widgets *app_wdgts )
{
  background_colour_type colour = NEUTRAL;
  g_info( "grid.c / set_cell_background_neutral");
  set_cell_background( colour, app_wdgts );
  g_info( "grid.c / ~set_cell_background_neutral");
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
  // Copy text from editor to save destinations
  // Summary
  gtk_text_buffer_get_start_iter( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_edit_summary ) ), &start );
  gtk_text_buffer_get_end_iter( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_edit_summary ) ), &end );
  gtk_label_set_text( GTK_LABEL( app_wdgts->w_current_edit_text_element ),
                      gtk_text_buffer_get_text( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_edit_summary ) ),
                            &start,
                            &end,
                            FALSE ) );
  // Header
  gtk_text_buffer_get_start_iter( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_edit_heading ) ), &start );
  gtk_text_buffer_get_end_iter( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_edit_heading ) ), &end );
  gchar *new_text = gtk_text_buffer_get_text( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_edit_heading ) ), &start, &end, FALSE );
  list_put_text( HEADER_LIST,
                 app_wdgts->edit_grid_row,
                 app_wdgts->edit_grid_column,
                 new_text,
                 app_wdgts );
  // Free up text
  g_free( new_text );
  // Body
  gtk_text_buffer_get_start_iter( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_edit_body ) ), &start );
  gtk_text_buffer_get_end_iter( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_edit_body ) ), &end );
  new_text = gtk_text_buffer_get_text( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_edit_body ) ), &start, &end, FALSE );
  list_put_text( BODY_LIST,
                 app_wdgts->edit_grid_row,
                 app_wdgts->edit_grid_column,
                 new_text,
                 app_wdgts );
  // Free up text
  g_free( new_text );

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
  // Copy current summary text
  gtk_text_buffer_set_text( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_edit_summary ) ),
                        gtk_label_get_text( GTK_LABEL( app_wdgts->w_current_edit_text_element ) ),
                        -1 );
  // Read Heading from the linked list
  gtk_text_buffer_set_text( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_edit_heading ) ),
                        list_get_text( HEADER_LIST, row, column, app_wdgts ),
                        -1 );
  // Read Body Text from the linked list
  gtk_text_buffer_set_text( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_edit_body ) ),
                        list_get_text( BODY_LIST, row, column, app_wdgts ),
                        -1 );
  // Show the Edit window
  gtk_widget_show( app_wdgts->w_editor_window );
  // Put the keyboard focus in the text window
  gtk_window_present( GTK_WINDOW( app_wdgts->w_editor_window ) );
  gtk_widget_grab_focus( app_wdgts->w_edit_body );
  // Move cursor to the beginning of the buffer
  GtkTextIter iter;
  gtk_text_buffer_get_start_iter( gtk_text_view_get_buffer( GTK_TEXT_VIEW(app_wdgts->w_edit_body ) ), &iter );
  gtk_text_buffer_place_cursor( gtk_text_view_get_buffer( GTK_TEXT_VIEW(app_wdgts->w_edit_body ) ), &iter );

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
                      TRUE, app_wdgts );
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
    // Move the highlight if this is a different cell
    if( ( row != app_wdgts->edit_grid_row ) || ( column != app_wdgts->edit_grid_column ) )
    {
      highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                      row, column,
                      TRUE, app_wdgts );
      // Update the coordinates
      app_wdgts->edit_grid_row = row;
      app_wdgts->edit_grid_column = column;
    }
    // Show popup menu
    // For now this is built manually because of problems with the Glade version
    GtkWidget *option;
    GtkWidget *pmenu = gtk_menu_new();
    // Cell colouring
    // None
    option = gtk_menu_item_new_with_label( "Clear Priority" );
    gtk_widget_show( option );
    g_signal_connect( G_OBJECT( option ), "activate", G_CALLBACK( set_cell_background_none ), app_wdgts );
    gtk_menu_shell_append( GTK_MENU_SHELL( pmenu ), option );
    gtk_widget_add_accelerator( option, "activate", app_wdgts->right_click_accel_group,
                                 GDK_KEY_0, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE );
    // High
    option = gtk_menu_item_new_with_label( "High Priority" );
    gtk_widget_show( option );
    g_signal_connect( G_OBJECT( option ), "activate", G_CALLBACK( set_cell_background_high ), app_wdgts );
    gtk_menu_shell_append( GTK_MENU_SHELL( pmenu ), option );
    gtk_widget_add_accelerator( option, "activate", app_wdgts->right_click_accel_group,
                                 GDK_KEY_1, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE );
    // Medium
    option = gtk_menu_item_new_with_label( "Medium Priority" );
    gtk_widget_show( option );
    g_signal_connect( G_OBJECT( option ), "activate", G_CALLBACK( set_cell_background_medium ), app_wdgts );
    gtk_menu_shell_append( GTK_MENU_SHELL( pmenu ), option );
    gtk_widget_add_accelerator( option, "activate", app_wdgts->right_click_accel_group,
                                 GDK_KEY_2, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE );
    // Low
    option = gtk_menu_item_new_with_label( "Low Priority" );
    gtk_widget_show( option );
    g_signal_connect( G_OBJECT( option ), "activate", G_CALLBACK( set_cell_background_low ), app_wdgts );
    gtk_menu_shell_append( GTK_MENU_SHELL( pmenu ), option );
    gtk_widget_add_accelerator( option, "activate", app_wdgts->right_click_accel_group,
                                 GDK_KEY_3, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE );
    // Neutral
    option = gtk_menu_item_new_with_label( "Neutral Priority" );
    gtk_widget_show( option );
    g_signal_connect( G_OBJECT( option ), "activate", G_CALLBACK( set_cell_background_neutral ), app_wdgts );
    gtk_menu_shell_append( GTK_MENU_SHELL( pmenu ), option );
    gtk_widget_add_accelerator( option, "activate", app_wdgts->right_click_accel_group,
                                 GDK_KEY_4, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE );
    // Separator
    option = gtk_separator_menu_item_new();
    gtk_widget_show( option );
    gtk_menu_shell_append( GTK_MENU_SHELL( pmenu ), option );
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

  g_info( "grid.c / highlight_cell");
  g_info( "  Current - row: %d, column: %d, New - row: %d, Column: %d", current_r, current_c, new_r, new_c );
  // Remove the current highlight - get the event box
  GtkWidget *e_box = gtk_grid_get_child_at( GTK_GRID( app_wdgts->w_text_grid ), current_c, current_r );
  // Now get the frame
  GtkWidget *child = gtk_bin_get_child( GTK_BIN( e_box ) );
  context = gtk_widget_get_style_context( child );
  gtk_style_context_remove_class( context, "highlight" );

  // Add the new highlight, source is the event box
  // so find the child to find the frame
  e_box = gtk_grid_get_child_at( GTK_GRID( app_wdgts->w_text_grid ), new_c, new_r );
  // Set focus to the event box
  gtk_widget_grab_focus( e_box );
  if( gtk_widget_is_focus( e_box ) == FALSE )
  {
    g_info( "  ERROR - could not grab focus" );
  }
  child = gtk_bin_get_child( GTK_BIN( e_box ) ); // Frame
  context = gtk_widget_get_style_context( child );
  gtk_style_context_add_class( context, "highlight" );

  // If required scroll to show the focus - move the scroll bars in the same proportion as
  // the current cell is to the grid. This is not ideal but the best compromise for now
  if( scroll == TRUE )
  {
    // Find the current size of the focussed element and its position on screen
    GtkAllocation alloc_ebox, alloc_scroll, alloc_grid;
    GtkAdjustment *hadjustment, *vadjustment;
    gtk_widget_get_allocation( app_wdgts->w_grid_container, &alloc_scroll );
    gtk_widget_get_allocation( app_wdgts->w_text_grid, &alloc_grid );
    gtk_widget_get_allocation( e_box, &alloc_ebox );
    // Calculate the current horizontal scroll bar position
    hadjustment = gtk_scrolled_window_get_hadjustment( GTK_SCROLLED_WINDOW( app_wdgts->w_grid_container ) );
    gdouble xlower = gtk_adjustment_get_lower( hadjustment );
    gdouble xupper = gtk_adjustment_get_upper( hadjustment );
    gdouble xpage_size = gtk_adjustment_get_page_size( hadjustment );
    gdouble xrange = xupper - xpage_size - xlower;
    gdouble xvalue = gtk_adjustment_get_value( hadjustment );
    gint max_xoffset = alloc_grid.width - alloc_scroll.width;
    gint xoffset = max_xoffset * ( xvalue / xrange );
    gdouble xcount_per_pixel = xrange / max_xoffset;
    // Work out if any scroll adjustment is needed
    if( ( alloc_ebox.x + alloc_ebox.width ) > ( alloc_scroll.width + xoffset ) )
    {
      // Right scroll
      gint scroll_right = ( alloc_ebox.x + alloc_ebox.width ) - ( alloc_scroll.width + xoffset ) + XOVERSCROLL;
      g_info( "  Scroll right %d pixels", scroll_right );
      gdouble xnew_value = xvalue + ( scroll_right * xcount_per_pixel );
      gtk_adjustment_set_value( hadjustment, xnew_value );
    }
    else if ( alloc_ebox.x < xoffset )
    {
      // Left scroll
      gint scroll_left = xoffset - alloc_ebox.x + XOVERSCROLL;
      g_info( "  Scroll left %d pixels", scroll_left );
      gdouble xnew_value = xvalue - ( scroll_left * xcount_per_pixel );
      gtk_adjustment_set_value( hadjustment, xnew_value );
    }

    // Calculate the current vertical scroll bar position
    vadjustment = gtk_scrolled_window_get_vadjustment( GTK_SCROLLED_WINDOW( app_wdgts->w_grid_container ) );
    gdouble ylower = gtk_adjustment_get_lower( vadjustment );
    gdouble yupper = gtk_adjustment_get_upper( vadjustment );
    gdouble ypage_size = gtk_adjustment_get_page_size( vadjustment );
    gdouble yrange = yupper - ypage_size - ylower;
    gdouble yvalue = gtk_adjustment_get_value( vadjustment );
    gint max_yoffset = alloc_grid.height - alloc_scroll.height;
    gint yoffset = max_yoffset * ( yvalue / yrange );
    gdouble ycount_per_pixel = yrange / max_yoffset;
    // Work out if any scroll adjustment is needed
    if( ( alloc_ebox.y + alloc_ebox.height ) > ( alloc_scroll.height + yoffset ) )
    {
      // Scroll down
      gint scroll_down = ( alloc_ebox.y + alloc_ebox.height ) - ( alloc_scroll.height + yoffset ) + YOVERSCROLL;
      g_info( "  Scroll down %d pixels", scroll_down );
      gdouble ynew_value = yvalue + ( scroll_down * ycount_per_pixel );
      gtk_adjustment_set_value( vadjustment, ynew_value );
    }
    else if ( alloc_ebox.y < yoffset )
    {
      // Scroll up
      gint scroll_up = yoffset - alloc_ebox.y + YOVERSCROLL;
      g_info( "  Scroll up %d pixels", scroll_up );
      gdouble ynew_value = yvalue - ( scroll_up * ycount_per_pixel );
      gtk_adjustment_set_value( vadjustment, ynew_value );
    }
  }

  // Update the coordinate labels
  if( ( new_r == 0 ) && ( new_c == 0 ) )
  {
    // If it's the top left hand cell then don't show anything
    gtk_label_set_text( GTK_LABEL( app_wdgts->l_row_id_label ), "" );
    gtk_label_set_text( GTK_LABEL( app_wdgts->l_column_id_label ), "" );
  }
  else if( new_r == 0 )
  {
    // Top row so just show the series name
    gtk_label_set_text( GTK_LABEL( app_wdgts->l_row_id_label ), "" );
    gtk_label_set_text( GTK_LABEL( app_wdgts->l_column_id_label ), get_cell_text( 0, new_c, app_wdgts ) );
  }
  else if( new_c == 0 )
  {
    // Left column so just show the chapter
    gtk_label_set_text( GTK_LABEL( app_wdgts->l_row_id_label ), get_cell_text( new_r, 0, app_wdgts ) );
    gtk_label_set_text( GTK_LABEL( app_wdgts->l_column_id_label ), "" );
  }
  else
  {
    // Otherwise show the row and column headers
    gtk_label_set_text( GTK_LABEL( app_wdgts->l_row_id_label ), get_cell_text( new_r, 0, app_wdgts ) );
    gtk_label_set_text( GTK_LABEL( app_wdgts->l_column_id_label ), get_cell_text( 0, new_c, app_wdgts ) );
  }
  g_info( "grid.c / ~highlight_cell");
}

// --------------------------------------------------------------------------
// text_grid_keypress
//
// Processes the keyboard presses on the text grid
//
// --------------------------------------------------------------------------

gboolean text_grid_keypress( GtkWidget *source, GdkEventKey *event, app_widgets *app_wdgts )
{
  gboolean inhibit = FALSE; // Set true to inhibit further keypress processing
  g_info( "grid.c / text_grid_keypress");
  switch( event->keyval )
  {
    case GDK_KEY_Return:
      g_info( "  Open editor on row: %d, column: %d", app_wdgts->edit_grid_row, app_wdgts->edit_grid_column );
      // Show the Edit window
      edit_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column, app_wdgts );
      inhibit = TRUE;
      break;

    case GDK_KEY_Left:
      if( app_wdgts->edit_grid_column > 0 )
      {
        if( ( event->state & GDK_SHIFT_MASK ) == 0 )
        {
          // No shift key so just move left
          g_info( "  Left" );
          highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                          app_wdgts->edit_grid_row, app_wdgts->edit_grid_column-1,
                          TRUE, app_wdgts );
          app_wdgts->edit_grid_column--;
        }
        else
        {
          // Shift key so move to column 0
          g_info( "  Shift Left" );
          highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                          app_wdgts->edit_grid_row, 0,
                          TRUE, app_wdgts );
          app_wdgts->edit_grid_column = 0;
        }
      }
      inhibit = TRUE;
      break;
    case GDK_KEY_Up:
      if( app_wdgts->edit_grid_row > 0 )
      {
        if( ( event->state & GDK_SHIFT_MASK ) == 0 )
        {
          // No shift key so just move up
          g_info( "  Up" );
          highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                          app_wdgts->edit_grid_row-1, app_wdgts->edit_grid_column,
                          TRUE, app_wdgts );
          app_wdgts->edit_grid_row--;
        }
        else
        {
          // Shift key so move to row 0
          g_info( "  Shift Up" );
          highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                          0, app_wdgts->edit_grid_column,
                          TRUE, app_wdgts );
          app_wdgts->edit_grid_row = 0;
        }
      }
      inhibit = TRUE;
      break;
    case GDK_KEY_Right:
      if( app_wdgts->edit_grid_column < app_wdgts->current_grid_columns-1 )
      {
        if( ( event->state & GDK_SHIFT_MASK ) == 0 )
        {
          // No shift key so just move right
          g_info( "  Right" );
          highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                          app_wdgts->edit_grid_row, app_wdgts->edit_grid_column+1,
                          TRUE, app_wdgts );
          app_wdgts->edit_grid_column++;
        }
        else
        {
          // Shift key so move to last column
          g_info( "  Shift Right" );
          highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                          app_wdgts->edit_grid_row, app_wdgts->current_grid_columns - 1,
                          TRUE, app_wdgts );
          app_wdgts->edit_grid_column = app_wdgts->current_grid_columns - 1;
        }
      }
      inhibit = TRUE;
      break;
    case GDK_KEY_Down:
      if( app_wdgts->edit_grid_row < app_wdgts->current_grid_rows-1 )
      {
        if( ( event->state & GDK_SHIFT_MASK ) == 0 )
        {
          // No shift key so just move down
          g_info( "  Down" );
          highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                          app_wdgts->edit_grid_row+1, app_wdgts->edit_grid_column,
                          TRUE, app_wdgts );
          app_wdgts->edit_grid_row++;
        }
        else
        {
          // Shift key so move to bottom row
          g_info( "  Shift Down" );
          highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                          app_wdgts->current_grid_rows-1, app_wdgts->edit_grid_column,
                          TRUE, app_wdgts );
          app_wdgts->edit_grid_row = app_wdgts->current_grid_rows - 1;
        }
      }
      inhibit = TRUE;
      break;
    case GDK_KEY_Home:
      g_info( "  Home" );
      highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                      0, 0,
                      TRUE, app_wdgts );
      app_wdgts->edit_grid_row = 0;
      app_wdgts->edit_grid_column = 0;
      break;
      inhibit = TRUE;
    case GDK_KEY_End:
      g_info( "  End" );
      highlight_cell( app_wdgts->edit_grid_row, app_wdgts->edit_grid_column,
                      app_wdgts->current_grid_rows - 1, app_wdgts->current_grid_columns - 1,
                      TRUE, app_wdgts );
      app_wdgts->edit_grid_row = app_wdgts->current_grid_rows - 1;
      app_wdgts->edit_grid_column = app_wdgts->current_grid_columns - 1;
      break;
      inhibit = TRUE;
    default:
      g_info( " Ignoring: %x", event->keyval );
      break;
  }
  g_info( "grid.c / ~text_grid_keypress");
  return( inhibit );
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
  GtkWidget *focus_widget;
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
              focus_widget = e_box; // Store this for later
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

  // Set up the linked lists
  list_init( HEADER_LIST, new_rows, new_columns );
  list_init( BODY_LIST, new_rows, new_columns );

  // Now set the focus to the correct cell
  gtk_widget_grab_focus( focus_widget );
  if( gtk_widget_is_focus( focus_widget ) == FALSE )
  {
    g_info( "  ERROR - could not grab focus" );
  }

  g_info( "grid.c / ~fill_grid");
}
