// file.c - functions to handle the "File" menu items
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "main.h"
#include "file.h"
#include "grid.h"
#include "list.h"
#include "util.h"
#include "json.h"
#include "tree.h"

// --------------------------------------------------------------------------
// on_about_activate
//
// Shows "About" box
//
// --------------------------------------------------------------------------

void on_about_activate( GtkMenuItem *menuitem, app_widgets *app_wdgts )
{
  g_info( "file.c / on_about_activate");
  gtk_widget_show( app_wdgts->w_dlg_about );
  g_info( "file.c / ~on_about_activate");
}

// --------------------------------------------------------------------------
// on_dlg_about_response
//
// Closes "About" box
//
// --------------------------------------------------------------------------

void on_dlg_about_response( GtkDialog *dialog, gint response_id, app_widgets *app_wdgts)
{
  g_info( "file.c / on_dlg_about_response");
  gtk_widget_hide( app_wdgts->w_dlg_about );
  g_info( "file.c / ~on_dlg_about_response");
}

// --------------------------------------------------------------------------
// on_export_activate
//
// Exports the current mapter file
//
// --------------------------------------------------------------------------

void on_export_activate( GtkMenuItem *menuitem, app_widgets *app_wdgts )
{
  gboolean use_cell_0_0;
  gboolean row_chapters;
  gboolean add_series;
  gchar *file_path = NULL;        // Name of file to open from dialog box

  g_info( "file.c / on_export_activate");
  // Launch dialog to get rows/columns
  gtk_widget_show(app_wdgts->w_dlg_export_options );

  // Check return value from Open Text File dialog box to see if user clicked the Open button
  if( gtk_dialog_run( GTK_DIALOG( app_wdgts->w_dlg_export_options ) ) == GTK_RESPONSE_OK )
  {
    // Get the options
    use_cell_0_0 = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( app_wdgts->b_chkbtn_export_title ) );
    row_chapters = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( app_wdgts->b_rdbtn_row ) );
    add_series = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( app_wdgts->b_chkbtn_export_series ) );
    // Close the dialog
    gtk_widget_hide(app_wdgts->w_dlg_export_options );

    // Show the "Export" dialog box
    gtk_widget_show( app_wdgts->w_dlg_export );
    // Check return value from Export dialog box to see if user clicked the Export button
    if( gtk_dialog_run( GTK_DIALOG( app_wdgts->w_dlg_export ) ) == GTK_RESPONSE_OK )
    {
      // Get the export file name
      file_path = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( app_wdgts->w_dlg_export ) );
      g_info( "  Export filename: %s\n", file_path );
      if( file_path != NULL )
      {
        g_info( "  use_cell_0_0 = %s", btoa( use_cell_0_0 ) );
        g_info( "  add_series = %s", btoa( add_series ) );
        // Open export file
        FILE *output_file = fopen( file_path, "w" );
        if( output_file != NULL )
        {
          // And export the data
          // Title
          if( use_cell_0_0 == TRUE )
          {
            gchar *title = list_get_text( HEADER_LIST, 0, 0, app_wdgts );
            gchar *body = list_get_text( BODY_LIST, 0, 0, app_wdgts );
            if( title != NULL )
            {
              fprintf( output_file, "%s\n\n", title );
            }
            if( ( body != NULL ) && ( strlen( body ) > 0 ) )
            {
              fprintf( output_file, "%s\n\n", body );
            }
          }

          if( row_chapters == TRUE )
          {
            // Rows as chapters
            g_info( "  Use rows as chapters" );
            for( gint r=1; r<app_wdgts->current_grid_rows; r++ )
            {
              // Chapter title is in column 0
              gchar *chapter = list_get_text( HEADER_LIST, r, 0, app_wdgts );
              if( ( chapter != NULL ) && ( strlen( chapter ) > 0 ) )
              {
                fprintf( output_file, "%s\n\n", chapter );
              }
              // Now the sections
              for( gint c=1; c<app_wdgts->current_grid_columns; c++ )
              {
                gchar *header = list_get_text( HEADER_LIST, r, c, app_wdgts );
                gchar *body = list_get_text( BODY_LIST, r, c, app_wdgts );
                // Header
                if( ( header != NULL ) && ( strlen( header ) > 0 ) )
                {
                  if( add_series == TRUE )
                  {
                    fprintf( output_file, "%s - ", fetch_cell_contents( app_wdgts->w_text_grid, 0, c  ) );
                  }
                  fprintf( output_file, "%s\n\n", header );
                }
                // Body
                if( ( body != NULL ) && ( strlen( body ) > 0 ) )
                {
                  fprintf( output_file, "%s\n\n", body );
                }
              }
              fprintf( output_file, "\n" );
            }
          }
          else
          {
            // Columns as chapters
            g_info( "  Use columns as chapters" );
            for( gint c=1; c<app_wdgts->current_grid_columns; c++ )
            {
              // Chapter title is in row 0
              gchar *chapter = list_get_text( HEADER_LIST, 0, c, app_wdgts );
              if( ( chapter != NULL ) && ( strlen( chapter ) > 0 ) )
              {
                fprintf( output_file, "%s\n\n", chapter );
              }
              // Now the sections
              for( gint r=1; r<app_wdgts->current_grid_rows; r++ )
              {
                gchar *header = list_get_text( HEADER_LIST, r, c, app_wdgts );
                gchar *body = list_get_text( BODY_LIST, r, c, app_wdgts );
                // Header
                if( ( header != NULL ) && ( strlen( header ) > 0 ) )
                {
                  if( add_series == TRUE )
                  {
                    fprintf( output_file, "%s - ", fetch_cell_contents( app_wdgts->w_text_grid, r, 0  ) );
                  }
                  fprintf( output_file, "%s\n\n", header );
                }
                // Body
                if( ( body != NULL ) && ( strlen( body ) > 0 ) )
                {
                  fprintf( output_file, "%s\n\n", body );
                }
              }
              fprintf( output_file, "\n" );
            }
          }
        }
        else
        {
          g_info( "  ERROR: Could not open file" );
          // Show error if necessary
          GtkWidget *dialog_box = gtk_message_dialog_new( GTK_WINDOW( app_wdgts->w_dlg_open ),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_CLOSE,
                                        NULL );
          gtk_message_dialog_set_markup( GTK_MESSAGE_DIALOG (dialog_box), EXPORT_ERROR );
          gtk_dialog_run( GTK_DIALOG( dialog_box ) );
          gtk_widget_destroy( dialog_box );
        }
        fclose( output_file );
      }
      g_free(file_path);
    }
    // Close the export dialog box
    gtk_widget_hide( app_wdgts->w_dlg_export );
  }
  else
  {
    // Just close the dialog
    gtk_widget_hide(app_wdgts->w_dlg_export_options );
  }
  g_info( "file.c / ~on_export_activate");
}

