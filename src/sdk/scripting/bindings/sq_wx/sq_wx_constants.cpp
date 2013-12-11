
#include <scripting/bindings/sq_wx/sq_wx.h>
#include <scripting/bindings/sc_binding_util.h>
#include <wx/choice.h>
#include <wx/hyperlink.h>
#include <wx/propgrid/propgrid.h>

namespace ScriptBindings
{


void bind_wxConstants(HSQUIRRELVM vm)
{
/** \defgroup sq_wx_constants wxWidgets constants bound to squirrel
 *  \ingroup Squirrel
 *  \brief
*/

    BIND_INT_CONSTANT(wxNOT_FOUND);

    BIND_INT_CONSTANT(wxEVT_ACTIVATE);
    BIND_INT_CONSTANT(wxEVT_ACTIVATE_APP);
    BIND_INT_CONSTANT(wxEVT_COMMAND_BUTTON_CLICKED);
    BIND_INT_CONSTANT_NAMED(wxEVT_COMMAND_BUTTON_CLICKED,"wxEVT_BUTTON");
    BIND_INT_CONSTANT(wxEVT_COMMAND_CHECKBOX_CLICKED);
    BIND_INT_CONSTANT_NAMED(wxEVT_COMMAND_CHECKBOX_CLICKED,"EVT_CHECKBOX");
    BIND_INT_CONSTANT(wxEVT_COMMAND_CHOICE_SELECTED);
    BIND_INT_CONSTANT_NAMED(wxEVT_COMMAND_CHOICE_SELECTED,"wxEVT_CHOICE");
    BIND_INT_CONSTANT(wxEVT_COMMAND_LISTBOX_SELECTED);
    BIND_INT_CONSTANT_NAMED(wxEVT_COMMAND_LISTBOX_SELECTED,"wxEVT_LISTBOX");
    BIND_INT_CONSTANT(wxEVT_COMMAND_LISTBOX_DOUBLECLICKED);
    BIND_INT_CONSTANT_NAMED(wxEVT_COMMAND_LISTBOX_DOUBLECLICKED,"wxEVT_LISTBOX_DCLICK");
    BIND_INT_CONSTANT(wxEVT_COMMAND_CHECKLISTBOX_TOGGLED);
    BIND_INT_CONSTANT_NAMED(wxEVT_COMMAND_CHECKLISTBOX_TOGGLED,"wxEVT_CHECKLISTBOX");

    // now they are in wx/textctrl.h
    BIND_INT_CONSTANT(wxEVT_COMMAND_TEXT_UPDATED);
    BIND_INT_CONSTANT(wxEVT_COMMAND_TEXT_ENTER);
    BIND_INT_CONSTANT(wxEVT_COMMAND_TEXT_URL);
    BIND_INT_CONSTANT(wxEVT_COMMAND_TEXT_MAXLEN);
    BIND_INT_CONSTANT(wxEVT_COMMAND_MENU_SELECTED);
    BIND_INT_CONSTANT(wxEVT_COMMAND_SLIDER_UPDATED);
    BIND_INT_CONSTANT(wxEVT_COMMAND_RADIOBOX_SELECTED);
    BIND_INT_CONSTANT(wxEVT_COMMAND_RADIOBUTTON_SELECTED);
    BIND_INT_CONSTANT(wxEVT_COMMAND_HYPERLINK);

    // wxEVT_COMMAND_SCROLLBAR_UPDATED is now obsolete since we use
    // wxEVT_SCROLL... events

    BIND_INT_CONSTANT(wxEVT_COMMAND_SCROLLBAR_UPDATED);
    BIND_INT_CONSTANT(wxEVT_COMMAND_VLBOX_SELECTED);
    BIND_INT_CONSTANT(wxEVT_COMMAND_COMBOBOX_SELECTED);
    BIND_INT_CONSTANT(wxEVT_COMMAND_TOOL_RCLICKED);
    BIND_INT_CONSTANT(wxEVT_COMMAND_TOOL_ENTER);
    BIND_INT_CONSTANT(wxEVT_COMMAND_SPINCTRL_UPDATED);
    BIND_INT_CONSTANT(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED);
    BIND_INT_CONSTANT(wxEVT_COMMAND_SEARCHCTRL_CANCEL_BTN);
    BIND_INT_CONSTANT(wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN);
    BIND_INT_CONSTANT(wxEVT_COMMAND_COLOURPICKER_CHANGED);
    BIND_INT_CONSTANT(wxEVT_COMMAND_FILEPICKER_CHANGED);
    BIND_INT_CONSTANT(wxEVT_COMMAND_DIRPICKER_CHANGED);


    // Sockets and timers send events, too
    BIND_INT_CONSTANT(wxEVT_TIMER);

        // Mouse event types
    BIND_INT_CONSTANT(wxEVT_LEFT_DOWN);
    BIND_INT_CONSTANT(wxEVT_LEFT_UP);
    BIND_INT_CONSTANT(wxEVT_MIDDLE_DOWN);
    BIND_INT_CONSTANT(wxEVT_MIDDLE_UP);
    BIND_INT_CONSTANT(wxEVT_RIGHT_DOWN);
    BIND_INT_CONSTANT(wxEVT_RIGHT_UP);
    BIND_INT_CONSTANT(wxEVT_MOTION);
    BIND_INT_CONSTANT(wxEVT_ENTER_WINDOW);
    BIND_INT_CONSTANT(wxEVT_LEAVE_WINDOW);
    BIND_INT_CONSTANT(wxEVT_LEFT_DCLICK);
    BIND_INT_CONSTANT(wxEVT_MIDDLE_DCLICK);
    BIND_INT_CONSTANT(wxEVT_RIGHT_DCLICK);
    BIND_INT_CONSTANT(wxEVT_SET_FOCUS);
    BIND_INT_CONSTANT(wxEVT_KILL_FOCUS);
    BIND_INT_CONSTANT(wxEVT_CHILD_FOCUS);
    BIND_INT_CONSTANT(wxEVT_MOUSEWHEEL);

    // Non-client mouse events
    /*BIND_INT_CONSTANT(wxEVT_NC_LEFT_DOWN);
    BIND_INT_CONSTANT(wxEVT_NC_LEFT_UP);
    BIND_INT_CONSTANT(wxEVT_NC_MIDDLE_DOWN);
    BIND_INT_CONSTANT(wxEVT_NC_MIDDLE_UP);
    BIND_INT_CONSTANT(wxEVT_NC_RIGHT_DOWN);
    BIND_INT_CONSTANT(wxEVT_NC_RIGHT_UP);
    BIND_INT_CONSTANT(wxEVT_NC_MOTION);
    BIND_INT_CONSTANT(wxEVT_NC_ENTER_WINDOW);
    BIND_INT_CONSTANT(wxEVT_NC_LEAVE_WINDOW);
    BIND_INT_CONSTANT(wxEVT_NC_LEFT_DCLICK);
    BIND_INT_CONSTANT(wxEVT_NC_MIDDLE_DCLICK);
    BIND_INT_CONSTANT(wxEVT_NC_RIGHT_DCLICK);*/

        // Character input event type
    BIND_INT_CONSTANT(wxEVT_CHAR);
    BIND_INT_CONSTANT(wxEVT_CHAR_HOOK);
    BIND_INT_CONSTANT(wxEVT_NAVIGATION_KEY);
    BIND_INT_CONSTANT(wxEVT_KEY_DOWN);
    BIND_INT_CONSTANT(wxEVT_KEY_UP);
#if wxUSE_HOTKEY
    BIND_INT_CONSTANT(wxEVT_HOTKEY);
#endif
        // Set cursor event
    BIND_INT_CONSTANT(wxEVT_SET_CURSOR);

        // wxScrollBar and wxSlider event identifiers
    BIND_INT_CONSTANT(wxEVT_SCROLL_TOP);
    BIND_INT_CONSTANT(wxEVT_SCROLL_BOTTOM);
    BIND_INT_CONSTANT(wxEVT_SCROLL_LINEUP);
    BIND_INT_CONSTANT(wxEVT_SCROLL_LINEDOWN);
    BIND_INT_CONSTANT(wxEVT_SCROLL_PAGEUP);
    BIND_INT_CONSTANT(wxEVT_SCROLL_PAGEDOWN);
    BIND_INT_CONSTANT(wxEVT_SCROLL_THUMBTRACK);
    BIND_INT_CONSTANT(wxEVT_SCROLL_THUMBRELEASE);
    BIND_INT_CONSTANT(wxEVT_SCROLL_CHANGED);



        // Scroll events from wxWindow
    BIND_INT_CONSTANT(wxEVT_SCROLLWIN_TOP);
    BIND_INT_CONSTANT(wxEVT_SCROLLWIN_BOTTOM);
    BIND_INT_CONSTANT(wxEVT_SCROLLWIN_LINEUP);
    BIND_INT_CONSTANT(wxEVT_SCROLLWIN_LINEDOWN);
    BIND_INT_CONSTANT(wxEVT_SCROLLWIN_PAGEUP);
    BIND_INT_CONSTANT(wxEVT_SCROLLWIN_PAGEDOWN);
    BIND_INT_CONSTANT(wxEVT_SCROLLWIN_THUMBTRACK);
    BIND_INT_CONSTANT(wxEVT_SCROLLWIN_THUMBRELEASE);

        // System events
    BIND_INT_CONSTANT(wxEVT_SIZE);
    BIND_INT_CONSTANT(wxEVT_MOVE);
    BIND_INT_CONSTANT(wxEVT_CLOSE_WINDOW);
    BIND_INT_CONSTANT(wxEVT_END_SESSION);
    BIND_INT_CONSTANT(wxEVT_QUERY_END_SESSION);
    BIND_INT_CONSTANT(wxEVT_ACTIVATE_APP);
    // 406..408 are power events
    BIND_INT_CONSTANT(wxEVT_ACTIVATE);
    BIND_INT_CONSTANT(wxEVT_CREATE);
    BIND_INT_CONSTANT(wxEVT_DESTROY);
    BIND_INT_CONSTANT(wxEVT_SHOW);
    BIND_INT_CONSTANT(wxEVT_ICONIZE);
    BIND_INT_CONSTANT(wxEVT_MAXIMIZE);
    BIND_INT_CONSTANT(wxEVT_MOUSE_CAPTURE_CHANGED);
    BIND_INT_CONSTANT(wxEVT_MOUSE_CAPTURE_LOST);
    BIND_INT_CONSTANT(wxEVT_PAINT);
    BIND_INT_CONSTANT(wxEVT_ERASE_BACKGROUND);
    BIND_INT_CONSTANT(wxEVT_NC_PAINT);
    //BIND_INT_CONSTANT(wxEVT_PAINT_ICON);
    BIND_INT_CONSTANT(wxEVT_MENU_OPEN);
    BIND_INT_CONSTANT(wxEVT_MENU_CLOSE);
    BIND_INT_CONSTANT(wxEVT_MENU_HIGHLIGHT);
    BIND_INT_CONSTANT(wxEVT_CONTEXT_MENU);
    BIND_INT_CONSTANT(wxEVT_SYS_COLOUR_CHANGED);
    BIND_INT_CONSTANT(wxEVT_DISPLAY_CHANGED);
    //BIND_INT_CONSTANT(wxEVT_SETTING_CHANGED);
    BIND_INT_CONSTANT(wxEVT_QUERY_NEW_PALETTE);
    BIND_INT_CONSTANT(wxEVT_PALETTE_CHANGED);
    BIND_INT_CONSTANT(wxEVT_JOY_BUTTON_DOWN);
    BIND_INT_CONSTANT(wxEVT_JOY_BUTTON_UP);
    BIND_INT_CONSTANT(wxEVT_JOY_MOVE);
    BIND_INT_CONSTANT(wxEVT_JOY_ZMOVE);
    BIND_INT_CONSTANT(wxEVT_DROP_FILES);
    //BIND_INT_CONSTANT(wxEVT_DRAW_ITEM);
    //BIND_INT_CONSTANT(wxEVT_MEASURE_ITEM);
    //BIND_INT_CONSTANT(wxEVT_COMPARE_ITEM);
    BIND_INT_CONSTANT(wxEVT_INIT_DIALOG);
    BIND_INT_CONSTANT(wxEVT_UPDATE_UI);
    BIND_INT_CONSTANT(wxEVT_SIZING);
    BIND_INT_CONSTANT(wxEVT_MOVING);
    BIND_INT_CONSTANT(wxEVT_HIBERNATE);
    // more power events follow -- see wx/power.h

        // Clipboard events
    BIND_INT_CONSTANT(wxEVT_COMMAND_TEXT_COPY);
    BIND_INT_CONSTANT(wxEVT_COMMAND_TEXT_CUT);
    BIND_INT_CONSTANT(wxEVT_COMMAND_TEXT_PASTE);

        // Generic command events
        // Note: a click is a higher-level event than button down/up
    BIND_INT_CONSTANT(wxEVT_COMMAND_LEFT_CLICK);
    BIND_INT_CONSTANT(wxEVT_COMMAND_LEFT_DCLICK);
    BIND_INT_CONSTANT(wxEVT_COMMAND_RIGHT_CLICK);
    BIND_INT_CONSTANT(wxEVT_COMMAND_RIGHT_DCLICK);
    BIND_INT_CONSTANT(wxEVT_COMMAND_SET_FOCUS);
    BIND_INT_CONSTANT(wxEVT_COMMAND_KILL_FOCUS);
    BIND_INT_CONSTANT(wxEVT_COMMAND_ENTER);

        // Help events
    BIND_INT_CONSTANT(wxEVT_HELP);
    BIND_INT_CONSTANT(wxEVT_DETAILED_HELP);


    // Property Grid event
    BIND_INT_CONSTANT(wxEVT_PG_SELECTED);
    BIND_INT_CONSTANT(wxEVT_PG_CHANGED);
    BIND_INT_CONSTANT(wxEVT_PG_CHANGING);
    BIND_INT_CONSTANT(wxEVT_PG_HIGHLIGHTED);
    BIND_INT_CONSTANT(wxEVT_PG_RIGHT_CLICK);
    BIND_INT_CONSTANT(wxEVT_PG_DOUBLE_CLICK);
    BIND_INT_CONSTANT(wxEVT_PG_ITEM_COLLAPSED);
    BIND_INT_CONSTANT(wxEVT_PG_ITEM_EXPANDED);
    BIND_INT_CONSTANT(wxEVT_PG_LABEL_EDIT_BEGIN);
    BIND_INT_CONSTANT(wxEVT_PG_LABEL_EDIT_ENDING);
    //BIND_INT_CONSTANT(wxEVT_PG_COL_BEGIN_DRAG);
    //BIND_INT_CONSTANT(wxEVT_PG_COL_DRAGGING);
    //BIND_INT_CONSTANT(wxEVT_PG_COL_END_DRAG);

    // path separator for filenames
    BIND_WXSTR_CONSTANT_NAMED(wxString(wxFILE_SEP_PATH), "wxFILE_SEP_PATH");

    // wxPathFormat
    BIND_INT_CONSTANT(wxPATH_NATIVE);
    BIND_INT_CONSTANT(wxPATH_UNIX);
    BIND_INT_CONSTANT(wxPATH_BEOS);
    BIND_INT_CONSTANT(wxPATH_MAC);
    BIND_INT_CONSTANT(wxPATH_DOS);
    BIND_INT_CONSTANT(wxPATH_WIN);
    BIND_INT_CONSTANT(wxPATH_OS2);
    BIND_INT_CONSTANT(wxPATH_VMS);

    // for wxFileName::GetPath()
    BIND_INT_CONSTANT(wxPATH_GET_VOLUME);
    BIND_INT_CONSTANT(wxPATH_GET_SEPARATOR);

    // wxPathNormalize
    BIND_INT_CONSTANT(wxPATH_NORM_ENV_VARS);
    BIND_INT_CONSTANT(wxPATH_NORM_DOTS);
    BIND_INT_CONSTANT(wxPATH_NORM_TILDE);
    BIND_INT_CONSTANT(wxPATH_NORM_CASE);
    BIND_INT_CONSTANT(wxPATH_NORM_ABSOLUTE);
    BIND_INT_CONSTANT(wxPATH_NORM_LONG);
    BIND_INT_CONSTANT(wxPATH_NORM_SHORTCUT);
    BIND_INT_CONSTANT(wxPATH_NORM_ALL);



}


}
