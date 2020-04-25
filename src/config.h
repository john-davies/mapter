// config.h - header file for config.c
//            part of the mapter program
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

#ifndef CONFIG_H
#define CONFIG_H

typedef struct
{
    gint current_width;
    gint current_height;
    gboolean is_maximized;
} window_geometry;

extern window_geometry main_window_cache;
extern window_geometry editor_window_cache;

// File paths etc
#define APP_NAME "mapter"
#define APP_CACHE_PERMISSIONS 0700
#define CACHE_FILE_NAME "mapter.ini"

// Keyfile values
#define MAIN_WINDOW_GROUP "main_window_state"
#define MAIN_WINDOW_WIDTH "width"
#define MAIN_WINDOW_HEIGHT "height"
#define MAIN_WINDOW_ISMAX "is_max"
#define EDITOR_WINDOW_GROUP "editor_window_state"
#define EDITOR_WINDOW_WIDTH "width"
#define EDITOR_WINDOW_HEIGHT "height"
#define EDITOR_WINDOW_ISMAX "is_max"

void on_window_main_destroy( app_widgets * );
void on_window_main_size_allocate( GtkWidget *, GtkAllocation *, app_widgets * );

gboolean load_config( app_widgets * );
gboolean save_config( app_widgets * );

#endif
