#ifndef DLGMANAGEBLOB_H
#define DLGMANAGEBLOB_H

//(*Headers(dlgmanageblob)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/gbsizer.h>
#include <wx/listctrl.h>
#include <wx/statline.h>
//*)

class dlgManageGlobs: public wxDialog
{
	public:

		dlgManageGlobs(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~dlgManageGlobs();

		//(*Declarations(dlgManageGlobs)
		wxButton* btnAdd;
		wxButton* btnCancel;
		wxButton* btnDelete;
		wxButton* btnEdit;
		wxButton* btnOk;
		wxListCtrl* lstGlobsList;
		wxStaticLine* StaticLine1;
		//*)

	protected:

		//(*Identifiers(dlgManageGlobs)
		static const long ID_LISTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		static const long ID_STATICLINE1;
		//*)

	private:

		//(*Handlers(dlgManageGlobs)
		void OnbtnAddClick(wxCommandEvent& event);
		void OnbtnDeleteClick(wxCommandEvent& event);
		void OnbtnEditClick(wxCommandEvent& event);
		void OnbtnOkClick(wxCommandEvent& event);
		//*)

		void PopulateList();
		bool GlobsChanged();

		std::vector<cbProject::Glob> m_GlobList;

		DECLARE_EVENT_TABLE()
};

#endif
