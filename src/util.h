// util.h - header file for util.c
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

#ifndef UTIL_H
#define UTIL_H

void update_file_path( gchar *, app_widgets * );
void update_window_title( app_widgets * );
void find_grid_coordinates( GtkWidget *, GtkWidget *, gint *, gint *  );
const gchar *fetch_cell_contents( GtkWidget *, gint, gint );

#endif
