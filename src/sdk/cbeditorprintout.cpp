/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU Lesser General Public License, version 3
 * http://www.gnu.org/licenses/lgpl-3.0.html
 *
 * $Revision$
 * $Id$
 * $HeadURL$
 */

#include "sdk_precomp.h"

#ifndef CB_PRECOMP
    #include <wx/dc.h>

    #include "manager.h"
    #include "logmanager.h"
    #include "cbeditor.h"
#endif
#include "cbstyledtextctrl.h"

#include "cbeditorprintout.h"
#include "printing_types.h"
#include <wx/paper.h>

cbEditorPrintout::cbEditorPrintout(const wxString& title, cbStyledTextCtrl* control, bool selectionOnly, bool destroy)
        : wxPrintout(title),
        m_TextControl(control),
        m_selectionOnly(selectionOnly),
        m_destroyOnDestruct(destroy)
{
    // ctor
    m_SelStart = 0;
    if (control != nullptr)
    {
        m_SelEnd = control->GetLength();
        if (selectionOnly && !control->GetSelectedText().IsEmpty())
        {
            m_SelStart = control->GetSelectionStart();
            m_SelEnd = control->GetSelectionEnd();
        }
        m_editors.push_back(control);
    }
}

cbEditorPrintout::~cbEditorPrintout()
{
    // dtor
    if (m_destroyOnDestruct)
    {
        for (auto itr = m_editors.begin(); itr != m_editors.end(); ++itr)
        {
            if(*itr)
                (*itr)->Destroy();
            (*itr) = nullptr;
        }
    }
}

void cbEditorPrintout::AddEditor(cbStyledTextCtrl* control)
{
    if(control != nullptr)
        m_editors.push_back(control);
}

bool cbEditorPrintout::OnPrintPage(int page)
{
    wxDC *dc = GetDC();
    if (dc)
    {
        // scale DC
        ScaleDC(dc);

        // print selected page
        int maxpage = m_pageInfo.size();
        if (page == 0 || page > maxpage)
        {
            Manager::Get()->GetLogManager()->DebugLog(F(_T("OnPrintPage ERROR: page = %d , maxpage = %d"), page, maxpage));
            return false;
        }

        PageInfo& curPage = m_pageInfo[page-1];

        //Manager::Get()->GetLogManager()->DebugLog(_T("OnPrintPage: page %d , m_printed %d"), page, m_printed);

        // Draws the lines from m_printed to m_SelEnd and returns the printed lanes
        // if there is not enough space for all lanes m_printed != m_SelEnd
        curPage.editor->FormatRange (1, curPage.start, curPage.end,
                                      dc, dc, m_printRect, m_pageRect);
        return true;
    }
    return false;
}

bool cbEditorPrintout::HasPage( int page)
{
    return (m_pageInfo.size() > page-1);
}

