/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef DLGABOUT_H
#define DLGABOUT_H

#include "scrollingdialog.h" // inheriting class's header file
#include "cbproject.h"

#include <wx/grid.h>

#include <vector>

class wxWindow;

class dlgManageGlob : public wxScrollingDialog
{
    public:
        // class constructor
        dlgManageGlob(wxWindow* parent);
        // class destructor
        ~dlgManageGlob();

        void OnAdd(wxCommandEvent& event);
        void OnDelete(wxCommandEvent& event);
        void OnCancel(wxCommandEvent& event);
        void OnOk(wxCommandEvent& event);

    private:

        void OnPopulateList();

        wxGrid* m_grid;
        std::vector<cbProject::Glob> m_GlobList;

        DECLARE_EVENT_TABLE()
};

#endif // DLGABOUT_H