// --------------------------------------------------------------------------
// open_file
//
// Opens and loads a saved mapter file
//
// --------------------------------------------------------------------------

result_return open_file( gchar* file_path, app_widgets *app_wdgts )
{
  char *json_string = NULL;
  long json_length;
  result_return file_process = { TRUE, "" };
  struct json_value_s *json_data_root = NULL;
  struct json_object_s *json_data_object;
  struct json_object_element_s *json_data_current;
  struct json_string_s *json_data_current_name;
  gint new_rows = -1;
  gint new_columns = -1;

  g_info( "file.c / open_file");

  // Open the file for reading
  FILE *input_file = fopen( file_path, "r" );
  if( input_file == NULL )
  {
    g_info( "  ERROR: Could not open file for reading" );
    file_process.result = FALSE;
    file_process.message = "Could not open file for reading";
    goto error_exit;
  }
  // Calculate the length of the file
  if( fseek( input_file, 0, SEEK_END ) != 0 )
  {
    g_info( "  ERROR: Open file fseek #1 fail" );
    file_process.result = FALSE;
    file_process.message = "Open file fseek #1 fail";
    goto error_exit;
  }
  if( ( json_length = ftell(input_file ) ) == -1 )
  {
    g_info( "  ERROR: Open file ftell fail" );
    file_process.result = FALSE;
    file_process.message = "Open file ftell fail";
    goto error_exit;
  }
  if( fseek( input_file, 0, SEEK_SET ) != 0 )
  {
    g_info( "  ERROR: Open file fseek #2 fail" );
    file_process.result = FALSE;
    file_process.message = "Open file fseek #2 fail";
    goto error_exit;
  }
  // Allocate memory to hold the file
  if( ( json_string = malloc( json_length + 1 ) ) == NULL )
  {
    g_info( "  ERROR: Open file could not allocate buffer" );
    file_process.result = FALSE;
    file_process.message = "Open file could not allocate buffer";
    goto error_exit;
  }
  // And read it
  long bytes_read = fread( json_string, 1, json_length, input_file );
  if( bytes_read != json_length )
  {
    g_info( "  ERROR: Open file wrong number of bytes read ( got: %ld, expected: %ld )", bytes_read, json_length );
    free( json_string );
    file_process.result = FALSE;
    file_process.message = "Open file wrong number of bytes read";
    goto error_exit;
  }
  // Zero terminate the string as fread doesn't do this
  json_string[json_length] = '\0';

  // Parse data
  if( ( json_data_root = json_parse( json_string, json_length ) ) == NULL )
  {
    free( json_string );
    free( json_data_root );
    g_info( "  ERROR: Open file parse failed #1" );
    file_process.result = FALSE;
    file_process.message = "Open file parse failed #1";
    goto error_exit;
  }
  if( ( json_data_object = json_value_as_object( json_data_root ) ) == NULL )
  {
    free( json_string );
    free( json_data_root );
    g_info( "  ERROR: Open file parse failed #2" );
    file_process.result = FALSE;
    file_process.message = "Open file parse failed #2";
    goto error_exit;
  }
  json_data_current = json_data_object->start;
  // Loop through the top level objects
  g_info( "  Reading file: %s ( %ld bytes )", file_path, json_length );
  while( json_data_current != NULL )
  {
    json_data_current_name = json_data_current->name;
    if( strcmp( json_data_current_name->string, VERSION ) == 0 )
    {
      // Check that the version is <= current supported version
      gint version_no = atoi( json_value_as_number( json_data_current->value )->number );
      g_info( "  Version number: %d", version_no );
      if( version_no > SAVE_FILE_VERSION_NUMBER )
      {
        free( json_string );
        free( json_data_root );
        g_info( "  ERROR: Save file version number is unsupported" );
        file_process.result = FALSE;
        file_process.message = "Save file version number is unsupported";
        goto error_exit;
      }
    }
    else if( strcmp( json_data_current_name->string, ROWS ) == 0 )
    {
      // Check that rows >= minimum rows
      new_rows = atoi( json_value_as_number( json_data_current->value )->number );
      g_info( "  Rows: %d", new_rows );
      if( new_rows < MIN_GRID_ROWS )
      {
        free( json_string );
        free( json_data_root );
        g_info( "  ERROR: Row specification too small" );
        file_process.result = FALSE;
        file_process.message = "Row specification too small";
        goto error_exit;
      }
    }
    else if( strcmp( json_data_current_name->string, COLUMNS ) == 0 )
    {
      // Check that columns >= minimum columns
      new_columns = atoi( json_value_as_number( json_data_current->value )->number );
      g_info( "  Columns: %d", new_columns );
      if( new_columns < MIN_GRID_COLUMNS )
      {
        free( json_string );
        free( json_data_root );
        g_info( "  ERROR: Column specification too small" );
        file_process.result = FALSE;
        file_process.message = "Column specification too small";
        goto error_exit;
      }
    }
    else if( strcmp( json_data_current_name->string, TEXT_GRID ) == 0 )
    {
      struct json_array_s* array = json_value_as_array( json_data_current->value );
      g_info( "  Reading text array" );
      // Check that there is the correct number of elements
      if( array->length != ( new_rows * new_columns ) )
      {
        free( json_string );
        free( json_data_root );
        g_info( "  ERROR: Array size does not match" );
        file_process.result = FALSE;
        file_process.message = "Array size does not match";
        goto error_exit;
      }
      // Clear the existing grid and set up a new one of the required dimensions
      fill_grid( new_rows, new_columns, app_wdgts );
      app_wdgts->current_grid_rows = new_rows;
      app_wdgts->current_grid_columns = new_columns;
      struct json_array_element_s* text_array_element = array->start;
      // Loop through text grid
      gint row_idx = 0;
      gint col_idx = 0;
      while( text_array_element != NULL )
      {
        // Get the object at this entry
        struct json_object_s *text_array_element_object = json_value_as_object( text_array_element->value );
        struct json_object_element_s *text_array_element_object_current = text_array_element_object->start;
        // Loop through each object in each array element
        // Get destination cell
        GtkWidget *dest = gtk_grid_get_child_at( GTK_GRID( app_wdgts->w_text_grid ), col_idx, row_idx ); // event box
        while( text_array_element_object_current != NULL )
        {
          const gchar *name = ( text_array_element_object_current->name )->string;
          if( strcmp( name, CELL_BACKGROUND_COLOUR ) == 0 )
          {
            // Set up destination
            app_wdgts->edit_grid_column = col_idx;
            app_wdgts->edit_grid_row = row_idx;
            set_cell_background( atoi( json_value_as_number( text_array_element_object_current->value )->number ), app_wdgts );
          }
          else if( strcmp( name, TEXT_SUMMARY ) == 0 )
          {
            dest = gtk_bin_get_child( GTK_BIN( dest ) ); // frame
            dest = gtk_bin_get_child( GTK_BIN( dest ) ); // label

            // Update text element
            gtk_label_set_text( GTK_LABEL( dest ),
                            json_value_as_string( text_array_element_object_current->value )->string );
          }
          else if( strcmp( name, TEXT_HEADING ) == 0 )
          {
            list_put_text( HEADER_LIST, row_idx, col_idx,
                    (gchar *)json_value_as_string( text_array_element_object_current->value )->string,
                    app_wdgts );
          }
          else if( strcmp( name, TEXT_BODY ) == 0 )
          {
            list_put_text( BODY_LIST, row_idx, col_idx,
                    (gchar *)json_value_as_string( text_array_element_object_current->value )->string,
                    app_wdgts );
          }
          else
          {
            g_info( "ERROR - ignoring entry: %s", name );
          }
          // Step on
          text_array_element_object_current = text_array_element_object_current->next;
        }
        col_idx++;
        if( col_idx == new_columns )
        {
          col_idx = 0;
          row_idx++;
        }
        text_array_element = text_array_element->next;
      }
    }
    else if( strcmp( json_data_current_name->string, TREE_NOTES ) == 0 )
    {
      g_info( "  Reading tree array" );
      // Clear the existing tree
      app_wdgts->stop_node_processing = TRUE;
      gtk_tree_store_clear( app_wdgts->w_notes_treestore );
      app_wdgts->stop_node_processing = FALSE;
      app_wdgts->current_node_status = FALSE;
      // Clear the text view
      gtk_text_buffer_set_text( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_notes_textview ) ), "", -1 );
      // Start to parse JSON
      struct json_array_s* array = json_value_as_array( json_data_current->value );
      struct json_array_element_s* tree_array_element = array->start;
      // Loop through tree
      int count = 0;
      gboolean first_entry = TRUE;
      gint current_level = 0;
      // Linked list for storing tree level iterator
      GSList *import_tree = NULL;
      while( tree_array_element != NULL )
      {
        // Get the data at this row
        struct json_object_s *tree_array_element_object = json_value_as_object( tree_array_element->value );
        struct json_object_element_s *tree_array_element_object_current = tree_array_element_object->start;

        const gchar *name;
        gchar *index;
        gchar *heading;
        gchar *text;

        // Index
        name = ( tree_array_element_object_current->name )->string;
        if( strcmp( name, TREE_INDEX ) != 0 )
        {
          // Error so exit
          g_info( "  ERROR when reading tree index: %d, abandoning import", count );
          free( index );
          free( heading );
          free( text );
          break;
        }
        index = strdup( json_value_as_string( tree_array_element_object_current->value )->string );
        tree_array_element_object_current = tree_array_element_object_current->next;
        // Heading
        name = ( tree_array_element_object_current->name )->string;
        if( strcmp( name, TREE_HEADING ) != 0 )
        {
          // Error so exit
          g_info( "  ERROR when reading tree heading: %d, abandoning import", count );
          free( index );
          free( heading );
          free( text );
          break;
        }
        heading = strdup( json_value_as_string( tree_array_element_object_current->value )->string );
        tree_array_element_object_current = tree_array_element_object_current->next;
        // Text
        name = ( tree_array_element_object_current->name )->string;
        if( strcmp( name, TREE_TEXT ) != 0 )
        {
          // Error so exit
          g_info( "  ERROR when reading tree text: %d, abandoning import", count );
          free( index );
          free( heading );
          free( text );
          break;
        }
        text = strdup( json_value_as_string( tree_array_element_object_current->value )->string );
        tree_array_element_object_current = tree_array_element_object_current->next;
        // Check end
        if( tree_array_element_object_current != NULL )
        {
          g_info( "  ERROR when reading tree entry: %d abandoning import", count );
          free( index );
          free( heading );
          free( text );
          break;
        }
        // Process this row
        // Calculate level = no of ':' characters in index string
        gchar *ptr = index;
        gint level = 0;
        while( *ptr != '\0' )
        {
          if( *ptr == INDEX_SEPARATOR )
          {
            level++;
          }
          ptr++;
        }
        // Dynamically create a tree iter so that it can be stored in the liked list
        void *iter_ptr = g_malloc( sizeof( GtkTreeIter ) );
        if( iter_ptr == NULL )
        {
          // Something went wrong so abandon import
          g_info( "  ERROR when allocating memory: %d abandoning import", count );
          break;
        }

        // Process the data according to the previous level
        if( first_entry == TRUE )
        {
          // This is the first entry so just add at top layer
          gtk_tree_store_append( app_wdgts->w_notes_treestore, iter_ptr, NULL );
          gtk_tree_store_set( app_wdgts->w_notes_treestore, iter_ptr, 0, heading, 1, text, -1);
          // Add to linked list
          import_tree = g_slist_append( import_tree, iter_ptr );
          first_entry = FALSE;
          current_level = 0;
        }
        else if( level == current_level )
        {
          // Add at the same level
          if( level == 0 )
          {
            // Add at the top level
            gtk_tree_store_append( app_wdgts->w_notes_treestore, iter_ptr, NULL );
            gtk_tree_store_set( app_wdgts->w_notes_treestore, iter_ptr, 0, heading, 1, text, -1);
          }
          else
          {
            // Add at the relevant level
            gtk_tree_store_append( app_wdgts->w_notes_treestore, iter_ptr, g_slist_nth_data( import_tree, level-1 ) );
            gtk_tree_store_set( app_wdgts->w_notes_treestore, iter_ptr, 0, heading, 1, text, -1);
          }
          // Replace the entry in the list
          // Add new one
          import_tree = g_slist_insert( import_tree, iter_ptr, level+1 );
          // Remove old one
          GSList * temp_tree_ptr = g_slist_nth( import_tree, level );
          import_tree = g_slist_delete_link( import_tree, temp_tree_ptr );
        }
        else if( level > current_level )
        {
          // Add child
          gtk_tree_store_append( app_wdgts->w_notes_treestore, iter_ptr, g_slist_nth_data( import_tree, level-1 ) );
          gtk_tree_store_set( app_wdgts->w_notes_treestore, iter_ptr, 0, heading, 1, text, -1);
          // Add to linked list
          import_tree = g_slist_append( import_tree, iter_ptr );
          current_level = level;
        }
        else
        {
          // Move up level
          if( level == 0 )
          {
            // Add at the top level
            gtk_tree_store_append( app_wdgts->w_notes_treestore, iter_ptr, NULL );
            gtk_tree_store_set( app_wdgts->w_notes_treestore, iter_ptr, 0, heading, 1, text, -1);
          }
          else
          {
            // Add at the relevant level
            gtk_tree_store_append( app_wdgts->w_notes_treestore, iter_ptr, g_slist_nth_data( import_tree, level-1 ) );
            gtk_tree_store_set( app_wdgts->w_notes_treestore, iter_ptr, 0, heading, 1, text, -1);
          }
          // Replace linked list element and remove all the linked list elements after this level
          // Add new one
          import_tree = g_slist_insert( import_tree, iter_ptr, level+1 );
          // Remove old one
          GSList *temp_tree_ptr = g_slist_nth( import_tree, level );
          import_tree = g_slist_delete_link( import_tree, temp_tree_ptr );
          // Remove remainder
          gint length = g_slist_length( import_tree );
          for( int i = level+1; i<length; i++)
          {
            temp_tree_ptr = g_slist_nth( import_tree, i );
            g_free( g_slist_nth_data( import_tree, i ) ); // Free the data
            import_tree = g_slist_delete_link( import_tree, temp_tree_ptr );
          }
          current_level = level;
        }

        // Free up copies of strings
        free( index );
        free( heading );
        free( text );
        // Next row
        tree_array_element = tree_array_element->next;
        count++;
      }
      // Import finished so clean up linked list
      g_slist_free_full( import_tree, g_free );
    }
    else if( strcmp( json_data_current_name->string, GENERAL_NOTES ) == 0 )
    {
      // Clear the existing tree
      app_wdgts->stop_node_processing = TRUE;
      gtk_tree_store_clear( app_wdgts->w_notes_treestore );
      app_wdgts->stop_node_processing = FALSE;
      app_wdgts->current_node_status = FALSE;
      // Clear the text view
      gtk_text_buffer_set_text( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_notes_textview ) ), "", -1 );
      // Create just a single top level tree entry
      import_single_header( (gchar *) json_value_as_string( json_data_current->value )->string, app_wdgts );
    }
    else
    {
      g_info( "  WARNING: Unknown JSON entry found and ignored: %s", json_data_current_name->string );
    }
    // Step on
    json_data_current = json_data_current->next;
  }

  // Tidy up
  update_file_path( file_path, app_wdgts );
  update_window_title( app_wdgts );

  error_exit: // Destination if an error was found during the file opening
  free( json_string );
  free( json_data_root );

  g_info( "file.c / ~open_file");
  return( file_process );
}

