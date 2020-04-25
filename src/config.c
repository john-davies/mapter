// config.c - functions to store and load the .config file
//            design based on: https://wiki.gnome.org/HowDoI/SaveWindowState
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

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <gtk/gtk.h>
#include "main.h"
#include "config.h"

// Storage for window geometries

window_geometry main_window_cache = {-1, -1, FALSE };
window_geometry editor_window_cache = {-1, -1, FALSE };

// --------------------------------------------------------------------------
// on_window_main_destroy
//
// Called on "Quit" command from menu
//
// --------------------------------------------------------------------------

void on_window_main_destroy( app_widgets *app_wdgts )
{
  g_info( "config.c / on_window_main_destroy");
  save_config( app_wdgts );
  gtk_main_quit();
  g_info( "config.c / ~on_window_main_destroy");
}

// --------------------------------------------------------------------------
// on_window_main_size_allocate
//
// Called when main window size changes
//
// --------------------------------------------------------------------------

void on_window_main_size_allocate( GtkWidget *widget, GtkAllocation *allocation, app_widgets *app_wdgts )
{
  g_info( "config.c / on_window_main_size_allocate");

  // save the window geometry only if we are not maximized of fullscreen
  if( gtk_window_is_maximized( GTK_WINDOW( widget ) ) == TRUE )
  {
    main_window_cache.is_maximized = TRUE;
  }
  else
  {
    // Update window size
    gtk_window_get_size( GTK_WINDOW( widget ),
                          &main_window_cache.current_width,
                          &main_window_cache.current_height);
    main_window_cache.is_maximized = FALSE;
  }

  g_info( "config.c / ~on_window_main_size_allocate");
}

// --------------------------------------------------------------------------
// on_editor_window_size_allocate
//
// Called when the editor window size changes
//
// --------------------------------------------------------------------------

void on_editor_window_size_allocate( GtkWidget *widget, GtkAllocation *allocation, app_widgets *app_wdgts )
{
  g_info( "config.c / on_editor_window_size_allocate");

  // save the window geometry only if we are not maximized of fullscreen
  if( gtk_window_is_maximized( GTK_WINDOW( widget ) ) == TRUE )
  {
    editor_window_cache.is_maximized = TRUE;
  }
  else
  {
    // Update window size
    gtk_window_get_size( GTK_WINDOW( widget ),
                          &editor_window_cache.current_width,
                          &editor_window_cache.current_height);
    editor_window_cache.is_maximized = FALSE;
  }

  g_info( "config.c / ~on_editor_window_size_allocate");
}

// --------------------------------------------------------------------------
// save_config
//
// saves the current config
//
// --------------------------------------------------------------------------
gboolean save_config( app_widgets *app_wdgts )
{
  gboolean result = TRUE;
  g_info( "config.c / save_config");
  g_info( "  Main window: %d, %d, %s", main_window_cache.current_width, main_window_cache.current_height, btoa( main_window_cache.is_maximized ) );
  g_info( "  Editor window: %d, %d, %s", editor_window_cache.current_width, editor_window_cache.current_height, btoa( editor_window_cache.is_maximized ) );

  // Build key file
  GKeyFile *keyfile = g_key_file_new ();
  // Main window
  g_key_file_set_integer (keyfile, MAIN_WINDOW_GROUP, MAIN_WINDOW_WIDTH, main_window_cache.current_width);
  g_key_file_set_integer (keyfile, MAIN_WINDOW_GROUP, MAIN_WINDOW_HEIGHT, main_window_cache.current_height);
  g_key_file_set_boolean (keyfile, MAIN_WINDOW_GROUP, MAIN_WINDOW_ISMAX, main_window_cache.is_maximized);
  // Editor window
  g_key_file_set_integer (keyfile, EDITOR_WINDOW_GROUP, EDITOR_WINDOW_WIDTH, editor_window_cache.current_width);
  g_key_file_set_integer (keyfile, EDITOR_WINDOW_GROUP, EDITOR_WINDOW_HEIGHT, editor_window_cache.current_height);
  g_key_file_set_boolean (keyfile, EDITOR_WINDOW_GROUP, EDITOR_WINDOW_ISMAX, editor_window_cache.is_maximized);

  // Check that the destination exists
  gint dir = mkdir( g_build_filename( g_get_user_cache_dir(), APP_NAME, NULL ), APP_CACHE_PERMISSIONS );
  if( dir == 0 || ( ( dir == -1 ) && ( errno == EEXIST ) ) )
  {
    // Write the data
    g_autoptr(GError) error = NULL;
    result = g_key_file_save_to_file( keyfile,
                  g_build_filename( g_get_user_cache_dir(), APP_NAME, CACHE_FILE_NAME, NULL ),
                  &error );
    if( result == FALSE )
    {
      // Couldn't write file so print some error details
      g_info( "  ERROR - could not save key file: %s", error->message );
    }
  }
  else
  {
    // Couldn't create destination
    result = FALSE;
    g_info( "  ERROR - could not create cache file directory" );
  }

  g_info( "config.c / ~save_config");
  return result;
}


