// css.h - CSS for mapter
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

#include <gtk/gtk.h>

const gchar *mapter_CSS = R""""(
.highlight{
    border: 3px solid black;
}
.red_background {
  background-color: #FF8080;
}
.yellow_background {
  background-color: #FFFF80;
}
.green_background {
  background-color: #C0FF80;
}
.blue_background {
  background-color: #80FFC0;
}
.grey_background {
  background-color: grey;
}
.no_background {
  background-color: white;
}
)"""";