// --------------------------------------------------------------------------
// on_open_activate
//
// Shows an "open file" selector and acts on the results
//
// --------------------------------------------------------------------------

void on_open_activate( GtkMenuItem *menuitem, app_widgets *app_wdgts )
{
    gchar *file_path = NULL;        // Name of file to open from dialog box
    result_return file_op;

    g_info( "file.c / on_open_activate");
    // Show the "Open Text File" dialog box
    gtk_widget_show( app_wdgts->w_dlg_open );

    // Check return value from Open Text File dialog box to see if user clicked the Open button
    if( gtk_dialog_run( GTK_DIALOG( app_wdgts->w_dlg_open ) ) == GTK_RESPONSE_OK )
    {
        // Get the file name from the dialog box
        file_path = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( app_wdgts->w_dlg_open ) );
        if (file_path != NULL)
        {
          file_op = open_file( file_path, app_wdgts );
          if( file_op.result == FALSE )
          {
            // Show error if necessary
            GtkWidget *dialog_box = gtk_message_dialog_new( GTK_WINDOW( app_wdgts->w_dlg_open ),
                                          GTK_DIALOG_DESTROY_WITH_PARENT,
                                          GTK_MESSAGE_ERROR,
                                          GTK_BUTTONS_CLOSE,
                                          NULL );
            gtk_message_dialog_set_markup( GTK_MESSAGE_DIALOG (dialog_box), file_op.message );
            gtk_dialog_run( GTK_DIALOG( dialog_box ) );
            gtk_widget_destroy( dialog_box );
          }
        }
        g_free(file_path);
    }
    gtk_widget_hide(app_wdgts->w_dlg_open );
    g_info( "file.c / ~on_open_activate");
}