void cbEditorPrintout::GetPageInfo(int *minPage, int *maxPage, int *selPageFrom, int *selPageTo)
{
    // initialize values
    *minPage = 0;
    *maxPage = 0;
    *selPageFrom = 0;
    *selPageTo = 0;
    // get print page information and convert to printer pixels
    wxSize ppiScr;
    GetPPIScreen (&ppiScr.x, &ppiScr.y);
    if (ppiScr.x == 0 || ppiScr.y == 0)
    {
        // guess
        ppiScr.x = 96;
        ppiScr.y = 96;
    }

    wxPrintData* ppd = &(g_printer->GetPrintDialogData().GetPrintData());
    // We cannot use GetSize from wxPrintData, because it always returns -1 for page.x and page.y,
    wxPrintPaperDatabase paperDB;
    paperDB.CreateDatabase();
    wxSize page=paperDB.GetSize(ppd->GetPaperId());
    if(ppd->GetOrientation() == wxLANDSCAPE )
    {
        int temp = page.x;
        page.x = page.y;
        page.y = temp;
    }

    // We have to divide through 254 instead of 25.4, because GetSize() of paperDB returns tenth of millimeters
    page.x = static_cast<int> (page.x * ppiScr.x / 254);
    page.y = static_cast<int> (page.y * ppiScr.y / 254);
    m_pageRect = wxRect (0,
                         0,
                         page.x,
                         page.y);
    // get margins information and convert to printer pixels
    int  top = 15; // default 25
    int  bottom = 15; // default 25
    int  left = 20; // default 20
    int  right = 15; // default 20
// TODO (Tiwag#1#): get margins from PageSetup Dialog
//    wxPoint (top, left) = g_pageSetupData->GetMarginTopLeft();
//    wxPoint (bottom, right) = g_pageSetupData->GetMarginBottomRight();
    top = static_cast<int> (top * ppiScr.y / 25.4);
    bottom = static_cast<int> (bottom * ppiScr.y / 25.4);
    left = static_cast<int> (left * ppiScr.x / 25.4);
    right = static_cast<int> (right * ppiScr.x / 25.4);
    m_printRect = wxRect (left,
                          top,
                          page.x - (left + right),
                          page.y - (top + bottom));

    // wxWidgets 2.4.2, have some printing-related bugs.
    // one of them is that that GetDC always returns 0 in GetPageInfo.
    // this means we can't count the pages...
    wxDC *dc = GetDC();
    if (dc)
    {
        ScaleDC(dc);

        // count pages and save SelStart value of each page
        // m_pPageSelStart[i] contains the line count for page i
        //m_pPageSelStart->Clear();
        //m_pPageSelStart->Add(m_SelStart);
        //m_printed = m_SelStart;

        for (auto itr = m_editors.begin(); itr != m_editors.end(); ++itr)
        {
            int start = 0;
            int end = (*itr)->GetLength();

            if(m_selectionOnly)
            {
                start = m_SelStart;
                end   = m_SelEnd;
            }

            do
            {
                PageInfo curPage;
                curPage.start = start;
                curPage.editor = *itr;

                curPage.end = curPage.editor->FormatRange (0, start, end,
                                                            dc, dc, m_printRect, m_pageRect);
                start = curPage.end;
                m_pageInfo.push_back(curPage);
                *maxPage += 1;

            } while( start < end);
        }
    }
    else
        *maxPage = 32000; // use a fictitious high number

    if (*maxPage > 0)
        *minPage = 1;
    *selPageFrom = *minPage;
    *selPageTo = *maxPage;
    m_printed = m_SelStart;
}

bool cbEditorPrintout::OnBeginDocument(int startPage, int endPage)
{
    bool result = wxPrintout::OnBeginDocument(startPage, endPage);
    // FIXME (Tiwag#1#): when the first time a printout is initiated
    // and you request a page to print which is out of bounds of available pages
    // it is not recognized by the above check, don't know how to fix this better
    int maxpage = m_pageInfo.size();
    if( startPage > maxpage || endPage > maxpage )
    {
        Manager::Get()->GetLogManager()->DebugLog(F(_T("OnBeginDocument ERROR: startPage %d , endPage %d , maxpage %d "), startPage, endPage, maxpage));
        return false;
    }
    return result;
}

bool cbEditorPrintout::ScaleDC(wxDC *dc)
{
    if (!dc)
        return false;
    // get printer and screen sizing values
    wxSize ppiScr;
    GetPPIScreen (&ppiScr.x, &ppiScr.y);
    if (ppiScr.x == 0)
    { // most possible guess 96 dpi
        ppiScr.x = 96;
        ppiScr.y = 96;
    }
    wxSize ppiPrt;
    GetPPIPrinter (&ppiPrt.x, &ppiPrt.y);
    if (ppiPrt.x == 0)
    { // scaling factor to 1
        ppiPrt.x = ppiScr.x;
        ppiPrt.y = ppiScr.y;
    }
    wxSize dcSize = dc->GetSize();
    wxSize pageSize;
    GetPageSizePixels (&pageSize.x, &pageSize.y);
    // set user scale
    float scale_x = (float)(ppiPrt.x * dcSize.x) /
                    (float)(ppiScr.x * pageSize.x);
    float scale_y = (float)(ppiPrt.y * dcSize.y) /
                    (float)(ppiScr.y * pageSize.y);
    dc->SetUserScale (scale_x, scale_y);
    return true;
}
