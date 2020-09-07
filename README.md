# mapter

## Update information

* v0.5.3 - Small change to "save" logic
* v0.5.2 - Small layout changes & word count statistics
* v0.5.1 - Urgent bug fix
* v0.5 - Tree control for notes tab
* v0.4 - Addition of cell background selector

## Introduction

mapter is a free tool to assist with planning a piece of writing using [the book architecture method](http://www.betternovelproject.com/blog/series-outline/). _There's an alternative description [here](https://thefriendlyeditor.com/tag/the-book-architecture-method/)_

There are many, many writing tools already available but very few that support this sort of grid approach. Of the ones that I found they all had some drawbacks:

* Not available for Linux, e.g. [Scrivener](https://www.literatureandlatte.com/scrivener/overview)
* Had lots of features that I didn't want, e.g. [bibisco](https://www.bibisco.com/)
* Online only or use web technologies which I didn't want, e.g. [Wavemaker](https://wavemaker.co.uk)

It is not my intention to add word processing features like text markup, spell checking, grammar checking etc. This is designed as a no-distractions planning and writing tool. However tools like [Markdown](https://en.wikipedia.org/wiki/Markdown) or [LaTeX](https://www.latex-project.org/) could be used to format and typeset the export if necessary.

_( The name comes from a portmanteau of "mapping" and "chapter" and was created using an [online name generator](https://namelix.com/) )_

## Current Status

The current version ( 0.5.4 ) could generously be called a minimum viable product ( MVP ) and allows the creation and editing of a full work. The main limitation is that the editor is extremely basic and lacks common features like "search/replace".

## Building

mapter uses the [GTK+ 3 library](https://www.gtk.org/) and can be built by simply typing `make` in the top level directory. Note that the build files and general structure follow that suggested in the rather good set of tutorials at https://prognotes.net/gtk-glade-c-programming/. That page also provides some useful hints as to which GTK related packages are needed for the build to succeed.

The GUI definition is done largely using [Glade](https://glade.gnome.org/) but some parts are built dynamically within the code.

It's possible to show some debugging information by setting the GTK debug level:

`G_MESSAGES_DEBUG=all ./mapter`

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
1. The currently selected cell is shown with a highlight. The selection can be moved with the arrow keys or by clicking with the mouse. ( "Home", "End", shift up-arrow and shift down-arrow also work ). Hitting Return will bring up the editor for the selected cell.
1. The "Chapter" and "Series" of the selected cell are shown at the bottom. This makes navigation easier when the row and column headers are scrolled off the screen.
1. The background colour of each cell can be changed by right clicking on the cell and selecting the colour.  Currently the options are:
    * Clear - no background
    * High - red background
    * Medium - yellow background
    * Low - green background
    * Neutral - blue background


#### Notes tab

The notes tab is a simple free format text window with a hierarchical tree control. The tree structure can be edited by dragging the elements and by the buttons at the bottom. Text is saved automatically when the tree view changes.

![Notes Tab](/doc-images/main-notes.png)

### Edit Window

Double clicking on any of the cells or pressing Return on the highlighted cell brings up the edit window:

![Edit Window](/doc-images/edit.png)

This has three sections:

1. Text that appears on the front grid
1. Header text for that section in the document export
1. Body text for that section in the document export

### Changing the size of the grid

__Important note: at the moment there is no confirmation of any changes and no undo.__

Right clicking on any of the cells shows a popup menu with insert/delete commands which can be used to change the size of the grid.

### File Loading and Saving

The usual file open, save, save as, new commands can be found under the "File" menu.

### File Export

File export is similar to save but exports the data in a more structured way. There are some export options:

![Edit Window](/doc-images/export.png)

Some tools use two consecutive carriage returns as a paragraph marker. However it's sometimes more convenient and a nicer layout in the mapter section editor to write text using just one carriage return. The first option adds an extra carriage return into the export.

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

The included Markdown and LaTeX examples give an idea as to how the output may be typeset. The LaTeX example can be built using the following commands:

````
Export the document from mapter with a .tex extension
pdflatex export.tex
pdflatex export.tex
````
_Run the second command twice to create the table of contents properly_

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

* Improved Editor with features like search/replace and undo. At the moment the [GTKSourceView](https://gitlab.gnome.org/GNOME/gtksourceview) component looks a likely candidate.
* A method of moving or swapping the contents of cells without a lot of cutting & pasting