// --------------------------------------------------------------------------
// load_config
//
// Loads the stored config file
//
// --------------------------------------------------------------------------
gboolean load_config( app_widgets *app_wdgts )
{
  gboolean result = TRUE;
  g_info( "config.c / load_config");

  // Build filename and fetch data
  GKeyFile *keyfile = g_key_file_new ();
  g_autoptr(GError) error = NULL;
  result = g_key_file_load_from_file( keyfile,
                             g_build_filename( g_get_user_cache_dir(), APP_NAME, CACHE_FILE_NAME, NULL ),
                             G_KEY_FILE_NONE,
                             &error );
  if( result == TRUE )
  {
    gint w, h;
    // Unpack the data
    // Main window
    main_window_cache.current_width = g_key_file_get_integer (keyfile, MAIN_WINDOW_GROUP, MAIN_WINDOW_WIDTH, &error );
    main_window_cache.current_height = g_key_file_get_integer (keyfile, MAIN_WINDOW_GROUP, MAIN_WINDOW_HEIGHT, &error );
    main_window_cache.is_maximized = g_key_file_get_boolean (keyfile, MAIN_WINDOW_GROUP, MAIN_WINDOW_ISMAX, &error );
    // Sanity check to make sure that stored sizes > default
    gtk_window_get_default_size( GTK_WINDOW( app_wdgts->w_window_main ), &w, &h );
    if( ( main_window_cache.current_width < w ) || ( main_window_cache.current_height < h ) )
    {
      // If not then reset to default size
      main_window_cache.current_width = w;
      main_window_cache.current_height = h;
    }
    // Set the window geometry
    gtk_window_resize( GTK_WINDOW( app_wdgts->w_window_main ), main_window_cache.current_width, main_window_cache.current_height );
    if( main_window_cache.is_maximized == TRUE )
    {
      gtk_window_maximize( GTK_WINDOW( app_wdgts->w_window_main ) );
    }

    // Editor window
    editor_window_cache.current_width = g_key_file_get_integer (keyfile, EDITOR_WINDOW_GROUP, EDITOR_WINDOW_WIDTH, &error );
    editor_window_cache.current_height = g_key_file_get_integer (keyfile, EDITOR_WINDOW_GROUP, EDITOR_WINDOW_HEIGHT, &error );
    editor_window_cache.is_maximized = g_key_file_get_boolean (keyfile, EDITOR_WINDOW_GROUP, EDITOR_WINDOW_ISMAX, &error );
    // Sanity check to make sure that stored sizes > default
    gtk_window_get_default_size( GTK_WINDOW( app_wdgts->w_editor_window ), &w, &h );
    if( ( editor_window_cache.current_width < w ) || ( editor_window_cache.current_height < h ) )
    {
      // If not then reset to default size
      editor_window_cache.current_width = w;
      editor_window_cache.current_height = h;
    }
    // Set the window geometry
    gtk_window_resize( GTK_WINDOW( app_wdgts->w_editor_window ), editor_window_cache.current_width, editor_window_cache.current_height );
    if( editor_window_cache.is_maximized == TRUE )
    {
      gtk_window_maximize( GTK_WINDOW( app_wdgts->w_editor_window ) );
    }
  }
  else
  {
    // Problem loading data so report
    g_info( "  ERROR - could not load key file: %s", error->message );
  }

  g_info( "config.c / ~load_config");
  return result;
}
