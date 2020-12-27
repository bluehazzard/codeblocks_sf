#include "sdk.h"
#ifndef CB_PRECOMP

    #include "cbproject.h"
    #include "configmanager.h"
    #include "editorcolourset.h"
    #include "editormanager.h"
    #include "globals.h"
    #include "manager.h"
    #include "projectmanager.h"
    #include "projectloader.h"
#endif
#include "manageglobsdlg.h"
#include "editprojectglobsdlg.h"

//(*InternalHeaders(ManageGlobsDlg)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(ManageGlobsDlg)
const long ManageGlobsDlg::ID_LISTCTRL1 = wxNewId();
const long ManageGlobsDlg::ID_BUTTON1 = wxNewId();
const long ManageGlobsDlg::ID_BUTTON2 = wxNewId();
const long ManageGlobsDlg::ID_BUTTON3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ManageGlobsDlg,wxDialog)
	//(*EventTable(ManageGlobsDlg)
	//*)
END_EVENT_TABLE()

ManageGlobsDlg::ManageGlobsDlg(cbProject* prj, wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(ManageGlobsDlg)
	wxGridBagSizer* GridBagSizer1;
	wxGridBagSizer* GridBagSizer2;
	wxStaticLine* StaticLine1;

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
	StaticLine1 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("wxID_ANY"));
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

	Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&ManageGlobsDlg::OnlstGlobsListItemSelect);
	Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_DESELECTED,(wxObjectEventFunction)&ManageGlobsDlg::OnlstGlobsListItemDeselect);
	Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_ACTIVATED,(wxObjectEventFunction)&ManageGlobsDlg::OnlstGlobsListItemActivated);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ManageGlobsDlg::OnAddClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ManageGlobsDlg::OnDeleteClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ManageGlobsDlg::OnEditClick);
	Connect(wxID_OK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ManageGlobsDlg::OnOkClick);
	//*)

    if (prj != nullptr)
    {
        m_Prj = prj;
        m_GlobList = m_Prj->GetGlobs();
        wxString title = m_Prj->GetTitle();
        this->SetTitle(wxString::Format(_("Edit globs of %s"), title.wx_str()));
    }

    btnEdit->Disable();
    btnDelete->Disable();

    lstGlobsList->InsertColumn(0, _("Path"));
    lstGlobsList->InsertColumn(1, _("Recursive"), wxLIST_FORMAT_CENTRE);
    lstGlobsList->InsertColumn(2, _("Wildcard"));

    m_GlobsChanged = false;

    PopulateList();

}

ManageGlobsDlg::~ManageGlobsDlg()
{
	//(*Destroy(ManageGlobsDlg)
	//*)
}

void ManageGlobsDlg::PopulateList()
{
    lstGlobsList->DeleteAllItems();
    int i = 0;
    for (const std::shared_ptr<ProjectGlob>& globObj : m_GlobList)
    {
        if (globObj)
        {
            lstGlobsList->InsertItem(i, globObj->GetPath());
            wxString rec = wxString::Format(wxT("%i"), globObj->GetRecursive());
            lstGlobsList->SetItem(i, 1, rec);
            lstGlobsList->SetItem(i, 2, globObj->GetWildCard());
            ++i;
        }
    }
}

void ManageGlobsDlg::OnAddClick(wxCommandEvent& event)
{
    std::shared_ptr<ProjectGlob> tmpGlob = std::make_shared<ProjectGlob>("", "*.*", false);
    EditProjectGlobsDlg dlg(tmpGlob, nullptr);
    if (dlg.ShowModal() == wxID_OK)
    {
        dlg.WriteGlob();
        if (std::find_if(m_GlobList.begin(), m_GlobList.end(), [&tmpGlob](const std::shared_ptr<ProjectGlob>& a){ return tmpGlob->GetId() == a->GetId(); }) == m_GlobList.end())
        {
            m_GlobList.push_back(tmpGlob);
            PopulateList();
            m_GlobsChanged = true;
        }
        else
            cbMessageBox("Path already in list", "Info");
    }
}

void ManageGlobsDlg::OnDeleteClick(wxCommandEvent& event)
{
    int item = -1;
    std::vector<std::shared_ptr<ProjectGlob>> itemsToDelete;
    for ( ;; )
    {
        item = lstGlobsList->GetNextItem(item,
                                         wxLIST_NEXT_ALL,
                                         wxLIST_STATE_SELECTED);
        if ( item == -1 )
            break;
        itemsToDelete.push_back(m_GlobList[item]);
    }

    for (auto itr = m_GlobList.begin(); itr != m_GlobList.end(); )
    {
        if (std::find(itemsToDelete.begin(),itemsToDelete.end(), *itr ) != itemsToDelete.end())
            itr = m_GlobList.erase(itr);
        else
            ++itr;
    }

    if(itemsToDelete.size() > 0)
        m_GlobsChanged = true;

    PopulateList();
}

void ManageGlobsDlg::OnEditClick(wxCommandEvent& event)
{
    EditSelectedItem();
}

void  ManageGlobsDlg::EditSelectedItem()
{
    int item = lstGlobsList->GetNextItem(-1,
                                         wxLIST_NEXT_ALL,
                                         wxLIST_STATE_SELECTED);
    if ( item == -1 )
        return;

    EditProjectGlobsDlg dlg(m_GlobList[item], this);
    if (dlg.ShowModal() == wxID_OK)
    {
        dlg.WriteGlob();
        m_GlobsChanged = true;
        PopulateList();
    }
}

void ManageGlobsDlg::OnOkClick(wxCommandEvent& event)
{
    if (m_Prj != nullptr && GlobsChanged())
    {
        m_Prj->SetModified(true);
        m_Prj->SetGlobs(m_GlobList);
        Manager::Get()->GetProjectManager()->GetUI().ReloadFileSystemWatcher(m_Prj);
        Manager::Get()->GetProjectManager()->GetUI().RebuildTree();
    }
    this->EndModal(wxID_OK);
}

bool ManageGlobsDlg::GlobsChanged()
{
    return m_GlobsChanged;
}

void ManageGlobsDlg::OnlstGlobsListItemSelect(wxListEvent& event)
{
    btnEdit->Enable();
    btnDelete->Enable();
}

void ManageGlobsDlg::OnlstGlobsListItemDeselect(wxListEvent& event)
{
    btnEdit->Disable();
    btnDelete->Disable();
}

void ManageGlobsDlg::OnlstGlobsListItemActivated(wxListEvent& event)
{
    EditSelectedItem();
}