// --------------------------------------------------------------------------
// json_encode
//
// JSON encodes the specified string and outputs to the specified file
//
// --------------------------------------------------------------------------

void json_encode( FILE* output_file, const gchar *input_str)
{
  gchar *ip = (gchar *) input_str;
  g_info( "file.c / json_encode");
  // Print only the first 20 characters
  g_info( "  %.20s", input_str );
  while( *ip != '\0' )
  {
    switch( *ip )
    {
      // Special cases
      case '"':
        fprintf( output_file, "\\\"" );
        break;
      case '\\':
        fprintf( output_file, "\\\\" );
        break;
      case '\b':
        fprintf( output_file, "\\b" );
        break;
      case '\f':
        fprintf( output_file, "\\f" );
        break;
      case '\n':
        fprintf( output_file, "\\n" );
        break;
      case '\r':
        fprintf( output_file, "\\r" );
        break;
      case '\t':
        fprintf( output_file, "\\t" );
        break;
      default:
        if( ( *ip > 0 ) && ( *ip < 0x20 ) )
        {
          // Encode with \uxxxx
          fprintf( output_file, "\\u%04X", *ip );
        }
        else
        {
            // Normal character
            fprintf( output_file, "%c", *ip );
        }
        break;
    }
    ip++;
  }
  g_info( "file.c / ~json_encode");
}

