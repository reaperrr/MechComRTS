Help for ShpEd Version 0.5
written and Copyright by
Fred Chlanda
June 1999

Introduction:
---------------------------------------
Disclaimer
This program is Freeware and may be freely distributed as long as it is not modified. The author makes no warranty as to the suitability of the program for its intended or any other purpose. Furthermore, the author is not responsible for any damage to your system nor is he liable for any other damages whatsoever that may be incurred by use of this program. In particular, the author does not encourage or condone the unauthorized distribution of copyrighted materials.
 
Features
SSI has published may games that use graphics that are stored in files with the shp extension. These include all the 5-star games except Allied General, Age of Rifles, Steel Panthers (SP) 1, 2 and 3 and Great Naval Battles. Unfortunately, no commonly available paint programs are able to work with the graphics format used in the shp files. ShpEd overcomes this difficulty by allowing the user to look inside a shp file to view the images stored there. Furthermore, it lets you export images in the ubiquitous Windows bmp format so that they can be modified. After modification, the bmp files can be reconverted by ShpEd to the shp format so that the original image can be replaced with the new one. Direct transfer of images between files, even files from different games, is also supported. Some of the SP  files contain special information that allows the icons to be centered and rotated. This information can also be added using a special function of ShpEd.

Installation
ShpEd is a 32-bit MicroSoft Windows (tm) program which will operate  under WIN95/98 and may also work with WIN 3.1 using the WIN32s extensions. It requires at least a 16 bpp (HiColor) video mode. Although 640x480 may work, at least 800x600 resolution is recommended. No special installation is required except to unzip the archive. It is recommended that you place ShpEd and it associated files in a separate directory. To use the shp to shp transfer function, the ShpEd directory will need two subdirectories  name "dest" and "source". A link to ShpEd can be installed on your desk top for easy drag and drop operation. You can also associate ShpEd with the shp extension so that a double click on a shp file in Explorer will start ShpEd.

Shp Files
Although it isn't necessary to understand the details of the shp file format to work with them, a little information may help you in using ShpEd. First of all, the shp format is based on a 256 color model. Each of the 256 colors is defined in a palette as a Red/Green/Blue combination able to take on values  0-63 (0-255 in the external palettes). Although some shp files include palette information as an integral part of the file, some do not. In any event, as far as I know, none of the games actually use the palette information in the shp file. Instead, there are one or more palettes defined somewhere in the game files. The bitmaps exported from ShpEd are in 24-bpp format (16million color) mode, so there are effectively an infinite number of colors available while you edit, but when the image is imported  into ShpEd for incorporation into the shp file, only the maximum 256 colors in the game palette are available. This can lead to some problems in color matching. Pacific General uses many palettes, some of which are very limited in their color range, so the problems with color matching can be very apparent. This is not a limitation of ShpEd but is inherent in the games themselves.

Shp files include a provision for transparency, i.e. portions of the image don't cover up the information already on the screen. Since bmp files do not include a transparent feature, a special bright pink color (RGB triple 255,225,225)  is used by ShpEd to represent transparent portions of the image. It is important in working on bitmaps with transparent areas that this color not be changed. Adding more transparent area to an image is best done by using the eyedropper function to copy the pink color from one area to another. Edited bmp files must be saved in 24-bpp mode. It is all that ShpEd can read.

The shp file itself starts with four bytes that are always "1.10". The next four bytes give the number of images in the file. This is followed by a table which lists the address where the information for each of the images starts and the address of the palette information for that image (remember, this is generally ignored). The information for each image begins with a header which is 24 bytes long and stores various parameters such as the image size. The header is followed by the actual image data.

Using ShpEd:
--------------------------------------------
Starting the Program
ShpEd can be started in any of the usual ways for a Windows program. If you install ShpEd as a desktop program or in as desktop icon you will be able to drag a file from Explorer and drop it on the ShpEd icon. ShpEd will startup with the dragged shp file already loaded. You can also associate ShpEd with the shp extension so that double clicking a file with the shp extension in Explorer will start ShpEd with that file loaded. ShpEd uses a configuration file (ShpEd.cfg) which is stored in ShpEd's home directory. The file will load the last used palette and window positions on startup. The first line of the ShpEd.cfg is a 1 by default. If you change it to 0, the information in the cfg file will be ignored. The second line is the main palette that will be loaded when ShpEd is started (if it is in the ShpEd directory). The 2nd line is the secondary palette (this is not currently loaded on startup). There follows Main, Bmp, Shp, SP Fix and Transfer window x,y positions. Once ShpEd appears you will see a sign on screen that can be removed by clicking on it or by waiting a few seconds.

