/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 *
 * $Revision$
 * $Id$
 * $HeadURL$
 */

#include "sdk.h"

#ifndef CB_PRECOMP
    #ifdef __WXMAC__
        #include <wx/font.h>
    #endif //__WXMAC__
    #include <wx/button.h>    // wxImage
    #include <wx/image.h>    // wxImage
    #include <wx/intl.h>
    #include <wx/stattext.h>
    #include <wx/string.h>
    #include <wx/textctrl.h>
    #include <wx/xrc/xmlres.h>
    #if wxCHECK_VERSION(3, 0, 0)
        #include <wx/versioninfo.h>
    #endif // wxCHECK_VERSION

    #include "licenses.h"
    #include "configmanager.h"
    #include "wx/wxscintilla.h"
#endif

#include <wx/bitmap.h>
#include <wx/dcmemory.h>    // wxMemoryDC
#include <wx/statbmp.h>
#include <algorithm>

#include "appglobals.h"
#include "dlgmanageglob.h" // class's header file


BEGIN_EVENT_TABLE(dlgManageGlob, wxScrollingDialog)
    EVT_BUTTON(XRCID("btnGlobAdd"),      dlgManageGlob::OnAdd)
    EVT_BUTTON(XRCID("btnGlobDelete"),   dlgManageGlob::OnDelete)
    EVT_BUTTON(XRCID("btnGlobCancel"),   dlgManageGlob::OnCancel)
    EVT_BUTTON(XRCID("btnGlobOk"),       dlgManageGlob::OnOk)
END_EVENT_TABLE()
// class constructor

dlgManageGlob::dlgManageGlob(wxWindow* parent)
{
    if (!wxXmlResource::Get()->LoadObject(this, parent, _T("dlgManageGlob"), _T("wxScrollingDialog")))
    {
        cbMessageBox(_("There was an error loading the \"About\" dialog from XRC file."),
                     _("Information"), wxICON_EXCLAMATION);
        return;
    }

    m_grid = XRCCTRL(*this, "listCtrlGlob", wxGrid);

    wxButton *OkButton = XRCCTRL(*this, "btnGlobOk", wxButton);
    OkButton->SetDefault();
    OkButton->SetFocus();

    cbProject* prj = Manager::Get()->GetProjectManager()->GetActiveProject();
    if(prj != nullptr)
    {
        m_GlobList = Manager::Get()->GetProjectManager()->GetActiveProject()->GetGlobs();
    }

    m_grid->CreateGrid( 0, 3 );

    m_grid->SetColLabelValue(0, _("Path"));
    m_grid->SetColLabelValue(1, _("recursive"));
    m_grid->SetColLabelValue(2, _("mask"));

    m_grid->SetRowLabelSize(wxGRID_AUTOSIZE);
    m_grid->SetColLabelSize(wxGRID_AUTOSIZE);

    Fit();
    CentreOnParent();

    OnPopulateList();
}

// class destructor
dlgManageGlob::~dlgManageGlob()
{
    // insert your code here
}

void dlgManageGlob::OnPopulateList()
{
    size_t i = 0;
    for(; i < m_GlobList.size(); i++)
    {
        m_grid->AppendRows(1);
        m_grid->SetCellValue(i,0, m_GlobList[i].m_Path);


        m_grid->SetCellRenderer(i, 1, new wxGridCellBoolRenderer);
        m_grid->SetCellEditor(i, 1, new wxGridCellBoolEditor);
        m_grid->SetCellAlignment(i, 1, wxALIGN_CENTRE , wxALIGN_CENTRE  );
        m_grid->SetCellValue(i, 1, m_GlobList[i].m_Recursive ? _("1") : wxString() );

        m_grid->SetCellValue(i, 2, m_GlobList[i].m_WildCard);
    }
    m_grid->SetRowLabelSize(wxGRID_AUTOSIZE );
}

void dlgManageGlob::OnAdd(wxCommandEvent& event)
{
    m_grid->AppendRows(1);
}

void dlgManageGlob::OnDelete(wxCommandEvent& event)
{
    long item = 0;

    wxArrayInt rows = m_grid->GetSelectedRows();
    for(; item < rows.size(); ++item)
    {
        m_grid->DeleteRows(rows[item]);
        m_GlobList.erase(m_GlobList.begin() + item);
    }
}

void dlgManageGlob::OnCancel(wxCommandEvent& event)
{
    // insert your code here
    this->EndModal(wxID_CANCEL);
}

void dlgManageGlob::OnOk(wxCommandEvent& event)
{

    m_GlobList.clear();

    for(int row = 0; row < m_grid->GetNumberRows(); ++row)
    {
        if(m_grid->GetCellValue(row,0) == wxEmptyString)
        {
            continue;
        }
        wxString path = m_grid->GetCellValue(row,0);
        wxString strRec = m_grid->GetCellValue(row,1);
        wxString wildchart = m_grid->GetCellValue(row,2);
        bool recursive = true;
        if(strRec == _("1"))
            recursive = true;
        else
            recursive = false;

        m_GlobList.push_back(cbProject::Glob(path, wildchart, recursive));
    }

    cbProject* prj = Manager::Get()->GetProjectManager()->GetActiveProject();

    if(prj != nullptr)
    {
        prj->SetGlobs(m_GlobList);
        prj->SetModified(true);
    }

    this->EndModal(wxID_OK);
}