// --------------------------------------------------------------------------
// save_file
//
// Saves the current project to a mapter file
//
// --------------------------------------------------------------------------

result_return save_file( app_widgets *app_wdgts )
{
  result_return file_process = { TRUE, "" };

  g_info( "file.c / save_file");
  g_info( "  Save: %s\n", app_wdgts->current_file_path );
  // Open file for writing
  FILE *output_file = fopen( app_wdgts->current_file_path, "w" );
  if( output_file != NULL )
  {
    gint rows = app_wdgts->current_grid_rows;
    gint columns = app_wdgts->current_grid_columns;
    // Header
    fprintf( output_file, "{\n" );

    // Version number
    fprintf( output_file, "\t\"%s\": %d,\n", VERSION, SAVE_FILE_VERSION_NUMBER );

    // Rows and columns
    fprintf( output_file, "\t\"%s\": %d,\n", ROWS, rows );
    fprintf( output_file, "\t\"%s\": %d,\n", COLUMNS, columns );

    // Array of text entries from the Planning Grid tab
    fprintf( output_file, "\t\"%s\": [\n", TEXT_GRID );
    gboolean first = TRUE;
    GtkWidget *child;
    background_colour_type back;
    for( gint r=0; r<rows; r++ )
    {
      for( gint c=0; c<columns; c++ )
      {
        if( first == FALSE )
        {
          // If it's not the first time then print the ,
          fprintf( output_file, ",\n" );
        }
        first = FALSE;
        fprintf( output_file, "\t\t{\n" );
        // Cell background colour
        fprintf( output_file, "\t\t\t\"%s\": ", CELL_BACKGROUND_COLOUR );
        // Set up editing data to retrieve the colour
        app_wdgts->edit_grid_row = r;
        app_wdgts->edit_grid_column = c;
        back = get_cell_background( app_wdgts );
        fprintf( output_file, "%i,\n", back );
        // Summary
        fprintf( output_file, "\t\t\t\"%s\": \"", TEXT_SUMMARY );
        // Fetch the text contents of this cell
        child = gtk_grid_get_child_at( GTK_GRID( app_wdgts->w_text_grid ), c, r ); // GtkEventBox
        child = gtk_bin_get_child( GTK_BIN( child ) ); // GtkFrame
        child = gtk_bin_get_child( GTK_BIN( child ) ); // GtkTextView
        // And output it
        json_encode( output_file, gtk_label_get_text( GTK_LABEL( child ) ) );
        fprintf( output_file, "\",\n" );
        // Heading
        fprintf( output_file, "\t\t\t\"%s\": \"", TEXT_HEADING );
        json_encode( output_file, list_get_text( HEADER_LIST, r, c, app_wdgts ) );
        fprintf( output_file, "\",\n" );
        // Body
        fprintf( output_file, "\t\t\t\"%s\": \"", TEXT_BODY );
        json_encode( output_file, list_get_text( BODY_LIST, r, c, app_wdgts ) );
        fprintf( output_file, "\"\n\t\t}" );

      }
    }
    fprintf( output_file, "\n\t],\n" );  // Close text_grid

    // General Notes Tab
    fprintf( output_file, "\t\"%s\": [\n", TREE_NOTES );
    // Loop through the tree structure
    gtk_tree_model_foreach( GTK_TREE_MODEL( app_wdgts->w_notes_treestore ), print_row, output_file );
    fprintf( output_file, "\n\t]\n" );

    // Footer
    fprintf( output_file, "}\n" );

    // Close file and tidy up
    fclose( output_file );
    update_window_title( app_wdgts );
  }
  else
  {
    g_info( "  ERROR: Could not open file for writing: %s", app_wdgts->current_file_path );
    file_process.result = FALSE;
    file_process.message = "Could not open file for writing";
  }
  g_info( "file.c / ~save_file" );
  return( file_process );
}

