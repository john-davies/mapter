// file.h - header file for tree.c
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

#ifndef TREE_H
#define TREE_H

void on_btn_add_heading_clicked( GtkWidget *, app_widgets * );
void on_btn_add_child_clicked( GtkWidget *, app_widgets * );
void on_btn_delete_heading_clicked( GtkWidget *, app_widgets * );
void on_notes_tree_section_r_edited( GtkCellRendererText *, gchar *, gchar *, app_widgets * );
void on_notes_treestore_selection_changed( GtkWidget *, app_widgets * );
void import_single_header( gchar *, app_widgets * );

#endif
