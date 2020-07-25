// main.h - header file for main.c
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

#ifndef MAIN_H
#define MAIN_H

#include <gtk/gtk.h>

// Version number
#define SAVE_FILE_VERSION_NUMBER 3

// Grid definitions
#define MIN_GRID_ROWS 1
#define MIN_GRID_COLUMNS 1
#define DEFAULT_ROWS 5
#define DEFAULT_COLUMNS 5
#define INITIAL_ROW_HIGHLIGHT 0
#define INITIAL_COLUMN_HIGHLIGHT 0

// Maximum path & file lengths
#define APP_NAME_SIZE 256
#define MAX_PATHSIZE 4096
#define MAX_FILENAME 256
#define MAX_WINDOW_TITLE APP_NAME_SIZE + MAX_FILENAME + 4
#define DIRECTORY_SEPARATOR '/'

// Error strings
#define EXPORT_ERROR "Error opening export file"

// Layout
// Width of each cell in characters
#define LABEL_WIDTH 20

// Useful macros
// Convert a boolean into a printable string
#define btoa(x) ( (x) ? "TRUE" : "FALSE" )

// Custom structure that holds pointers to widgets and user variables
typedef struct {
    // Row / columns sizes for grid
    gint current_grid_rows;
    gint current_grid_columns;
    // Temporary row and column values for use in grid editing
    gint edit_grid_row;
    gint edit_grid_column;
    GtkWidget *w_current_edit_text_element;
    // Pointers to widgets
    GtkWidget *w_window_main;
    GtkWidget *w_grid_container; // Scrolled window
    GtkWidget *w_grid_viewport;
    GtkWidget *w_text_grid;  // Dynamically added
    GtkWidget *w_dlg_save_as;
    GtkWidget *w_dlg_open;
    GtkWidget *w_dlg_get_row_col;
    GtkWidget *w_dlg_about;
    GtkWidget *w_spin_rows;
    GtkWidget *w_spin_columns;
    GtkWidget *w_grid_right_click_menu;
    GtkWidget *w_editor_window;
    GtkWidget *w_edit_summary;
    GtkWidget *w_edit_heading;
    GtkWidget *w_edit_body;
    // Tree View
    GtkWidget *w_notes_textview;
    GtkTreeView *w_notes_treeview;
    GtkTreeStore *w_notes_treestore;
    GtkTreeSelection *w_notes_treestore_selection;
    GtkTreeViewColumn *w_notes_tree_section;
    GtkCellRenderer *w_notes_tree_section_r;
    GtkTreeViewColumn *w_notes_tree_text;
    GtkCellRenderer *w_notes_tree_text_r;
    GtkWidget *w_dlg_delete;
    GtkWidget *w_dlg_export_options;
    GtkTreeIter current_node;
    gboolean current_node_status;
    GtkWidget *b_chkbtn_export_title;
    GtkWidget *b_rdbtn_row;
    GtkWidget *b_chkbtn_export_series;
    GtkWidget *w_dlg_export;
    GtkWidget *l_row_id_label;
    GtkWidget *l_column_id_label;
    // Accelerator group for right click menu
    GtkAccelGroup *right_click_accel_group;
    // Current open file path
    gchar app_name[ APP_NAME_SIZE ];
    gchar current_file_path[ MAX_PATHSIZE ];
    gchar current_file_name[ MAX_FILENAME ];
    gchar window_title[ MAX_WINDOW_TITLE ];
} app_widgets;

// Error return for file operations
typedef struct {
  gboolean result;
  gchar *message;
} result_return;

// Colours for cell background
// Note also the values in css.c
typedef enum { NONE = 0, HIGH, MEDIUM, LOW, NEUTRAL } background_colour_type;

#endif