// --------------------------------------------------------------------------
// print_row
//
// Prints a single row from the tree to the JSON file
//
// --------------------------------------------------------------------------

gboolean print_row( GtkTreeModel *model, GtkTreePath  *path, GtkTreeIter  *iter, gpointer output_file )
{
  gchar *heading;
  gchar *text;
  gchar *iter_path;
  // Get the data from the tree
  gtk_tree_model_get( model, iter, 0, &heading, 1, &text, -1 );
  iter_path = gtk_tree_model_get_string_from_iter( model, iter );
  // Check if this is not the first one, i.e. path != "0"
  // If so then print the separating comma
  if( !( ( iter_path[0] == '0' ) && ( iter_path[1] == '\0' ) ) )
  {
    fprintf( output_file, ",\n" );
  }
  // Output it
  fprintf( output_file, "\t\t{\n" );
  fprintf( output_file, "\t\t\"index\": \"" );
  json_encode( output_file, iter_path );
  fprintf( output_file, "\",\n" );
  fprintf( output_file, "\t\t\"heading\": \"" );
  json_encode( output_file, heading );
  fprintf( output_file, "\",\n" );
  fprintf( output_file, "\t\t\"text\": \"" );
  json_encode( output_file, text );
  fprintf( output_file, "\"\n" );
  fprintf( output_file, "\t\t}" );
  // Free up resources
  g_free( heading );
  g_free( text );
  g_free( iter_path );

  return FALSE;
}