Controls
All of ShpEd's actions are carried out by pressing one of the buttons on the small main window. The glyphs on the buttons are fairly descriptive of the actions which are performed by the buttons. Some of the buttons will be in an inactive state until their use is appropriate. 

Help. Pressing this button displays the Help file.

About ShpEd. Pressing this button displays the about box that gives the ShpEd version and copyright notice.

SP-No Flash. SP uses quite a few flashing colors to animate water and the like. The color numbers are 112-127 and 224-255 for those who wish to edit the palette file. Usually, you wouldn't want your tank to have a flashing turret. Use this checkbox to exclude the flashing colors when a bmp is converted to a shp image.

Save Collage. This button will give you an opportunity to save the currently displayed Collage as a Windows bmp file. This file should NOT be used for editing images that are going to later be converted to shp images. Use Save Bmp instead.

Load Shp File. Loads a shp file. When you load the file, it's name will appear on the Shp File Name line and some information about the structure of the file will appear in the Status Window.

Status Window. This area is used to display ShpEd messages about what is happening in ShpEd. Info about a shp file, problems with icons and the last image number displayed in a collage are reported here.

Stop. Interrupt the drawing of a single icon or collage. It may take a few seconds for the drawing to be stopped after you press the button.

Image. Set the currently selected image for viewing and replacement by using the up/down arrows or by typing in the box. (Note the first image in a shp file is #1 here).

View Image. Display the currently set Image # in the shp file.

View Collage. Starting with the current Image # display as many succeeding images in the shp file as will fit in the shp window.

Save Bmp. Use this button to save an image after it is displayed in the Windows bmp format. This function should be used to save an image for editing before reimmporting into ShpEd.

Load Bmp. Use this button to load a bmp format file into which will be converted to the shp format. 

Convert Bmp. Pressing this button will convert the presently loaded bitmap into the shp format so that it can be used for Replacing or Adding an image in the shp file. 

Replace Image. Pressing this button will Replace the currently selected Image # in the active shp file with the converted bitmap. The revised file will be called bignew.shp. If you wish, you may edit bignew.shp to make multiple changes. Once bignew.shp is loaded, it will not need to be reloaded for changes to show up.

Add Shp. The converted bitmap will be added to the end of the currently loaded shp file. The result will be called bignew.shp. Bignew.shp can be edited for making additional changes.

Load Palette. This button will let you load a palette file for displaying graphics from games other than Panzer General. 

Palette Name. The name of the file that has been loaded uing the Load Palette button. 

View Palette. Displays the colors in the current palette. The colors are displayed as small rectangles with color numbers increasing from left to right across a line. 

Header. Use Old Header. For Steel Panthers files, the header is non-standard. If this box is checked, ShpEd will not try to change the information. This is a good option if you are only trying to make small changes to the image. You can write a new header using the Fix Header button if you need to.

Fix Header. For Steel Panthers, the headers are more complicated than for most shp images. The function, described in detail elsewhere, will allow you to write a header to display images in the Iconxxxx files correctly. See SP Fix in the contents.

Transfer Shp. Pressing this button will bring up a window which can be used to transfer shp files directly from one file to another. See Shp Transfer for more information.

Basic Editing
In the simplest case, the steps to replace an image in a shp file (foo.shp) would be as follows:
1.  Use the Load Shp button to load foo.shp into ShpEd.
2.  If foo.shp does not use the Panzer General palette, load the appropriate palette using the Load Palette button.
3.  Type in or use the up/down arrows to adjust the image number to the value that you want to edit. (Use the View Collage button to preview several images to find the one you want first if you don't already know the number.)
4.  Press the View Shp button to display the image. 
5.  Press the Save Bmp button and save the image as a bmp file e.g. foo.bmp.
6.  Use a paint program to edit foo.bmp and save as foox.bmp.
7.  Use the Load Bmp button to load foox.bmp.
8.  Click the Convert Bmp to Shp button to convert the image to the shp format.
9.  Make sure that the correct shp file (foo.shp) is loaded and the desired Image # is selected. Press the Replace Image button. Doing this will make a copy of foo.shp that contains the revised image. The resulting file is always named "bignew.shp". To use this file, it will need to be copied to the game's shp directory and renamed (after removing the original shp file) to the proper name e.g. foo.shp.

The basic steps use the buttons at the top of the main ShpEd window in order from left to right (unless a palette needs to be loaded) so it should be easy to remember. Also remember that when you Replace an image in a file, the currently loaded file does not contain the revise image. If you want to see it, you will need to load bignew.shp. You may make additional changes to bignew.shp in which case it will not be necessary to reload the file.

SP Fix
In Steel Panthers 1,2 and 3 some icons have not been handled properly by early versions of ShpEd. This should be corrected now. New sized icons can be added and centered and displayed properly. To use this feature load the shp file  (iconxxx.shp). Select the image you want. Load the new bitmap. Make sure the Steel palette is loaded, the use full palette and old header checkboxes are checked. Convert the bmp to shp then insert the bmp into the shp file. Switch to editing Bignew.shp (just written). Select the proper image number. Click the SPFix button. Click the Show button on the Fix window. An enlarged version of your bitmap should appear with crosshairs on it. Move the crosshairs to the pixel that you want to be at the center of the hex when using SP. (Take a look at some of the unmodified files to get an idea where this should be.) Click the Write button which will write the new header to the currently loaded shp file (bignew.shp in this case). Follow the usual procedure of replacing the icon file in SP with bignew.shp. If you really know what you are doing,  you can edit the header information directly in the "New" edit boxes on the right side of the window. I do not recommend this, but the feature is there if you want it.

Shp Transfer
A powerful new feature was added to ShpEd 0.49. It is possible to transfer shp icons directly from one shp file to another without generating an intermediate bmp file. This will allow easy transfer of icons between different versions of Steel Panthers for example, importing one game's shp files into another and even the maintenance of a library of shp icons in shp format for users with large customization projects. If the two shp files use different palettes, both palettes can both be loaded and ShpEd will make the best conversion that it can. Because some of the transfers might involve many icons, a provision for exporting and importing a script has been included. 

To use the transfer feature, you will need to make two subdirectories in your ShpEd directory called "Source" and "Dest". Icons can be moved from shp files in the Source directory to shp files in the Dest directory. Sorry, these are the only locations that will work, but you REALLY should only work on backup files anyway. You can only make substitutions. Additions will need to be done in the old way. 

To activate the Transfer window, click the Transfer Shp button on the right side of the main ShpEd. A new window with a grid and several buttons will start. The grid is the area where you enter information that tells ShpEd how to move icons. There are five columns. The first is the description. This is just for your information. ShpEd does not use it. The next column is the name, without the shp extension, of the file to which the image will be moved. The third column is the icon number in the destination file that will be changed. Numbering in this case is DIFFERENT than what ShpEd uses in the main window. Images here are numbered with the first considered as 0, not 1. (I did this because the game programs themselves use this convention.) The fourth column is the name of the shp file containing the new icon and the last column is the number of the icon that will be moved. For example, if the fields were "test  icon0200  5  icon0201  7" then ShpEd will interpret this to mean move icon #7 (the eighth icon in the file) from the file icon0201.shp in the Source directory into the file icon0200.shp in the Dest directory replacing icon 5 (the sixth image) there.

To actually make the transfer, select a cell in the row and click the Transfer button. If you have entered several lines of instructions in the grid, you can select each line and then the Transfer button or you can mark the Auto Mode check box and then click the transfer button. In this case, all of the instructions will be carried out beginning at the first line and ending at the first line that does not have an entry in one of columns 2-5. Making a lot of changes can take some time, especially if it involves palette conversion. The progress can be followed by looking at the information displayed above the grid. Clicking the Save Script button will give you the opportunity to save the data in the grid in a Comma Separated Variable (csv) format compatible with most spreadsheets. A csv script, perhaps one that has been generated using a spreadsheet, can be loaded using the Load Script button. There is room for up to 100 entries in the table. If you find this too small, let me know.

Palette Conversion in Shp Transfers
Colors in shp files are stored as a single number 0-255. This is used as an index into a table called a palette that gives the amount of color of the three primary light colors (Red, Green, Blue) to be used in displaying the color on the screen. Different games use different palettes. Some games use more than one palette. To make the transfer of icons between different games, you will need to convert from one palette to another. To transfer an icon from Panzer General 1 to Panzer General 2, you will need to load the palette PG2.pal into the main ShpEd window and use Load Pal on the Transfer window to load the PG.pal. The 2nd palette refers to the palette that will be used for the Source files. After the second palette is loaded check the Use 2 Palettes box. ShpEd will convert the color numbers as it makes the transfer. Because the colors contained in different games are not exactly the same you might see some color shifts when you make the transfers. These should not be too bad in most cases. Some of the Steel Panthers shp images (specifically the ones in the iconxxxx.shp and terxxxx.shp files) have a format that is different than most other shp files. If you transfer images from other games to these slots you will need to use the Fix SP function. (This has not been tested.)

Palettes Supplied with Shpd
Age of Rifles - AOR.pal
Pacific General - PacGen.pal, Pag_day.pal, Pag_main.pal, Pag_mnu2.pal, Pag_tn1j.pal through Pag_tn6j.pal (between turn Japanese pictures), Pag_tn1 through tn6u.pal (between turn American pictures)

Panzer General - PG.pal, PG_new,pal, (also default ShpEd palette)

Panzer General 2 - pg2.pal,PG2Map.pal

Steel Panthers - Steel.pal

Fantasy General - fg.pal

Star General - sg.pal

Palettes used by ShpEd are in the ascii format used by PaintShop Pro. If you need a palette for a game other than those above you will probably find it in a file with the lbm extension and you can get it by loading that file into PSP and saving the palette.

Miscellaneous
-------------------------------------------
Acknowledgments
This program was prompted by my association with the Panzer General DOS Research Center, Panos Stoucas, Director. I wish to thank all of the associates of the PG-DOSRC for their encouragement, especially Paul Bond and Steve Farrell for their alpha testing. The Steel Panthers enhancements were developed with the encouragement and extensive testing of Don Goodbrand.

About the Author
Please send comments and bug reports to me at chlanda@hotmail.com. I will try to respond to your message and will take your comments into consideration in any future releases of this program. You can check for updates to ShpEd and other programs that I have written on my web page: pages.prodigy.net/chlanda. 

I was bitten by the computer bug about 20 years ago. My first computer was a TRS-80 Model I with 4k of memory. It was wonderful! Gradually that system expanded to 48k and 2 disk drives. While I used the TRS-80, I programmed in BASIC and Z80 assembly language. When I got my first PC compatible sometime in the mid 80's I switched to Borland's Turbo Pascal. Since then, on increasingly more complex systems, I have continued to use Borland products going from Pascal to C to (briefly) Delphi and now C++Builder. This is a very powerful tool and generates Windows code with a minimal effort. Excellent!

My gaming interests are mainly in RPG and Strategy/War games. I guess I own more games from SSI than anyone else. I have never been able to decide whether it is more fun to play the games or investigate the inner workings of the programs and data files. When copy protection was made obsolete by the sheer size and CDROM nature of most games, I lost one of my favorite pastimes. Usually my first project was to get rid of the many annoying copy protection schemes. Oh well, there are still cheats and editors to be developed.

Pacific General is a war game with some promise. The built in scenario editor is great, but the lack of original maps severely limits the usefulness of the editor. I thought that the game might be more popular among wargamers if it did not have this limitation. Anyway, I decided to write a map editor to generate new maps. I wanted to access the map tiles for Pacific General, and ran across a bunch of shp files in some huge data collections. Looking back at Panzer General, I saw the same type of files. After a few days of "I know what it looks like but what the hell do those numbers mean" I gradually figured out most of the ins and outs of unpacking the files so that I could proceed with my map editor, PacMap. I was amazed to hear that shp files were considered mysterious and that quite a few people really wanted an editor. 

Besides Shp Ed and PacMap I have released an editor for Jagged Alliance: Deadly Games (DGED) and a quest item locator for Daggerfall (DDFQL). I have also written a scenario/save game editor (SP23Ed) for Steel Panthers 2&3 that offers more features and ease of use than the built-in editors. Another of my programs, FPGE is  a scenario editor for Panzer General that runs in good old DOS and directly displays the shp images.

Fred Chlanda
chlanda@hotmail.com
June 1999
