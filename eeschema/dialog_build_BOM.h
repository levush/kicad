/////////////////////////////////////////////////////////////////////////////
// Name:        dialog_build_BOM.h
// Purpose:
// Author:      jean-pieere Charras
// Modified by:
// Created:     01/15/06 18:18:44
// RCS-ID:
// Copyright:   GNU license
// Licence:
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), 01/15/06 18:18:44

#ifndef _DIALOG_BUILD_BOM_H_
#define _DIALOG_BUILD_BOM_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "dialog_build_BOM.cpp"
#endif

/*!
 * Includes
 */

////@begin includes
#include "wx/valgen.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_DIALOG 10000
#define ID_CHECKBOX1 10001
#define ID_CHECKBOX2 10002
#define ID_CHECKBOX3 10003
#define ID_CHECKBOX4 10004
#define ID_CHECKBOX5 10005
#define ID_RADIOBOX_SELECT_FORMAT 10006
#define ID_RADIOBOX_SEPARATOR 10007
#define ID_CHECKBOX6 10008
#define ID_CHECKBOX_FOOTPRINT_FIELD 10018
#define ID_CHECKBOX_FIELD1 10009
#define ID_CHECKBOX_FIELD2 10010
#define ID_CHECKBOX_FIELD3 10011
#define ID_CHECKBOX_FIELD4 10012
#define ID_CHECKBOX_FIELD5 10013
#define ID_CHECKBOX_FIELD6 10014
#define ID_CHECKBOX_FIELD7 10015
#define ID_CHECKBOX_FIELD8 10016
#define ID_CREATE_LIST 10017
#define SYMBOL_WINEDA_BUILD_BOM_FRAME_STYLE wxDEFAULT_DIALOG_STYLE|wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|MAYBE_RESIZE_BORDER
#define SYMBOL_WINEDA_BUILD_BOM_FRAME_TITLE _("List of Material")
#define SYMBOL_WINEDA_BUILD_BOM_FRAME_IDNAME ID_DIALOG
#define SYMBOL_WINEDA_BUILD_BOM_FRAME_SIZE wxSize(400, 300)
#define SYMBOL_WINEDA_BUILD_BOM_FRAME_POSITION wxDefaultPosition
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif

/*!
 * WinEDA_Build_BOM_Frame class declaration
 */

class WinEDA_Build_BOM_Frame: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( WinEDA_Build_BOM_Frame )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    WinEDA_Build_BOM_Frame( );
    WinEDA_Build_BOM_Frame( WinEDA_DrawFrame* parent,
            wxWindowID id = SYMBOL_WINEDA_BUILD_BOM_FRAME_IDNAME,
            const wxString& caption = SYMBOL_WINEDA_BUILD_BOM_FRAME_TITLE,
            const wxPoint& pos = SYMBOL_WINEDA_BUILD_BOM_FRAME_POSITION,
            const wxSize& size = SYMBOL_WINEDA_BUILD_BOM_FRAME_SIZE,
            long style = SYMBOL_WINEDA_BUILD_BOM_FRAME_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_WINEDA_BUILD_BOM_FRAME_IDNAME, const wxString& caption = SYMBOL_WINEDA_BUILD_BOM_FRAME_TITLE, const wxPoint& pos = SYMBOL_WINEDA_BUILD_BOM_FRAME_POSITION, const wxSize& size = SYMBOL_WINEDA_BUILD_BOM_FRAME_SIZE, long style = SYMBOL_WINEDA_BUILD_BOM_FRAME_STYLE );

    /// Creates the controls and sizers
    void CreateControls();

////@begin WinEDA_Build_BOM_Frame event handler declarations

    /// wxEVT_COMMAND_RADIOBOX_SELECTED event handler for ID_RADIOBOX_SELECT_FORMAT
    void OnRadioboxSelectFormatSelected( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_CREATE_LIST
    void OnCreateListClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
    void OnOkClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL
    void OnCancelClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_APPLY
    void OnApplyClick( wxCommandEvent& event );

////@end WinEDA_Build_BOM_Frame event handler declarations

////@begin WinEDA_Build_BOM_Frame member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end WinEDA_Build_BOM_Frame member function declarations

    void Create_BOM_Lists(bool aTypeFileIsExport,
                          bool aIncludeSubComponents,
                          char aExportSeparatorSymbol,
                          bool aRunBrowser);
    void GenereListeOfItems(const wxString & FullFileName, bool aIncludeSubComponents );
    void CreateExportList(const wxString & FullFileName, bool aIncludeSubComponents);
    int PrintComponentsListByRef( FILE * f, ListComponent * List, int NbItems,
                            bool CompactForm, bool aIncludeSubComponents );
    int PrintComponentsListByVal( FILE *f, ListComponent * List, int NbItems,
                            bool aIncludeSubComponents);
    void PrintFieldData(FILE * f, SCH_COMPONENT * DrawLibItem, bool CompactForm = FALSE);
    void SavePreferences();


    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin WinEDA_Build_BOM_Frame member variables
    wxCheckBox* m_ListCmpbyRefItems;
    wxCheckBox* m_ListSubCmpItems;
    wxCheckBox* m_ListCmpbyValItems;
    wxCheckBox* m_GenListLabelsbyVal;
    wxCheckBox* m_GenListLabelsbySheet;
    wxRadioBox* m_OutputFormCtrl;
    wxRadioBox* m_OutputSeparatorCtrl;
    wxCheckBox* m_GetListBrowser;
    wxStaticBoxSizer* m_FieldsToAppendListSizer;
    wxCheckBox* m_AddFootprintField;
    wxCheckBox* m_AddField1;
    wxCheckBox* m_AddField2;
    wxCheckBox* m_AddField3;
    wxCheckBox* m_AddField4;
    wxCheckBox* m_AddField5;
    wxCheckBox* m_AddField6;
    wxCheckBox* m_AddField7;
    wxCheckBox* m_AddField8;
    wxButton* m_btClose;
////@end WinEDA_Build_BOM_Frame member variables

    WinEDA_DrawFrame * m_Parent;
    wxString m_LibArchiveFileName;
    wxString m_ListFileName;
};

#endif
    // _DIALOG_BUILD_BOM_H_