// --------------------------------------------------------------------------
// on_save_as_activate
//
// Shows an "save file" selector and acts on the results
//
// --------------------------------------------------------------------------

void on_save_as_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gchar *file_name = NULL;        // Name of file to open from dialog box
    result_return save_response;

    g_info( "file.c / on_save_as_activate" );
    gtk_widget_show(app_wdgts->w_dlg_save_as );

    // Check return value to see if user clicked the Save button
    if (gtk_dialog_run(GTK_DIALOG (app_wdgts->w_dlg_save_as ) ) == GTK_RESPONSE_OK)
    {
        // Get the file name from the dialog box
        file_name = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( app_wdgts->w_dlg_save_as ) );
        if (file_name != NULL)
        {
          update_file_path( file_name, app_wdgts );
          save_response = save_file( app_wdgts );
          // Show error if necessary
          if( save_response.result == FALSE )
          {
            // Show error if necessary
            GtkWidget *dialog_box = gtk_message_dialog_new( GTK_WINDOW( app_wdgts->w_dlg_open ),
                                          GTK_DIALOG_DESTROY_WITH_PARENT,
                                          GTK_MESSAGE_ERROR,
                                          GTK_BUTTONS_CLOSE,
                                          NULL );
            gtk_message_dialog_set_markup( GTK_MESSAGE_DIALOG (dialog_box), save_response.message );
            gtk_dialog_run( GTK_DIALOG( dialog_box ) );
            gtk_widget_destroy( dialog_box );
          }
        }
        g_free(file_name);
    }

    gtk_widget_hide(app_wdgts->w_dlg_save_as );
    g_info( "file.c / ~on_save_as_activate" );
}

