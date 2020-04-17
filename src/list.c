// list.c - Functions for managing the linked lists that hold the
//          headings and the text body contents
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
#include "list.h"

// Single linked lists definition

GSList *lists[ MAX_LIST ];

// --------------------------------------------------------------------------
// delete_element
//
// Frees the memory used by the GString that's passed in
// Used by list_init
//
// --------------------------------------------------------------------------

void delete_element( gpointer element )
{
  g_string_free( (GString *) element, TRUE );
}

// --------------------------------------------------------------------------
// list_init
//
// Initialises the specified list to hold the specified row and columns
// Any current data in the list are deleted
//
// --------------------------------------------------------------------------

void list_init( guint index, gint rows, gint columns )
{
  g_info( "list.c / list_init");
  if( index < MAX_LIST )
  {
    g_info( "  Initialising - Rows: %d, Columns: %d", rows, columns );
    // Clear and existing data and free any memory
    g_slist_free_full( g_steal_pointer( &lists[index] ), delete_element );
    // Create new blank strings, prepend the strings to make it more
    // efficient then reverse the string later
    for( gint r=0; r<rows; r++ )
    {
      for( gint c=0; c<columns; c++ )
      {
        lists[index] = g_slist_prepend( lists[index], g_string_new( NULL ) );
      }
    }
    lists[index] = g_slist_reverse( lists[index] );
  }
  else
  {
    g_info( "  ERROR - list index out of range: %d", index );
  }
  g_info( "list.c / ~list_init");
}

// --------------------------------------------------------------------------
// list_insert_row
//
// Inserts a new row of cells after the specified position
//
// --------------------------------------------------------------------------

void list_insert_row( guint index, gint row, app_widgets *app_wdgts  )
{
  g_info( "list.c / list_insert_row");
  g_info( "Inserting row at %d", row );
  if( index < MAX_LIST )
  {
    // Check if the row is in range
    if( row < app_wdgts->current_grid_rows )
    {
      // Insert string at the relevant point
      for( gint c=0; c<app_wdgts->current_grid_columns; c++ )
      {
        lists[index] = g_slist_insert( lists[index], g_string_new( NULL ), ( row * app_wdgts->current_grid_columns ) + c );
      }
    }
    else
    {
      g_info( "  ERROR - ignoring row out of range: %d", row );
    }
  }
  else
  {
    g_info( "  ERROR - list index out of range: %d", index );
  }
  g_info( "list.c / ~list_insert_row");
}

// --------------------------------------------------------------------------
// list_insert_column
//
// Inserts a new column of cells after the specified position
//
// --------------------------------------------------------------------------

void list_insert_column( guint index, gint column, app_widgets *app_wdgts  )
{
  g_info( "list.c / list_insert_column");
  g_info( "Inserting column at %d", column );
  if( index < MAX_LIST )
  {
    // Check if the row is in range
    if( column < app_wdgts->current_grid_columns )
    {
      // Insert string at the relevant point
      // Start at the end and work back because the inserts are not contiguous
      for( gint r=app_wdgts->current_grid_rows-1; r>=0; r-- )
      {
        lists[index] = g_slist_insert( lists[index], g_string_new( NULL ), ( r * app_wdgts->current_grid_columns ) + column );
        //g_info( "  Inserting at: %d", ( r * app_wdgts->current_grid_columns ) + column );
      }
    }
    else
    {
      g_info( "  ERROR - ignoring column out of range: %d", column );
    }
  }
  else
  {
    g_info( "  ERROR - list index out of range: %d", index );
  }
  g_info( "list.c / ~list_insert_column");
}

// --------------------------------------------------------------------------
// list_delete_row
//
// Deletes the row of cells at the specified position
//
// --------------------------------------------------------------------------

void list_delete_row( guint index, gint row, app_widgets *app_wdgts  )
{
  g_info( "list.c / list_delete_row");
  g_info( "Deleting row at %d", row );

  if( index < MAX_LIST )
  {
    // Check if the row is in range
    if( row < app_wdgts->current_grid_rows )
    {
      // Delete string at the relevant point
      for( gint c=0; c<app_wdgts->current_grid_columns; c++ )
      {
        // This should free the GString memory as well
        // Don't increment pointer as everything will have shifted down one
        // from the previous delete
        lists[index] = g_slist_delete_link( lists[index],
                              g_slist_nth( lists[index], row * app_wdgts->current_grid_columns ) );
      }
    }
    else
    {
      g_info( "  ERROR - ignoring row out of range: %d", row );
    }
  }
  else
  {
    g_info( "  ERROR - list index out of range: %d", index );
  }

  g_info( "list.c / ~list_delete_row");
}

// --------------------------------------------------------------------------
// list_delete_column
//
// Deletes the column of cells at the specified position
//
// --------------------------------------------------------------------------

void list_delete_column( guint index, gint column, app_widgets *app_wdgts  )
{
  g_info( "list.c / list_delete_column");
  g_info( "Deleting column at %d", column );

  if( index < MAX_LIST )
  {
    // Check if the row is in range
    if( column < app_wdgts->current_grid_columns )
    {
      // Delete string at the relevant point
      for( gint r=app_wdgts->current_grid_rows-1; r>=0; r-- )
      {
        // This should free the GString memory as well
        // Start at the end and work back because the deletions are not contiguous
        lists[index] = g_slist_delete_link( lists[index],
                              g_slist_nth( lists[index], ( r * app_wdgts->current_grid_columns ) + column ) );
        //g_info( "  Deleting at: %d", ( r * app_wdgts->current_grid_columns ) + column );
      }
    }
    else
    {
      g_info( "  ERROR - ignoring column out of range: %d", column );
    }
  }
  else
  {
    g_info( "  ERROR - list index out of range: %d", index );
  }

  g_info( "list.c / ~list_delete_column");
}

// --------------------------------------------------------------------------
// list_get_text
//
// Gets the pointer to the text at the specified list entry
//
// --------------------------------------------------------------------------

gchar *list_get_text( guint index, gint row, gint column, app_widgets *app_wdgts )
{
  gchar *text = NULL;
  gint length;
  g_info( "list.c / list_get_text");
  g_info( "  Reading text at Row: %d, Column %d", row, column );
  if( index < MAX_LIST )
  {
    length = g_slist_length( lists[index] );
    g_info( "  List length: %d", length );

    GString *element = g_slist_nth_data( lists[index], ( row * app_wdgts->current_grid_columns ) + column );
    if( element != NULL )
    {
      text = element->str;
    }
  }
  else
  {
    g_info( "  ERROR - list index out of range: %d", index );
  }

  g_info( "list.c / ~list_get_text");
  return text;

}

// --------------------------------------------------------------------------
// list_put_text
//
// Replaces the text at the specified list entry
//
// --------------------------------------------------------------------------

gchar *list_put_text( guint index, gint row, gint column, gchar *text, app_widgets *app_wdgts )
{
  gint length;
  g_info( "list.c / list_put_text");
  g_info( "  Reading text at Row: %d, Column %d", row, column );
  if( index < MAX_LIST )
  {
    length = g_slist_length( lists[index] );
    g_info( "  List length: %d", length );

    GString *element = g_slist_nth_data( lists[index], ( row * app_wdgts->current_grid_columns ) + column );
    g_string_overwrite( element, 0, text );
  }
  else
  {
    g_info( "  ERROR - list index out of range: %d", index );
  }

  g_info( "list.c / ~list_put_text");
  return text;

}
