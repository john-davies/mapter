// grid.h - header file for grid.c
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

#ifndef GRID_H
#define GRID_H

// Extra pixels added to scrolling, calculated by experiment
#define XOVERSCROLL 32
#define YOVERSCROLL 20

// Mark name used in search
#define SEARCH_MARK_NAME "last_find"

void add_row( app_widgets *, gint );
void add_row_above( GtkWidget *, app_widgets * );
void add_row_below( GtkWidget *, app_widgets * );
void delete_row( GtkWidget *, app_widgets * );

void add_column( app_widgets *, gint );
void add_column_above( GtkWidget *, app_widgets * );
void add_column_below( GtkWidget *, app_widgets * );
void delete_column( GtkWidget *, app_widgets * );

void set_cell_background( background_colour_type, app_widgets * );
background_colour_type get_cell_background( app_widgets *  );
void set_cell_background_none( GtkWidget *, app_widgets * );
void set_cell_background_red( GtkWidget *, app_widgets * );
void set_cell_background_yellow( GtkWidget *, app_widgets * );
void set_cell_background_green( GtkWidget *, app_widgets * );
void set_cell_background_blue( GtkWidget *, app_widgets * );

void on_btn_statistics_clicked( GtkButton *, app_widgets * );
void on_btn_edit_find_clicked( GtkButton *, app_widgets * );
void on_edit_search_entry_changed( GtkEditable *, app_widgets * );
void on_btn_edit_close_clicked( GtkButton *, app_widgets * );
void on_btn_edit_save_clicked( GtkButton *, app_widgets * );
void edit_cell( gint, gint, app_widgets * );
const gchar *get_cell_text( gint, gint, app_widgets * );
void text_grid_click( GtkWidget *, GdkEventButton *, app_widgets * );
void highlight_cell( gint, gint, gint, gint, gboolean, app_widgets * );
gboolean text_grid_keypress( GtkWidget *, GdkEventKey *, app_widgets * );

void fill_grid( gint, gint, app_widgets * );

#endif
