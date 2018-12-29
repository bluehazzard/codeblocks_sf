/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 *
 * $Revision$
 * $Id$
 * $HeadURL$
 */

#include <sdk.h>
#include "classwizardconfigdlg.h"
#include <wx/xrc/xmlres.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <string>
#include <configmanager.h>


#ifndef CB_PRECOMP
#include "globals.h"
#endif

BEGIN_EVENT_TABLE(ClassWizardConfigDlg, wxPanel)
END_EVENT_TABLE()

ClassWizardConfigDlg::ClassWizardConfigDlg(wxWindow* parent)
{
  //ctor
  wxXmlResource::Get()->LoadPanel(this, parent, _T("dlgClassWizardConfig"));
  LoadSettings();
}

ClassWizardConfigDlg::~ClassWizardConfigDlg()
{
  //dtor
}


void ClassWizardConfigDlg::LoadSettings()
{
  ConfigManager* cfg = Manager::Get()->GetConfigManager(_T("classwizard"));

  XRCCTRL(*this,   "rbParameterStyle",       wxRadioBox)->SetSelection(cfg->ReadInt(_T("/SetGet/ParameterStyle"),  0));
  XRCCTRL(*this,   "rbFirstLetter",          wxRadioBox)->SetSelection(cfg->ReadInt(_T("/SetGet/FirstLetter"),     0));
  XRCCTRL(*this,   "rbImplementation",       wxRadioBox)->SetSelection(cfg->ReadInt(_T("/SetGet/Implementation"),  0));
  XRCCTRL(*this,   "rbNameGeneration",       wxRadioBox)->SetSelection(cfg->ReadInt(_T("/SetGet/NameGeneration"),  0));

  XRCCTRL(*this,   "txtExtHeader",       wxTextCtrl)->SetValue(cfg->Read(_T("/header_type"),  _T("h")));
  XRCCTRL(*this,   "txtExtSource",       wxTextCtrl)->SetValue(cfg->Read(_T("/source_type"),  _T("cpp")));
}

void ClassWizardConfigDlg::SaveSettings()
{
  ConfigManager* cfg = Manager::Get()->GetConfigManager(_T("classwizard"));

  cfg->Write(_T("/SetGet/ParameterStyle"),    XRCCTRL(*this, "rbParameterStyle",    wxRadioBox)->GetSelection());
  cfg->Write(_T("/SetGet/FirstLetter"),       XRCCTRL(*this, "rbFirstLetter",       wxRadioBox)->GetSelection());
  cfg->Write(_T("/SetGet/Implementation"),    XRCCTRL(*this, "rbImplementation",    wxRadioBox)->GetSelection());
  cfg->Write(_T("/SetGet/NameGeneration"),    XRCCTRL(*this, "rbNameGeneration",    wxRadioBox)->GetSelection());

  cfg->Write(_T("/header_type"),    XRCCTRL(*this, "txtExtHeader",    wxTextCtrl)->GetValue());
  cfg->Write(_T("/source_type"),    XRCCTRL(*this, "txtExtSource",    wxTextCtrl)->GetValue());

}