// --------------------------------------------------------------------------
// on_save_activate
//
// If the file has already been saved then overwites the contents
// If the file hasn't been saved already then showthe "save as" dialog
//
// --------------------------------------------------------------------------

void on_save_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
  result_return save_response;

  g_info( "file.c / on_save_activate" );

  // Check if this file has been saved already
  if( strlen( app_wdgts->current_file_path ) == 0 )
  {
    // No so show "save as"
    on_save_as_activate( menuitem, app_wdgts );
  }
  else
  {
    // Yes so just save
    save_response = save_file( app_wdgts );
    // Show error if necessary
    if( save_response.result == FALSE )
    {
      g_info( "  ERROR: could not save: %s", app_wdgts->current_file_path );
      // Show error if necessary
      GtkWidget *dialog_box = gtk_message_dialog_new( GTK_WINDOW( app_wdgts->w_dlg_open ),
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_CLOSE,
                                    NULL );
      gtk_message_dialog_set_markup( GTK_MESSAGE_DIALOG (dialog_box), save_response.message );
      gtk_dialog_run( GTK_DIALOG( dialog_box ) );
      gtk_widget_destroy( dialog_box );
    }
  }
  g_info( "file.c / ~on_save_activate" );
}

// --------------------------------------------------------------------------
// on_new_activate
//
// Gets the new dimensions from the user then creates a new mapter file
// The current mapter data is discarded
//
// --------------------------------------------------------------------------

void on_new_activate( GtkMenuItem *menuitem, app_widgets *app_wdgts )
{
  gint rows;
  gint columns;
  GtkTreeModel *model;
  GtkTreeIter iter;

  g_info( "file.c / on_new_activate" );
  // Launch dialog to get rows/columns
  gtk_widget_show(app_wdgts->w_dlg_get_row_col );

  // Check return value from Open Text File dialog box to see if user clicked the Open button
  if (gtk_dialog_run(GTK_DIALOG (app_wdgts->w_dlg_get_row_col ) ) == GTK_RESPONSE_OK)
  {
    rows = gtk_spin_button_get_value_as_int( GTK_SPIN_BUTTON( app_wdgts->w_spin_rows ) );
    columns = gtk_spin_button_get_value_as_int( GTK_SPIN_BUTTON( app_wdgts->w_spin_columns ) );
    g_info( "  New: rows=%d, cols=%d", rows, columns );
    fill_grid( rows, columns, app_wdgts );
    update_file_path( "", app_wdgts );
    update_window_title( app_wdgts );
    // Clear the tree view and the text window
    model = gtk_tree_view_get_model( app_wdgts->w_notes_treeview );
    while( gtk_tree_model_get_iter_first( model, &iter) == TRUE )
    {
      // Delete this node
      app_wdgts->current_node_status = FALSE;
      gtk_tree_store_remove( app_wdgts->w_notes_treestore, &iter );
    }
    gtk_text_buffer_set_text( gtk_text_view_get_buffer( GTK_TEXT_VIEW( app_wdgts->w_notes_textview ) ), "", -1 );
  }

  gtk_widget_hide(app_wdgts->w_dlg_get_row_col );
  g_info( "file.c / ~on_new_activate" );
}
