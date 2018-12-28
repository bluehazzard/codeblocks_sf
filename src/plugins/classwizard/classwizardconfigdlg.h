/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef CLASSWIZARDCONFIGDLG_H
#define CLASSWIZARDCONFIGDLG_H

#include <wx/intl.h>
#include "configurationpanel.h"

class ClassWizardConfigDlg : public cbConfigurationPanel
{
    public:
        ClassWizardConfigDlg(wxWindow* parent);
        virtual ~ClassWizardConfigDlg();

    protected:

        virtual wxString GetTitle() const override { return _("Class wizard"); }
        virtual wxString GetBitmapBaseName() const override { return _T("classwizard-plugin"); }
        virtual void OnApply() override { SaveSettings(); }
        virtual void OnCancel() override {}

        void LoadSettings();
        void SaveSettings();

    private:
        DECLARE_EVENT_TABLE()
};

#endif // CLASSWIZARDCONFIGDLG_H
