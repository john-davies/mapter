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

void add_row( app_widgets *, gint );
void add_row_above( GtkWidget *, app_widgets * );
void add_row_below( GtkWidget *, app_widgets * );
void delete_row( GtkWidget *source, app_widgets *app_wdgts );

void add_column( app_widgets *, gint );
void add_column_above( GtkWidget *, app_widgets * );
void add_column_below( GtkWidget *, app_widgets * );
void delete_column( GtkWidget *source, app_widgets *app_wdgts );

void on_btn_edit_close_clicked( GtkButton *, app_widgets * );
void on_btn_edit_save_clicked( GtkButton *, app_widgets * );
void text_grid_click( GtkWidget *, GdkEventButton *, app_widgets * );

void fill_grid( gint, gint, app_widgets * );

#endif
