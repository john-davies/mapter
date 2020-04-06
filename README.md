# mapter

## Introduction

mapter is a free tool to assist with planning a piece of writing using [the book architecture method](http://www.betternovelproject.com/blog/series-outline/). _There's an alternative description [here](https://thefriendlyeditor.com/tag/the-book-architecture-method/)_

There are many, many writing tools already available but very few that support this sort of grid approach. Of the ones that I found they all had some drawbacks:

* Not available for Linux, e.g. [Scrivener](https://www.literatureandlatte.com/scrivener/overview)
* Had lots of features that I didn't want, e.g. [bibisco](https://www.bibisco.com/)
* Online only or use web technologies which I didn't want, e.g. [Wavemaker](https://wavemaker.co.uk)

It is not my intention to add word processing features like text markup, spell checking, grammar checking etc. This is designed as a no-distractions planning and writing tool. However tools like [Markdown](https://en.wikipedia.org/wiki/Markdown) or [LaTeX](https://www.latex-project.org/) could be used to format and typeset the export if necessary.

_( The name comes from a portmanteau of "mapping" and "chapter" and was created using an [online name generator](https://namelix.com/) )_

## Current Status

This is an initial alpha version with limited functionality:

* Create a grid and add headings
* Edit the size of the grid
* Add some general notes
* Load, save and export the created designs

Currently the Glade file defining the GUI is loaded from the hard coded path `glade/window_main.glade`. In future it is my intention to include this definition into the build to make just a single executable.

## Building

mapter uses the [GTK+ 3 library](https://www.gtk.org/) and can be built by simply typing `make` in the top level directory. Note that the build files and general structure follow that suggested in the rather good set of tutorials at https://prognotes.net/gtk-glade-c-programming/. That page also provides some useful hints as to which GTK related packages are needed for the build to succeed.

The GUI definition is done largely using [Glade](https://glade.gnome.org/) but some parts are built dynamically within the code.

## Operation

_Note that the screenshots use the `ww1-1916.mapter` file from the `examples` directory._

### Command line options

### Main Window

#### Grid tab

The grid tab has four main sections as described below. Double click on any of the cells to edit.

![Grid Tab](/doc-images/main-grid.png)

1. The cell at 0,0 doesn't really form part of the grid but is used here to store an optional title for the work ( see Export below ).
1. The column headings are used to describe the series or themes that flow through the work.
1. The row headings are used to define the chapter headings
1. The rest of the grid is for each of the sections mapping the theme/series to the chapter.

_For the export it is possible to swap the order such that the column headings are the chapter titles etc. see below_

#### Notes tab

The notes tab is a simple free format text window.

![Notes Tab](/doc-images/main-notes.png)

### Edit Window

Double clicking on any of the cells brings up the edit window:

![Edit Window](/doc-images/edit.png)

### Changing the size of the grid

__Important note: at the moment there is no confirmation of any changes and no undo.__

Right clicking on any of the cells shows a popup menu with insert/delete commands which can be used to change the size of the grid.

### File Loading and Saving

The usual file open, save, save as, new commands can be found under the "File" menu.

### File Export

File export is similar to save but exports the data in a more structured way. There are some export options:

![Edit Window](/doc-images/export.png)

The last option specifies whether extra data is added to each line, e.g.

unticked:

````
February
  The battle of Verdun begins
  Trebizond Campaign.
  Battle of Salaita Hill.
````

ticked:

````
February
  Western Front - The battle of Verdun begins
  Caucasian Front - Trebizond Campaign.
  African Theatre - Battle of Salaita Hill.
````

### File formats

#### mapter File

The `.mapter` file is a JSON file whose structure is pretty self-explanatory.

#### Export file

The export file is a simple text format.

### Debugging

Trace and debugging information can be show on the standard output by using the following command line:

`G_MESSAGES_DEBUG=all ./mapter`

## Future Developments

Future planned developments include:

* "Freeze Panes" type functionality for 1st row/column to make navigation of large projects a little clearer
* Full Editor to allow editing of titles and body text of each section so that the entire book can be edited from within mapter.
* Status indication ( or %age completion ) for each cell
* A method of moving or swapping the contents of cells without a lot of cutting & pasting
* Tree control for the notes tab so that information can be collated hierarchically