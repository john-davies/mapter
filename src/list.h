// list.h - header file for list.c
//          part of the mapter program
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

#ifndef LIST_H
#define LIST_H

// Index into array of linked lists
#define MAX_LIST 2      // Number of lists
#define HEADER_LIST 0
#define BODY_LIST 1

void list_init( guint, gint, gint );
void list_insert_row( guint, gint, app_widgets * );
void list_insert_column( guint, gint, app_widgets * );
void list_delete_row( guint, gint, app_widgets * );
void list_delete_column( guint, gint, app_widgets * );
gchar *list_get_text( guint, gint, gint, app_widgets * );
gchar *list_put_text( guint, gint, gint, gchar *, app_widgets * );

#endif
