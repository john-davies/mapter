// file.h - header file for file.c
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

#ifndef FILE_H
#define FILE_H

// JSON Headings
#define VERSION "version"
#define ROWS "rows"
#define COLUMNS "columns"
#define TEXT_GRID "text grid"
#define CELL_BACKGROUND_COLOUR "cell background colour"
#define TEXT_SUMMARY "summary"
#define TEXT_HEADING "heading"
#define TEXT_BODY "body"
#define GENERAL_NOTES "general notes"

void on_about_activate( GtkMenuItem *, app_widgets * );
void on_dlg_about_response( GtkDialog *, gint, app_widgets * );

void on_export_activate( GtkMenuItem *, app_widgets * );

void on_open_activate( GtkMenuItem *, app_widgets * );
void on_save_activate( GtkMenuItem *, app_widgets * );
void on_save_as_activate( GtkMenuItem *, app_widgets * );
void on_new_activate( GtkMenuItem *, app_widgets * );

result_return open_file( gchar*, app_widgets * );
result_return save_file( app_widgets * );

void json_encode( FILE*, const gchar *);

#endif
