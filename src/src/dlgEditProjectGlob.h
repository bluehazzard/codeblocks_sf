#ifndef DLGEDITPROJECTGLOB_H
#define DLGEDITPROJECTGLOB_H

//(*Headers(dlgEditProjectGlob)
#include <wx/bmpbuttn.h>
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/gbsizer.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

#include "cbProject.h"


class dlgEditProjectGlob: public wxDialog
{
	public:

		dlgEditProjectGlob(cbProject::Glob &glob, wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~dlgEditProjectGlob();

		//(*Declarations(dlgEditProjectGlob)
		wxBitmapButton* btnBrowse;
		wxBitmapButton* btnOther;
		wxCheckBox* chkRecursive;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxTextCtrl* txtPath;
		wxTextCtrl* txtWildcart;
		//*)

		cbProject::Glob GetGlob();

	protected:

		//(*Identifiers(dlgEditProjectGlob)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_BITMAPBUTTON1;
		static const long ID_BITMAPBUTTON2;
		static const long ID_CHECKBOX1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		//*)

	private:

		//(*Handlers(dlgEditProjectGlob)
		void OnbtnBrowseClick(wxCommandEvent& event);
		void OnbtnOtherClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
