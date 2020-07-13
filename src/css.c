// css.c - CSS for mapter
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
.high_background {
  background-color: #FF8080;
}
.medium_background {
  background-color: #FFFF80;
}
.low_background {
  background-color: #7cf580;
}
.neutral_background {
  background-color: #92d1f8;
}
.no_background {
  background-color: #FFFFFF;
}
)"""";
