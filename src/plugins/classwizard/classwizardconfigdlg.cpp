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

}

void ClassWizardConfigDlg::SaveSettings()
{
  ConfigManager* cfg = Manager::Get()->GetConfigManager(_T("classwizard"));

  cfg->Write(_T("/SetGet/ParameterStyle"),    XRCCTRL(*this, "rbParameterStyle",    wxRadioBox)->GetSelection());
  cfg->Write(_T("/SetGet/FirstLetter"),       XRCCTRL(*this, "rbFirstLetter",       wxRadioBox)->GetSelection());
  cfg->Write(_T("/SetGet/Implementation"),    XRCCTRL(*this, "rbImplementation",    wxRadioBox)->GetSelection());
  cfg->Write(_T("/SetGet/NameGeneration"),    XRCCTRL(*this, "rbNameGeneration",    wxRadioBox)->GetSelection());

}
