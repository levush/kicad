/**
 * @file menubarpcb.cpp
 * PCBNew editor menu bar
 */
#include "fctsys.h"
#include "appl_wxstruct.h"
#include "common.h"
#include "pcbnew.h"
#include "wxPcbStruct.h"
#include "bitmaps.h"
#include "protos.h"
#include "hotkeys.h"
#include "pcbnew_id.h"

/**
 * PCBNew mainframe menubar
 */
void
WinEDA_PcbFrame::ReCreateMenuBar()
{
    wxString    text;
    wxMenuItem* item;
    wxMenuBar*  menuBar = GetMenuBar();

   /**
    * Destroy the existing menu bar so it can be rebuilt.  This allows
    * language changes of the menu text on the fly.
    */
    if( menuBar )
        SetMenuBar( NULL );
    menuBar = new wxMenuBar();



   /**
    * File Menu
    */
    wxMenu* filesMenu = new wxMenu;

    /* New Board */
    item = new wxMenuItem( filesMenu, ID_NEW_BOARD, _( "&New" ),
                           _( "Clear current board and initialize a new one" ));
    item->SetBitmap( new_xpm );
    filesMenu->Append( item );

    /* Load Board */
    item = new wxMenuItem( filesMenu, ID_LOAD_FILE, _( "&Open" ),
                           _( "Delete current board and load new board" ) );
    item->SetBitmap( open_xpm );
    filesMenu->Append( item );

    /* Load Recent submenu */
    wxMenu* openRecentMenu = new wxMenu();
    wxGetApp().m_fileHistory.AddFilesToMenu( openRecentMenu );
    filesMenu->AppendSubMenu( openRecentMenu, _( "Open &Recent" ),
                              _("Open a recent opened document"));

    /* Save */
    item = new wxMenuItem( filesMenu, ID_SAVE_BOARD,
                           _( "&Save" ),
                           _( "Save current board" ) );
    item->SetBitmap( save_xpm );
    filesMenu->Append( item );

    /* Save As */
    item = new wxMenuItem( filesMenu, ID_SAVE_BOARD_AS,
                           _( "Save as..." ),
                           _( "Save the current board as.." ) );
    item->SetBitmap( save_as_xpm );
    filesMenu->Append( item );

    /* Separator */
    filesMenu->AppendSeparator();

    /* Rescue */
    item = new wxMenuItem( filesMenu, ID_MENU_RECOVER_BOARD, _( "&Rescue" ),
                           _( "Clear old board and get last rescue file" ) );
    item->SetBitmap( hammer_xpm );
    filesMenu->Append( item );

    /* Revert */
    item = new wxMenuItem( filesMenu, ID_MENU_READ_LAST_SAVED_VERSION_BOARD,
                           _( "&Revert" ),
                           _( "Clear old board and get old version of board" ) );
    item->SetBitmap( jigsaw_xpm );
    filesMenu->Append( item );

    /* Separator */
    filesMenu->AppendSeparator();



    /* Fabrication Outputs submenu */
    wxMenu* fabricationOutputsMenu = new wxMenu;
    item = new wxMenuItem( fabricationOutputsMenu, ID_PCB_GEN_POS_MODULES_FILE,
                           _( "&Modules Position" ),
                           _( "Generate modules position file for pick and place" ) );
    item->SetBitmap( post_compo_xpm );
    fabricationOutputsMenu->Append( item );

    item = new wxMenuItem( fabricationOutputsMenu, ID_PCB_GEN_DRILL_FILE,
                           _( "&Drill File" ),
                           _( "Generate excellon2 drill file" ) );
    item->SetBitmap( post_drill_xpm );
    fabricationOutputsMenu->Append( item );

    /* Component File */
    item = new wxMenuItem( fabricationOutputsMenu, ID_PCB_GEN_CMP_FILE,
                           _( "&Component File" ),
                           _( "(Re)create components file for CvPcb" ) );
    item->SetBitmap( save_cmpstuff_xpm );
    fabricationOutputsMenu->Append( item );

    /* BOM File */
    item = new wxMenuItem( fabricationOutputsMenu, ID_PCB_GEN_BOM_FILE_FROM_BOARD,
                _( "&BOM File" ),
                _( "(Re)create bill of materials file for CvPCB" ) );
    item->SetBitmap( tools_xpm );
    fabricationOutputsMenu->Append( item );

    /* Fabrications Outputs submenu append */
    filesMenu->AppendSubMenu( fabricationOutputsMenu,
                              _( "Fabrication Outputs "),
                   _( "Generate files for fabrication" ) );

    /* Import submenu */
    wxMenu* submenuImport = new wxMenu();

    /* PCBNew Board */
    item = new wxMenuItem( submenuImport, ID_APPEND_FILE, _( "PCBNew Board" ),
              _( "Append a other PCBNew board to the current loaded board" ) );
    item->SetBitmap( pcbnew_xpm );
    submenuImport->Append( item );

    /* Specctra Session */
    item = new wxMenuItem( submenuImport, ID_GEN_IMPORT_SPECCTRA_SESSION,
                           _( "&Specctra Session" ),
                           _( "Import a routed \"Specctra Session\" (*.ses) file" ) );
    item->SetBitmap( import_xpm );    // @todo need better bitmap
    submenuImport->Append( item );

   /** 
    * would be implemented in WinEDA_PcbFrame::ImportSpecctraDesign() in
    * specctra_import.cpp
    *  item = new wxMenuItem(submenuImport, ID_GEN_IMPORT_SPECCTRA_DESIGN,
    *  _("&Specctra Design"), _("Import a \"Specctra Design\" (*.dsn) file") );
    *  item->SetBitmap(export_xpm);    // @todo need better bitmap
    *  submenuImport->Append(item);
    */

    ADD_MENUITEM_WITH_HELP_AND_SUBMENU( filesMenu, submenuImport,
                                        ID_GEN_IMPORT_FILE, _( "Import" ),
                                        _( "Import files" ), import_xpm );



    /* Export submenu */
    wxMenu* submenuexport = new wxMenu();

    /* Specctra DSN */
    item = new wxMenuItem( submenuexport, ID_GEN_EXPORT_SPECCTRA,
                           _( "&Specctra DSN" ),
                           _( "Export the current board to a \"Specctra DSN\" file" ) );
    item->SetBitmap( export_xpm );
    submenuexport->Append( item );

    /* Export GenCAD Format */
    item = new wxMenuItem( submenuexport, ID_GEN_EXPORT_FILE_GENCADFORMAT,
                           _( "&GenCAD" ), _( "Export GenCAD Format" ) );
    item->SetBitmap( export_xpm );
    submenuexport->Append( item );

    /* Module Report */
    item = new wxMenuItem( submenuexport, ID_GEN_EXPORT_FILE_MODULE_REPORT,
                           _( "&Module Report" ),
                           _( "Create a report of all modules on the current board" ) );
    item->SetBitmap( tools_xpm );
    submenuexport->Append( item );
    ADD_MENUITEM_WITH_HELP_AND_SUBMENU( filesMenu, submenuexport,
                                        ID_GEN_EXPORT_FILE, _( "&Export" ),
                                        _( "Export board" ), export_xpm );

    /* Separator */
    filesMenu->AppendSeparator();

    /* Print */
    item = new wxMenuItem( filesMenu, ID_GEN_PRINT, _( "P&rint" ),
                           _( "Print pcb board" ) );
    item->SetBitmap( print_button );
    filesMenu->Append( item );

    /* Print SVG */
    item = new wxMenuItem( filesMenu, ID_GEN_PLOT_SVG, _( "Print S&VG" ),
                           _( "Plot board in Scalable Vector Graphics format" ) );
    item->SetBitmap( print_button );
    filesMenu->Append( item );

    /* Plot */
    item = new wxMenuItem( filesMenu, ID_GEN_PLOT, _( "&Plot" ),
                           _( "Plot board in HPGL, PostScript or Gerber RS-274X format)" ) );
    item->SetBitmap( plot_xpm );
    filesMenu->Append( item );

    /* Archive Footprints */
    filesMenu->AppendSeparator();
    wxMenu* submenuarchive = new wxMenu();
    item = new wxMenuItem( submenuarchive, ID_MENU_ARCHIVE_NEW_MODULES,
                           _( "Add New Footprints" ),
                           _( "Archive new footprints only in a library (keep other footprints in this lib)" ) );
    item->SetBitmap( library_update_xpm );
    submenuarchive->Append( item );
    item = new wxMenuItem( submenuarchive, ID_MENU_ARCHIVE_ALL_MODULES,
                           _( "Create Footprint Archive" ),
                           _( "Archive all footprints  in a library(old lib will be deleted)" ) );
    item->SetBitmap( library_xpm );
    submenuarchive->Append( item );
    ADD_MENUITEM_WITH_HELP_AND_SUBMENU( filesMenu, submenuarchive,
                                        ID_MENU_ARCHIVE_MODULES,
                                        _( "Archive Footprints" ),
                                        _( "Archive or add footprints in a library file" ),
                                        library_xpm );

    /* Exit */
    filesMenu->AppendSeparator();
    item = new wxMenuItem( filesMenu, ID_EXIT, _( "&Quit" ),
                           _( "Quit PCBNew" ) );
    item->SetBitmap( exit_xpm );
    filesMenu->Append( item );



   /**
    * Edit menu
    */
    wxMenu* editMenu = new wxMenu;

    /* Undo */
    /* TODO add Undo hotkey */
    item = new wxMenuItem( editMenu, ID_UNDO_BUTT, _( "Undo"),
                           _( "Undo last edition" ), wxITEM_NORMAL );
    item->SetBitmap( undo_xpm );
    editMenu->Append( item );

    /* Redo */
    /* TODO add Redo hotkey */
    item = new wxMenuItem( editMenu, ID_REDO_BUTT, _( "Redo" ),
                           _( "Redo the last undo command" ), wxITEM_NORMAL );
    item->SetBitmap( redo_xpm );
    editMenu->Append( item );

    /* Separator */
    editMenu->AppendSeparator();

    /* Find */
    text  = AddHotkeyName( _( "&Find..." ), s_Pcbnew_Editor_Hokeys_Descr, HK_FIND_ITEM);
    item = new wxMenuItem( editMenu, ID_FIND_ITEMS, text,
                           _("Find components and text in current loaded board") );
    editMenu->Append( item );

    /* Separator */
    editMenu->AppendSeparator();

    /* Global Deletions */
    item = new wxMenuItem( editMenu, ID_PCB_GLOBAL_DELETE,
                           _( "Global &Deletions" ),
                           _( "Delete tracks, modules, texts... on board" ) );
    item->SetBitmap( general_deletions_xpm );
    editMenu->Append( item );

    /* Tracks */
    item = new wxMenuItem( editMenu, ID_MENU_PCB_CLEAN,
           _( "&Tracks" ),
           _( "Clean stubs, vias, delete break points, or connect dangling tracks to pads and vias" ) );
    item->SetBitmap( delete_body_xpm );
    editMenu->Append( item );

    /* Swap Layers */
    item = new wxMenuItem( editMenu, ID_MENU_PCB_SWAP_LAYERS,
           _( "&Swap Layers" ),
           _( "Swap tracks on copper layers or drawings on others layers" ) );
    item->SetBitmap( swap_layer_xpm );
    editMenu->Append( item );



    /**
     * View menu
     */
    wxMenu* viewMenu = new wxMenu;

    /* Zoom in */
    text  = AddHotkeyName( _( "Zoom in" ), s_Pcbnew_Editor_Hokeys_Descr, HK_ZOOM_IN);
    item = new wxMenuItem( viewMenu, ID_ZOOM_IN, text, _( "Zoom in" ),
                           wxITEM_NORMAL );
    item->SetBitmap( zoom_in_xpm );
    viewMenu->Append( item );

    /* Zoom out */
    text = AddHotkeyName( _( "Zoom out" ), s_Pcbnew_Editor_Hokeys_Descr,
                         HK_ZOOM_OUT );
    item = new wxMenuItem( viewMenu, ID_ZOOM_OUT, text, _( "Zoom out" ),
                           wxITEM_NORMAL );
    item->SetBitmap( zoom_out_xpm );
    viewMenu->Append( item );

    /* Zoom auto */
    text = AddHotkeyName( _( "Zoom auto" ), s_Pcbnew_Editor_Hokeys_Descr,
                         HK_ZOOM_AUTO );
    item = new wxMenuItem( viewMenu, ID_ZOOM_PAGE, text, _( "Zoom auto" ),
                           wxITEM_NORMAL );
    item->SetBitmap( zoom_auto_xpm );
    viewMenu->Append( item );

    viewMenu->AppendSeparator();

    /* Redraw view */
    text = AddHotkeyName( _( "Redraw view" ), s_Pcbnew_Editor_Hokeys_Descr,
                         HK_ZOOM_REDRAW );
    item = new wxMenuItem( viewMenu, ID_ZOOM_REDRAW, text, _( "Zoom auto" ),
                           wxITEM_NORMAL );
    item->SetBitmap( zoom_redraw_xpm );
    viewMenu->Append( item );

    /* Separator */
    viewMenu->AppendSeparator();

    /* List of Nets */
    item = new wxMenuItem( viewMenu, ID_MENU_LIST_NETS, _( "&List Nets" ),
                        _( "View a list of nets with names and id's" ) );
    item->SetBitmap( tools_xpm );
    viewMenu->Append( item );


    /* 3D Display */
    item = new wxMenuItem( viewMenu, ID_MENU_PCB_SHOW_3D_FRAME,
                       _( "3D Display" ), _( "Show board in the 3D viewer" ) );
    item->SetBitmap( show_3d_xpm );
    viewMenu->Append( item );



   /**
    * Preferences and configuration
    */
    wxMenu* configmenu = new wxMenu;

    /* Library */
    item = new wxMenuItem( configmenu, ID_CONFIG_REQ, _( "&Library" ),
                           _( "Setting libraries, directories and others..." ) );
    item->SetBitmap( library_xpm );
    configmenu->Append( item );

    /* Colors and Visibility */
    item = new wxMenuItem( configmenu, ID_COLORS_SETUP,
                           _( "&Colors and Visibility" ),
                           _( "Select colors and visibility of layers and some items" ) );
    item->SetBitmap( palette_xpm );
    configmenu->Append( item );

    /* General */
    item = new wxMenuItem( configmenu, ID_OPTIONS_SETUP, _( "&General" ),
                           _( "Select general options for PCBnew" ) );
    item->SetBitmap( preference_xpm );
    configmenu->Append( item );

    /* Display */
    item = new wxMenuItem( configmenu, ID_PCB_DISPLAY_OPTIONS_SETUP,
                           _( "&Display" ),
                           _( "Select how items (pads, tracks texts ... ) are displayed" ) );
    item->SetBitmap( display_options_xpm );
    configmenu->Append( item );

    /* Dimensions submenu */
    wxMenu* dimensionsMenu = new wxMenu;

    /* Grid */
    item = new wxMenuItem( dimensionsMenu, ID_PCB_USER_GRID_SETUP, _( "Grid" ),
                           _( "Adjust user grid dimensions" ) );
    item->SetBitmap( grid_xpm );
    dimensionsMenu->Append( item );

    /* Text and Drawings */
    item = new wxMenuItem( dimensionsMenu, ID_PCB_DRAWINGS_WIDTHS_SETUP,
                           _( "Texts and Drawings" ),
                           _( "Adjust dimensions for texts and drawings" ) );
    item->SetBitmap( options_text_xpm );
    dimensionsMenu->Append( item );

    /* Pads */
    item = new wxMenuItem( dimensionsMenu, ID_PCB_PAD_SETUP, _( "Pads" ),
                           _( "Adjust pads shape, dimensions, layers" ) );
    item->SetBitmap( pad_xpm );
    dimensionsMenu->Append( item );

    /* Pads Mask Clearance */ 
    item = new wxMenuItem( dimensionsMenu, ID_PCB_MASK_CLEARANCE,
                           _( "Pads Mask Clearance" ),
                           _( "Adjust the global clearance between pads and the solder resist mask" ) );
    item->SetBitmap( pad_xpm );
    dimensionsMenu->Append( item );


    /* Save */
    dimensionsMenu->AppendSeparator();
    item = new wxMenuItem( dimensionsMenu, ID_CONFIG_SAVE, _( "&Save" ),
                           _( "Save dimension preferences" ) );
    item->SetBitmap( save_xpm );
    dimensionsMenu->Append( item );
    configmenu->AppendSubMenu( dimensionsMenu, _( "Di&mensions" ),
                               _( "Global dimensions preferences" ));

    /* Language submenu */
    wxGetApp().AddMenuLanguageList( configmenu );

    /* Hotkey submenu */
    AddHotkeyConfigMenu( configmenu );

    /* Separator */
    configmenu->AppendSeparator();

    /* Save Preferences */
    item = new wxMenuItem( configmenu, ID_CONFIG_SAVE, _( "&Save Preferences" ),
                           _( "Save application preferences" ) );
    item->SetBitmap( save_setup_xpm );
    configmenu->Append( item );

    /* Read Preferences */
    item = new wxMenuItem( configmenu, ID_CONFIG_READ, _( "&Read Preferences" ),
                           _( "Read application preferences" ) );
    item->SetBitmap( read_setup_xpm );
    configmenu->Append( item );



   /**
    * Design Rules menu
    */ 
    wxMenu* designRulesMenu = new wxMenu;

    /* Design Rules */
    item = new wxMenuItem( designRulesMenu, ID_MENU_PCB_SHOW_DESIGN_RULES_DIALOG,
                           _( "Design Rules" ),
                           _( "Open the design rules dialog editor" ) );
    item->SetBitmap( hammer_xpm );
    designRulesMenu->Append( item );

    /* Layers Setup */
    item = new wxMenuItem( configmenu, ID_PCB_LAYERS_SETUP, _( "&Layers Setup" ),
                           _( "Enable and set properties of layers" ) );
    item->SetBitmap( copper_layers_setup_xpm );
    designRulesMenu->Append( item );



    /**
     * Help menu
     */
    wxMenu* helpMenu = new wxMenu;
    item = new wxMenuItem( helpMenu, ID_GENERAL_HELP, _( "&Contents" ),
                           _( "Open the PCBnew manual" ) );
    item->SetBitmap( help_xpm );
    helpMenu->Append( item );

    item = new wxMenuItem( helpMenu, ID_KICAD_ABOUT, _( "&About" ),
                           _( "About PCBnew printed circuit board designer" ) );
    item->SetBitmap( info_xpm );
    helpMenu->Append( item );



    /**
     * Append all menus to the menuBar
     */
    menuBar->Append( filesMenu, _( "&File" ) );
    menuBar->Append( editMenu, _( "&Edit") );
    menuBar->Append( viewMenu, _( "&View" ) );
    menuBar->Append( configmenu, _( "&Preferences" ) );
    menuBar->Append( designRulesMenu, _( "&Design Rules" ) );
    menuBar->Append( helpMenu, _( "&Help" ) );

    /* Associate the menu bar with the frame */
    SetMenuBar( menuBar );
}

