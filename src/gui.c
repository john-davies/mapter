// gui.c - GUI definition file for mapter
//         Generated using Glade and make_gui.sh script
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

const gchar *glade_definition = R""""(

<?xml version="1.0" encoding="UTF-8"?>
<!-- Generated with glade 3.18.3 -->
<interface>
  <requires lib="gtk+" version="3.12"/>
  <requires lib="gtksourceview" version="3.0"/>
  <object class="GtkAdjustment" id="adj_columns">
    <property name="lower">1</property>
    <property name="upper">100</property>
    <property name="value">1</property>
    <property name="step_increment">1</property>
    <property name="page_increment">10</property>
  </object>
  <object class="GtkAdjustment" id="adj_rows">
    <property name="upper">100</property>
    <property name="step_increment">1</property>
    <property name="page_increment">10</property>
  </object>
  <object class="GtkMessageDialog" id="dlg_delete_warning">
    <property name="can_focus">False</property>
    <property name="modal">True</property>
    <property name="type_hint">dialog</property>
    <property name="message_type">warning</property>
    <property name="text" translatable="yes">Warning, this node and any children will be deleted.</property>
    <child internal-child="vbox">
      <object class="GtkBox" id="messagedialog-vbox">
        <property name="can_focus">False</property>
        <property name="orientation">vertical</property>
        <property name="spacing">2</property>
        <child internal-child="action_area">
          <object class="GtkButtonBox" id="messagedialog-action_area">
            <property name="can_focus">False</property>
            <property name="homogeneous">True</property>
            <property name="layout_style">end</property>
            <child>
              <object class="GtkButton" id="btn_delete_cancel">
                <property name="label">gtk-cancel</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <property name="use_stock">True</property>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">True</property>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="btn_delete_ok">
                <property name="label">gtk-ok</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <property name="use_stock">True</property>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">True</property>
                <property name="position">1</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">False</property>
            <property name="position">0</property>
          </packing>
        </child>
      </object>
    </child>
    <action-widgets>
      <action-widget response="-6">btn_delete_cancel</action-widget>
      <action-widget response="-5">btn_delete_ok</action-widget>
    </action-widgets>
  </object>
  <object class="GtkMenu" id="grid_right_click_menu">
    <property name="visible">True</property>
    <property name="can_focus">False</property>
    <property name="margin_top">5</property>
    <child>
      <object class="GtkMenuItem" id="add_row_above">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
        <property name="label" translatable="yes">Add row above</property>
        <property name="use_underline">True</property>
      </object>
    </child>
    <child>
      <object class="GtkMenuItem" id="add_row_below">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
        <property name="label" translatable="yes">Add row below</property>
        <property name="use_underline">True</property>
      </object>
    </child>
    <child>
      <object class="GtkMenuItem" id="delete_row">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
        <property name="label" translatable="yes">Delete row</property>
        <property name="use_underline">True</property>
      </object>
    </child>
    <child>
      <object class="GtkSeparatorMenuItem" id="menuitem2">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
      </object>
    </child>
    <child>
      <object class="GtkMenuItem" id="add_column_left">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
        <property name="label" translatable="yes">Add column left</property>
        <property name="use_underline">True</property>
      </object>
    </child>
    <child>
      <object class="GtkMenuItem" id="add_column_right">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
        <property name="label" translatable="yes">Add column right</property>
        <property name="use_underline">True</property>
      </object>
    </child>
    <child>
      <object class="GtkMenuItem" id="delete_column">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
        <property name="label" translatable="yes">Delete column</property>
        <property name="use_underline">True</property>
      </object>
    </child>
  </object>
  <object class="GtkImage" id="image1">
    <property name="visible">True</property>
    <property name="can_focus">False</property>
    <property name="stock">gtk-file</property>
  </object>
  <object class="GtkFileFilter" id="mapter files">
    <patterns>
      <pattern>*.mapter</pattern>
    </patterns>
  </object>
  <object class="GtkTreeStore" id="notes_treestore">
    <columns>
      <!-- column-name section -->
      <column type="gchararray"/>
      <!-- column-name text -->
      <column type="gchararray"/>
    </columns>
  </object>
  <object class="GtkWindow" id="window_main">
    <property name="width_request">600</property>
    <property name="height_request">400</property>
    <property name="can_focus">False</property>
    <property name="title" translatable="yes">Mapter</property>
    <signal name="destroy" handler="on_window_main_destroy" swapped="no"/>
    <signal name="size-allocate" handler="on_window_main_size_allocate" swapped="no"/>
    <child>
      <object class="GtkBox" id="box1">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
        <property name="orientation">vertical</property>
        <child>
          <object class="GtkMenuBar" id="menubar1">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <child>
              <object class="GtkMenuItem" id="menuitem1">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label" translatable="yes">_File</property>
                <property name="use_underline">True</property>
                <child type="submenu">
                  <object class="GtkMenu" id="menu1">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <child>
                      <object class="GtkImageMenuItem" id="new">
                        <property name="label">gtk-new</property>
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="use_underline">True</property>
                        <property name="use_stock">True</property>
                        <signal name="activate" handler="on_new_activate" swapped="no"/>
                        <accelerator key="n" signal="activate" modifiers="GDK_CONTROL_MASK"/>
                      </object>
                    </child>
                    <child>
                      <object class="GtkImageMenuItem" id="open">
                        <property name="label">gtk-open</property>
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="use_underline">True</property>
                        <property name="use_stock">True</property>
                        <signal name="activate" handler="on_open_activate" swapped="no"/>
                        <accelerator key="o" signal="activate" modifiers="GDK_CONTROL_MASK"/>
                      </object>
                    </child>
                    <child>
                      <object class="GtkImageMenuItem" id="save">
                        <property name="label">gtk-save</property>
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="use_underline">True</property>
                        <property name="use_stock">True</property>
                        <signal name="activate" handler="on_save_activate" swapped="no"/>
                        <accelerator key="s" signal="activate" modifiers="GDK_CONTROL_MASK"/>
                      </object>
                    </child>
                    <child>
                      <object class="GtkImageMenuItem" id="save_as">
                        <property name="label">gtk-save-as</property>
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="use_underline">True</property>
                        <property name="use_stock">True</property>
                        <signal name="activate" handler="on_save_as_activate" swapped="no"/>
                        <accelerator key="s" signal="activate" modifiers="GDK_SHIFT_MASK | GDK_CONTROL_MASK"/>
                      </object>
                    </child>
                    <child>
                      <object class="GtkSeparatorMenuItem" id="separatormenuitem1">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                      </object>
                    </child>
                    <child>
                      <object class="GtkImageMenuItem" id="export">
                        <property name="label">Export</property>
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="image">image1</property>
                        <property name="use_stock">False</property>
                        <signal name="activate" handler="on_export_activate" swapped="no"/>
                        <accelerator key="e" signal="activate" modifiers="GDK_CONTROL_MASK"/>
                      </object>
                    </child>
                    <child>
                      <object class="GtkSeparatorMenuItem" id="separatormenuitem2">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                      </object>
                    </child>
                    <child>
                      <object class="GtkImageMenuItem" id="quit">
                        <property name="label">gtk-quit</property>
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="use_underline">True</property>
                        <property name="use_stock">True</property>
                        <signal name="activate" handler="on_window_main_destroy" swapped="no"/>
                        <accelerator key="q" signal="activate" modifiers="GDK_CONTROL_MASK"/>
                      </object>
                    </child>
                  </object>
                </child>
              </object>
            </child>
            <child>
              <object class="GtkMenuItem" id="menuitem4">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label" translatable="yes">_Help</property>
                <property name="use_underline">True</property>
                <child type="submenu">
                  <object class="GtkMenu" id="menu3">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <child>
                      <object class="GtkImageMenuItem" id="about">
                        <property name="label">gtk-about</property>
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="use_underline">True</property>
                        <property name="use_stock">True</property>
                        <signal name="activate" handler="on_about_activate" swapped="no"/>
                      </object>
                    </child>
                  </object>
                </child>
              </object>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">0</property>
          </packing>
        </child>
        <child>
          <object class="GtkNotebook" id="notebook1">
            <property name="visible">True</property>
            <property name="can_focus">True</property>
            <child>
              <object class="GtkScrolledWindow" id="grid_container">
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="shadow_type">in</property>
                <child>
                  <object class="GtkViewport" id="grid_viewport">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <child>
                      <placeholder/>
                    </child>
                  </object>
                </child>
              </object>
            </child>
            <child type="tab">
              <object class="GtkLabel" id="label1">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label" translatable="yes">Planning grid</property>
              </object>
              <packing>
                <property name="tab_fill">False</property>
              </packing>
            </child>
            <child>
              <object class="GtkPaned" id="paned1">
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="margin_bottom">2</property>
                <child>
                  <object class="GtkBox" id="box7">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="orientation">vertical</property>
                    <child>
                      <object class="GtkScrolledWindow" id="tree_container">
                        <property name="visible">True</property>
                        <property name="can_focus">True</property>
                        <property name="vexpand">True</property>
                        <property name="shadow_type">in</property>
                        <child>
                          <object class="GtkTreeView" id="notes_treeview">
                            <property name="visible">True</property>
                            <property name="can_focus">True</property>
                            <property name="hscroll_policy">natural</property>
                            <property name="model">notes_treestore</property>
                            <property name="search_column">1</property>
                            <child internal-child="selection">
                              <object class="GtkTreeSelection" id="notes_treestore_selection">
                                <signal name="changed" handler="on_notes_treestore_selection_changed" swapped="no"/>
                              </object>
                            </child>
                            <child>
                              <object class="GtkTreeViewColumn" id="notes_tree_section">
                                <property name="spacing">1</property>
                                <property name="title" translatable="yes">Section</property>
                                <child>
                                  <object class="GtkCellRendererText" id="notes_tree_section_r">
                                    <property name="editable">True</property>
                                    <signal name="edited" handler="on_notes_tree_section_r_edited" swapped="no"/>
                                  </object>
                                </child>
                              </object>
                            </child>
                            <child>
                              <object class="GtkTreeViewColumn" id="notes_tree_text">
                                <property name="visible">False</property>
                                <property name="title" translatable="yes">Text</property>
                                <child>
                                  <object class="GtkCellRendererText" id="notes_tree_text_r"/>
                                </child>
                              </object>
                            </child>
                          </object>
                        </child>
                      </object>
                      <packing>
                        <property name="expand">False</property>
                        <property name="fill">True</property>
                        <property name="position">0</property>
                      </packing>
                    </child>
                    <child>
                      <object class="GtkBox" id="box8">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="margin_top">10</property>
                        <property name="margin_bottom">10</property>
                        <property name="homogeneous">True</property>
                        <child>
                          <object class="GtkButton" id="btn_add_heading">
                            <property name="label" translatable="yes">Add</property>
                            <property name="visible">True</property>
                            <property name="can_focus">True</property>
                            <property name="receives_default">True</property>
                            <property name="halign">center</property>
                            <signal name="clicked" handler="on_btn_add_heading_clicked" swapped="no"/>
                          </object>
                          <packing>
                            <property name="expand">False</property>
                            <property name="fill">True</property>
                            <property name="position">0</property>
                          </packing>
                        </child>
                        <child>
                          <object class="GtkButton" id="btn_add_child">
                            <property name="label" translatable="yes">Add child</property>
                            <property name="visible">True</property>
                            <property name="can_focus">True</property>
                            <property name="receives_default">True</property>
                            <property name="halign">center</property>
                            <signal name="clicked" handler="on_btn_add_child_clicked" swapped="no"/>
                          </object>
                          <packing>
                            <property name="expand">False</property>
                            <property name="fill">True</property>
                            <property name="position">1</property>
                          </packing>
                        </child>
                        <child>
                          <object class="GtkButton" id="btn_delete_heading">
                            <property name="label" translatable="yes">Delete</property>
                            <property name="visible">True</property>
                            <property name="can_focus">True</property>
                            <property name="receives_default">True</property>
                            <property name="halign">center</property>
                            <signal name="clicked" handler="on_btn_delete_heading_clicked" swapped="no"/>
                          </object>
                          <packing>
                            <property name="expand">False</property>
                            <property name="fill">True</property>
                            <property name="position">2</property>
                          </packing>
                        </child>
                      </object>
                      <packing>
                        <property name="expand">False</property>
                        <property name="fill">True</property>
                        <property name="position">1</property>
                      </packing>
                    </child>
                  </object>
                  <packing>
                    <property name="resize">False</property>
                    <property name="shrink">True</property>
                  </packing>
                </child>
                <child>
                  <object class="GtkScrolledWindow" id="notes_container">
                    <property name="visible">True</property>
                    <property name="can_focus">True</property>
                    <property name="vexpand">True</property>
                    <property name="shadow_type">in</property>
                    <child>
                      <object class="GtkSourceView" id="notes_textview">
                        <property name="visible">True</property>
                        <property name="can_focus">True</property>
                        <property name="border_width">3</property>
                        <property name="wrap_mode">word-char</property>
                        <property name="left_margin">2</property>
                        <property name="right_margin">2</property>
                      </object>
                    </child>
                  </object>
                  <packing>
                    <property name="resize">True</property>
                    <property name="shrink">True</property>
                  </packing>
                </child>
              </object>
              <packing>
                <property name="position">1</property>
              </packing>
            </child>
            <child type="tab">
              <object class="GtkLabel" id="label2">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label" translatable="yes">General notes</property>
              </object>
              <packing>
                <property name="position">1</property>
                <property name="tab_fill">False</property>
              </packing>
            </child>
            <child>
              <placeholder/>
            </child>
            <child type="tab">
              <placeholder/>
            </child>
          </object>
          <packing>
            <property name="expand">True</property>
            <property name="fill">True</property>
            <property name="position">1</property>
          </packing>
        </child>
        <child>
          <object class="GtkGrid" id="grid1">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="margin_left">5</property>
            <property name="margin_right">5</property>
            <property name="margin_top">5</property>
            <property name="margin_bottom">5</property>
            <child>
              <object class="GtkLabel" id="label5">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="halign">end</property>
                <property name="label" translatable="yes">Chapter: </property>
              </object>
              <packing>
                <property name="left_attach">0</property>
                <property name="top_attach">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkLabel" id="label6">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="halign">end</property>
                <property name="label" translatable="yes">Series: </property>
              </object>
              <packing>
                <property name="left_attach">0</property>
                <property name="top_attach">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkLabel" id="row_id_label">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="halign">start</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="top_attach">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkLabel" id="column_id_label">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="halign">start</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="top_attach">1</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">3</property>
          </packing>
        </child>
      </object>
    </child>
  </object>
  <object class="GtkAboutDialog" id="dlg_about">
    <property name="can_focus">False</property>
    <property name="type">popup</property>
    <property name="title" translatable="yes">About mapter</property>
    <property name="resizable">False</property>
    <property name="type_hint">dialog</property>
    <property name="deletable">False</property>
    <property name="transient_for">window_main</property>
    <property name="program_name">mapter</property>
    <property name="version">Version 0.6</property>
    <property name="copyright" translatable="yes">Copyright John Davies 2021</property>
    <property name="website">https://github.com/john-davies/mapter</property>
    <property name="website_label" translatable="yes">GitHub repository</property>
    <property name="authors">John Davies</property>
    <property name="logo_icon_name">help-about</property>
    <property name="license_type">gpl-3-0</property>
    <signal name="response" handler="on_dlg_about_response" swapped="no"/>
    <child internal-child="vbox">
      <object class="GtkBox" id="aboutdialog-vbox1">
        <property name="can_focus">False</property>
        <property name="orientation">vertical</property>
        <property name="spacing">2</property>
        <child internal-child="action_area">
          <object class="GtkButtonBox" id="aboutdialog-action_area1">
            <property name="can_focus">False</property>
            <property name="layout_style">end</property>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">False</property>
            <property name="position">0</property>
          </packing>
        </child>
        <child>
          <placeholder/>
        </child>
      </object>
    </child>
  </object>
  <object class="GtkFileChooserDialog" id="dlg_export">
    <property name="can_focus">False</property>
    <property name="window_position">center</property>
    <property name="type_hint">dialog</property>
    <property name="transient_for">window_main</property>
    <property name="action">save</property>
    <property name="do_overwrite_confirmation">True</property>
    <child internal-child="vbox">
      <object class="GtkBox" id="filechooserdialog-vbox4">
        <property name="can_focus">False</property>
        <property name="orientation">vertical</property>
        <property name="spacing">2</property>
        <child internal-child="action_area">
          <object class="GtkButtonBox" id="filechooserdialog-action_area4">
            <property name="can_focus">False</property>
            <property name="layout_style">end</property>
            <child>
              <object class="GtkButton" id="btn_export_cance">
                <property name="label">gtk-cancel</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <property name="use_stock">True</property>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">True</property>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="btn_export">
                <property name="label" translatable="yes">Export</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="can_default">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">True</property>
                <property name="position">1</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">False</property>
            <property name="position">0</property>
          </packing>
        </child>
        <child>
          <placeholder/>
        </child>
      </object>
    </child>
    <action-widgets>
      <action-widget response="-6">btn_export_cance</action-widget>
      <action-widget response="-5">btn_export</action-widget>
    </action-widgets>
  </object>
  <object class="GtkDialog" id="dlg_export_options">
    <property name="can_focus">False</property>
    <property name="resizable">False</property>
    <property name="window_position">center</property>
    <property name="type_hint">dialog</property>
    <property name="transient_for">window_main</property>
    <child internal-child="vbox">
      <object class="GtkBox" id="dialog-vbox2">
        <property name="can_focus">False</property>
        <property name="orientation">vertical</property>
        <property name="spacing">2</property>
        <child internal-child="action_area">
          <object class="GtkButtonBox" id="dialog-action_area2">
            <property name="can_focus">False</property>
            <property name="layout_style">end</property>
            <child>
              <object class="GtkButton" id="btn_export_cancel">
                <property name="label">gtk-cancel</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <property name="use_stock">True</property>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">True</property>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="btn_export_ok">
                <property name="label">gtk-ok</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <property name="use_stock">True</property>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">True</property>
                <property name="position">1</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">False</property>
            <property name="position">0</property>
          </packing>
        </child>
        <child>
          <object class="GtkBox" id="box4">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="border_width">8</property>
            <property name="orientation">vertical</property>
            <child>
              <object class="GtkCheckButton" id="chkbtn_export_dup_cr">
                <property name="label" translatable="yes">Duplicate carriage returns</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">False</property>
                <property name="margin_top">10</property>
                <property name="xalign">0</property>
                <property name="active">True</property>
                <property name="draw_indicator">True</property>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkCheckButton" id="chkbtn_export_title">
                <property name="label" translatable="yes">Use cell at 0,0 as title</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">False</property>
                <property name="margin_top">10</property>
                <property name="xalign">0</property>
                <property name="draw_indicator">True</property>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkCheckButton" id="chkbtn_export_series">
                <property name="label" translatable="yes">Preface each entry with the Series description</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">False</property>
                <property name="margin_top">10</property>
                <property name="xalign">0</property>
                <property name="draw_indicator">True</property>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">3</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">1</property>
          </packing>
        </child>
      </object>
    </child>
    <action-widgets>
      <action-widget response="-6">btn_export_cancel</action-widget>
      <action-widget response="-5">btn_export_ok</action-widget>
    </action-widgets>
  </object>
  <object class="GtkDialog" id="dlg_get_row_col">
    <property name="can_focus">False</property>
    <property name="resizable">False</property>
    <property name="type_hint">dialog</property>
    <property name="transient_for">window_main</property>
    <child internal-child="vbox">
      <object class="GtkBox" id="dialog-vbox1">
        <property name="can_focus">False</property>
        <property name="orientation">vertical</property>
        <property name="spacing">2</property>
        <child internal-child="action_area">
          <object class="GtkButtonBox" id="dialog-action_area1">
            <property name="can_focus">False</property>
            <property name="layout_style">end</property>
            <child>
              <object class="GtkButton" id="btn_cancel">
                <property name="label">gtk-cancel</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <property name="use_stock">True</property>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">True</property>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="btn_create">
                <property name="label">gtk-apply</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <property name="relief">none</property>
                <property name="use_stock">True</property>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">True</property>
                <property name="position">1</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">False</property>
            <property name="position">0</property>
          </packing>
        </child>
        <child>
          <object class="GtkGrid" id="grid2">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <child>
              <object class="GtkLabel" id="label3">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="halign">end</property>
                <property name="margin_right">10</property>
                <property name="label" translatable="yes">Rows:</property>
              </object>
              <packing>
                <property name="left_attach">0</property>
                <property name="top_attach">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkLabel" id="label4">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="halign">end</property>
                <property name="margin_right">10</property>
                <property name="label" translatable="yes">Columns:</property>
              </object>
              <packing>
                <property name="left_attach">0</property>
                <property name="top_attach">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkSpinButton" id="spin_rows">
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="max_length">3</property>
                <property name="width_chars">10</property>
                <property name="max_width_chars">10</property>
                <property name="adjustment">adj_rows</property>
                <property name="numeric">True</property>
                <property name="value">1</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="top_attach">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkSpinButton" id="spin_columns">
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="max_length">3</property>
                <property name="width_chars">10</property>
                <property name="adjustment">adj_columns</property>
                <property name="numeric">True</property>
                <property name="value">1</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="top_attach">1</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">1</property>
          </packing>
        </child>
      </object>
    </child>
    <action-widgets>
      <action-widget response="-6">btn_cancel</action-widget>
      <action-widget response="-5">btn_create</action-widget>
    </action-widgets>
  </object>
  <object class="GtkFileChooserDialog" id="dlg_open">
    <property name="can_focus">False</property>
    <property name="title" translatable="yes">Open</property>
    <property name="type_hint">normal</property>
    <property name="transient_for">window_main</property>
    <property name="filter">mapter files</property>
    <child internal-child="vbox">
      <object class="GtkBox" id="filechooserdialog-vbox2">
        <property name="can_focus">False</property>
        <property name="orientation">vertical</property>
        <property name="spacing">2</property>
        <child internal-child="action_area">
          <object class="GtkButtonBox" id="filechooserdialog-action_area2">
            <property name="can_focus">False</property>
            <property name="layout_style">end</property>
            <child>
              <object class="GtkButton" id="btn_cancel_open">
                <property name="label">gtk-cancel</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <property name="use_stock">True</property>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">True</property>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="btn_open">
                <property name="label">gtk-open</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="can_default">True</property>
                <property name="receives_default">True</property>
                <property name="use_stock">True</property>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">True</property>
                <property name="position">1</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">False</property>
            <property name="position">0</property>
          </packing>
        </child>
        <child>
          <placeholder/>
        </child>
      </object>
    </child>
    <action-widgets>
      <action-widget response="-6">btn_cancel_open</action-widget>
      <action-widget response="-5">btn_open</action-widget>
    </action-widgets>
  </object>
  <object class="GtkFileChooserDialog" id="dlg_save_as">
    <property name="can_focus">False</property>
    <property name="title" translatable="yes">Save as</property>
    <property name="type_hint">dialog</property>
    <property name="transient_for">window_main</property>
    <property name="action">save</property>
    <property name="do_overwrite_confirmation">True</property>
    <property name="filter">mapter files</property>
    <child internal-child="vbox">
      <object class="GtkBox" id="filechooserdialog-vbox1">
        <property name="can_focus">False</property>
        <property name="orientation">vertical</property>
        <property name="spacing">2</property>
        <child internal-child="action_area">
          <object class="GtkButtonBox" id="filechooserdialog-action_area1">
            <property name="can_focus">False</property>
            <property name="layout_style">end</property>
            <child>
              <object class="GtkButton" id="btn_cancel_save_as">
                <property name="label">gtk-cancel</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <property name="use_stock">True</property>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">True</property>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="btn_save_as">
                <property name="label">gtk-save-as</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="can_default">True</property>
                <property name="receives_default">True</property>
                <property name="use_stock">True</property>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">True</property>
                <property name="position">1</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">False</property>
            <property name="position">0</property>
          </packing>
        </child>
        <child>
          <placeholder/>
        </child>
      </object>
    </child>
    <action-widgets>
      <action-widget response="-6">btn_cancel_save_as</action-widget>
      <action-widget response="-5">btn_save_as</action-widget>
    </action-widgets>
  </object>
  <object class="GtkWindow" id="editor_window">
    <property name="width_request">600</property>
    <property name="height_request">400</property>
    <property name="can_focus">False</property>
    <property name="title" translatable="yes">mapter Editor</property>
    <property name="modal">True</property>
    <property name="window_position">center-on-parent</property>
    <property name="deletable">False</property>
    <property name="transient_for">window_main</property>
    <signal name="size-allocate" handler="on_editor_window_size_allocate" swapped="no"/>
    <child>
      <object class="GtkBox" id="box2">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
        <property name="border_width">5</property>
        <property name="orientation">vertical</property>
        <child>
          <object class="GtkFrame" id="summary_frame">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="margin_top">3</property>
            <property name="label_xalign">0</property>
            <property name="shadow_type">none</property>
            <child>
              <object class="GtkAlignment" id="alignment3">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <child>
                  <object class="GtkScrolledWindow" id="scrolledwindow4">
                    <property name="visible">True</property>
                    <property name="can_focus">True</property>
                    <property name="shadow_type">in</property>
                    <child>
                      <object class="GtkSourceView" id="edit_summary">
                        <property name="visible">True</property>
                        <property name="can_focus">True</property>
                        <property name="border_width">3</property>
                        <property name="wrap_mode">word-char</property>
                        <property name="left_margin">2</property>
                        <property name="right_margin">2</property>
                      </object>
                    </child>
                  </object>
                </child>
              </object>
            </child>
            <child type="label">
              <object class="GtkLabel" id="label10">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label" translatable="yes">Summary</property>
              </object>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">0</property>
          </packing>
        </child>
        <child>
          <object class="GtkFrame" id="heading_frame">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="margin_top">3</property>
            <property name="label_xalign">0</property>
            <property name="shadow_type">none</property>
            <child>
              <object class="GtkAlignment" id="alignment1">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <child>
                  <object class="GtkScrolledWindow" id="scrolledwindow2">
                    <property name="visible">True</property>
                    <property name="can_focus">True</property>
                    <property name="shadow_type">in</property>
                    <child>
                      <object class="GtkSourceView" id="edit_heading">
                        <property name="visible">True</property>
                        <property name="can_focus">True</property>
                        <property name="border_width">3</property>
                        <property name="wrap_mode">word-char</property>
                        <property name="left_margin">2</property>
                        <property name="right_margin">2</property>
                      </object>
                    </child>
                  </object>
                </child>
              </object>
            </child>
            <child type="label">
              <object class="GtkLabel" id="label7">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label" translatable="yes">Heading</property>
              </object>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">2</property>
          </packing>
        </child>
        <child>
          <object class="GtkFrame" id="text_body_frame">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="margin_top">3</property>
            <property name="vexpand">True</property>
            <property name="label_xalign">0</property>
            <property name="shadow_type">none</property>
            <child>
              <object class="GtkAlignment" id="alignment2">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <child>
                  <object class="GtkScrolledWindow" id="scrolledwindow3">
                    <property name="visible">True</property>
                    <property name="can_focus">True</property>
                    <property name="shadow_type">in</property>
                    <child>
                      <object class="GtkSourceView" id="edit_body">
                        <property name="visible">True</property>
                        <property name="can_focus">True</property>
                        <property name="border_width">3</property>
                        <property name="wrap_mode">word-char</property>
                        <property name="left_margin">2</property>
                        <property name="right_margin">2</property>
                      </object>
                    </child>
                  </object>
                </child>
              </object>
            </child>
            <child type="label">
              <object class="GtkLabel" id="label9">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label" translatable="yes">Body</property>
              </object>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">3</property>
          </packing>
        </child>
        <child>
          <object class="GtkBox" id="box3">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="spacing">10</property>
            <child>
              <object class="GtkButton" id="btn_statistics">
                <property name="label" translatable="yes">Statistics</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <property name="halign">center</property>
                <property name="margin_left">10</property>
                <property name="margin_top">10</property>
                <property name="margin_bottom">10</property>
                <signal name="clicked" handler="on_btn_statistics_clicked" swapped="no"/>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkBox" id="box5">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="halign">center</property>
                <child>
                  <object class="GtkEntry" id="edit_search_entry">
                    <property name="visible">True</property>
                    <property name="can_focus">True</property>
                    <signal name="activate" handler="on_btn_edit_find_clicked" swapped="no"/>
                    <signal name="changed" handler="on_edit_search_entry_changed" swapped="no"/>
                  </object>
                  <packing>
                    <property name="expand">False</property>
                    <property name="fill">True</property>
                    <property name="position">0</property>
                  </packing>
                </child>
                <child>
                  <object class="GtkButton" id="btn_edit_find">
                    <property name="label">gtk-find</property>
                    <property name="visible">True</property>
                    <property name="can_focus">True</property>
                    <property name="receives_default">True</property>
                    <property name="halign">center</property>
                    <property name="margin_top">10</property>
                    <property name="margin_bottom">10</property>
                    <property name="use_stock">True</property>
                    <signal name="clicked" handler="on_btn_edit_find_clicked" swapped="no"/>
                  </object>
                  <packing>
                    <property name="expand">False</property>
                    <property name="fill">True</property>
                    <property name="position">1</property>
                  </packing>
                </child>
                <child>
                  <object class="GtkCheckButton" id="check_btn_edit_case">
                    <property name="label" translatable="yes">Match case</property>
                    <property name="visible">True</property>
                    <property name="can_focus">True</property>
                    <property name="receives_default">False</property>
                    <property name="xalign">0</property>
                    <property name="draw_indicator">True</property>
                    <signal name="toggled" handler="on_edit_search_entry_changed" swapped="no"/>
                  </object>
                  <packing>
                    <property name="expand">False</property>
                    <property name="fill">True</property>
                    <property name="position">2</property>
                  </packing>
                </child>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="btn_edit_save">
                <property name="label">gtk-save</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <property name="halign">center</property>
                <property name="margin_right">10</property>
                <property name="margin_top">10</property>
                <property name="margin_bottom">10</property>
                <property name="use_stock">True</property>
                <signal name="clicked" handler="on_btn_edit_save_clicked" swapped="no"/>
                <accelerator key="s" signal="activate" modifiers="GDK_CONTROL_MASK"/>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="pack_type">end</property>
                <property name="position">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="btn_edit_close">
                <property name="label">gtk-close</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <property name="halign">center</property>
                <property name="margin_top">10</property>
                <property name="margin_bottom">10</property>
                <property name="use_stock">True</property>
                <property name="xalign">0.51999998092651367</property>
                <property name="yalign">0.49000000953674316</property>
                <signal name="clicked" handler="on_btn_edit_close_clicked" swapped="no"/>
                <accelerator key="q" signal="activate" modifiers="GDK_CONTROL_MASK"/>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="pack_type">end</property>
                <property name="position">2</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">4</property>
          </packing>
        </child>
      </object>
    </child>
  </object>
</interface>
)"""";
