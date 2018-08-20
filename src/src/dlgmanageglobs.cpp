#include "sdk.h"
#ifndef CB_PRECOMP

    #include "cbproject.h"
    #include "configmanager.h"
    #include "editorcolourset.h"
    #include "editormanager.h"
    #include "globals.h"
    #include "manager.h"
    #include "projectmanager.h"
#endif
#include "dlgManageGlobs.h"
#include "dlgEditProjectGlob.h"

//(*InternalHeaders(dlgManageGlobs)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(dlgManageGlobs)
const long dlgManageGlobs::ID_LISTCTRL1 = wxNewId();
const long dlgManageGlobs::ID_BUTTON1 = wxNewId();
const long dlgManageGlobs::ID_BUTTON2 = wxNewId();
const long dlgManageGlobs::ID_BUTTON3 = wxNewId();
const long dlgManageGlobs::ID_STATICLINE1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(dlgManageGlobs,wxDialog)
	//(*EventTable(dlgManageGlobs)
	//*)
END_EVENT_TABLE()

dlgManageGlobs::dlgManageGlobs(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(dlgManageGlobs)
	wxGridBagSizer* GridBagSizer1;
	wxGridBagSizer* GridBagSizer2;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	GridBagSizer1 = new wxGridBagSizer(0, 0);
	lstGlobsList = new wxListCtrl(this, ID_LISTCTRL1, wxDefaultPosition, wxDefaultSize, wxLC_REPORT, wxDefaultValidator, _T("ID_LISTCTRL1"));
	GridBagSizer1->Add(lstGlobsList, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxEXPAND, 5);
	GridBagSizer2 = new wxGridBagSizer(0, 0);
	btnAdd = new wxButton(this, ID_BUTTON1, _("Add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	GridBagSizer2->Add(btnAdd, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnDelete = new wxButton(this, ID_BUTTON2, _("Delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	GridBagSizer2->Add(btnDelete, wxGBPosition(1, 0), wxDefaultSpan, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnEdit = new wxButton(this, ID_BUTTON3, _("Edit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	GridBagSizer2->Add(btnEdit, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	GridBagSizer2->Add(StaticLine1, wxGBPosition(3, 0), wxDefaultSpan, wxALL|wxEXPAND, 5);
	btnCancel = new wxButton(this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
	GridBagSizer2->Add(btnCancel, wxGBPosition(4, 0), wxDefaultSpan, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnOk = new wxButton(this, wxID_OK, _("Ok"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
	GridBagSizer2->Add(btnOk, wxGBPosition(5, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridBagSizer1->Add(GridBagSizer2, wxGBPosition(0, 1), wxDefaultSpan, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	GridBagSizer1->AddGrowableCol(0);
	GridBagSizer1->AddGrowableRow(0);
	SetSizer(GridBagSizer1);
	GridBagSizer1->Fit(this);
	GridBagSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgManageGlobs::OnbtnAddClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgManageGlobs::OnbtnDeleteClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgManageGlobs::OnbtnEditClick);
	Connect(wxID_OK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgManageGlobs::OnbtnOkClick);
	//*)

    cbProject* prj = Manager::Get()->GetProjectManager()->GetActiveProject();
    if(prj != nullptr)
    {
        m_GlobList = Manager::Get()->GetProjectManager()->GetActiveProject()->GetGlobs();
        wxString title = prj->GetTitle();
        this->SetTitle(_("Edit globs of ") + title);
    }

    lstGlobsList->InsertColumn(0, _("Path"));
    lstGlobsList->InsertColumn(1, _("recursive"), wxLIST_FORMAT_CENTRE);
    lstGlobsList->InsertColumn(2, _("wildcard"));

    PopulateList();

}

dlgManageGlobs::~dlgManageGlobs()
{
	//(*Destroy(dlgManageGlobs)
	//*)
}

void dlgManageGlobs::PopulateList()
{
    lstGlobsList->DeleteAllItems();
    for (size_t i = 0; i < m_GlobList.size(); ++i)
    {
        lstGlobsList->InsertItem(i, m_GlobList[i].m_Path);
        wxString rec = wxString::Format(wxT("%i"), m_GlobList[i].m_Recursive);
        lstGlobsList->SetItem(i, 1, rec);
        lstGlobsList->SetItem(i, 2, m_GlobList[i].m_WildCard);
    }
}

void dlgManageGlobs::OnbtnAddClick(wxCommandEvent& event)
{
    cbProject::Glob tmp_glob(wxT(""), wxT("*.*"), false);
    dlgEditProjectGlob dlg(tmp_glob, nullptr);

    if (dlg.ShowModal() == wxID_OK)
    {
        tmp_glob = dlg.GetGlob();
        m_GlobList.push_back(tmp_glob);
        PopulateList();
    }
}

void dlgManageGlobs::OnbtnDeleteClick(wxCommandEvent& event)
{
    int item = -1;
    wxArrayInt items;
    for ( ;; )
    {
        item = lstGlobsList->GetNextItem(item,
                                    wxLIST_NEXT_ALL,
                                    wxLIST_STATE_SELECTED);
        if ( item == -1 )
            break;
        items.Add(item);
    }

    for(int i = 0; i < items.size(); ++i)
    {
        lstGlobsList->DeleteItem(items[i]);
        m_GlobList.erase(m_GlobList.begin() + items[i]);
    }
    PopulateList();
}

void dlgManageGlobs::OnbtnEditClick(wxCommandEvent& event)
{
    int item = lstGlobsList->GetNextItem(-1,
                                    wxLIST_NEXT_ALL,
                                    wxLIST_STATE_SELECTED);
    if ( item == -1 )
        return;

    dlgEditProjectGlob dlg(m_GlobList[item], nullptr);
    if(dlg.ShowModal() == wxID_OK)
    {
        m_GlobList[item] = dlg.GetGlob();
        PopulateList();
    }
}

void dlgManageGlobs::OnbtnOkClick(wxCommandEvent& event)
{
    cbProject* prj = Manager::Get()->GetProjectManager()->GetActiveProject();
    if(prj != nullptr && GlobsChanged())
    {
        prj->SetGlobs(m_GlobList);
        prj->SetModified(true);
    }

    this->EndModal(wxID_OK);
}

bool dlgManageGlobs::GlobsChanged()
{
    cbProject* prj = Manager::Get()->GetProjectManager()->GetActiveProject();
    if(prj != nullptr)
    {
        if(prj->GetGlobs().size() != m_GlobList.size())
            return true;

        for (size_t i = 0; i < m_GlobList.size(); ++i)
        {
           if(m_GlobList[i].m_Path      != prj->GetGlobs()[i].m_Path     ||
              m_GlobList[i].m_WildCard  != prj->GetGlobs()[i].m_WildCard ||
              m_GlobList[i].m_Recursive != prj->GetGlobs()[i].m_Recursive  )
            return true;
        }
        return false;
    }
    return true; // in doubt return true
}
