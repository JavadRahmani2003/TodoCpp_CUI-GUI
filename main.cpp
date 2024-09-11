#include <wx/wx.h>
#include <wx/textfile.h>

wxPanel* MainPanel = nullptr;

int y = 0;//y of tasks they don't combine together
bool isCheckedTask = false;

wxCheckBox* CheckedTask = nullptr;
wxString TaskTextStore = "";
wxButton* BtnApply = nullptr;
wxButton* BtnRemove = nullptr;
wxListBox* mainlistbox = nullptr;

class TheApp : public wxApp
{
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(TheApp);

class TheFrame : public wxFrame
{
public:
    TheFrame();

private:
    void ToDoAdd(wxCommandEvent& event);
};

bool TheApp::OnInit()
{
    TheFrame* frame = new TheFrame();
    frame->Show(true);
    frame->Center();
    return true;
}

class EnterTaskName : public wxDialog
{
public:
    EnterTaskName(const wxString& WindowTitle);
private:
    void SetString(wxCommandEvent& event);
};


TheFrame::TheFrame() : wxFrame(nullptr, wxID_ANY, "0xJ's ToDo App", wxDefaultPosition, wxSize(500, 400), wxDEFAULT_FRAME_STYLE & ~(wxMAXIMIZE_BOX))
{
    y = 80;// wxPoint(x = default,y = 80)

    MainPanel = new wxPanel(this);
    MainPanel->SetBackgroundColour(*wxWHITE);

    mainlistbox = new wxListBox(MainPanel,wxID_ANY,wxPoint(0,y), GetSize());

    wxButton* AddList = new wxButton(MainPanel,wxID_ADD,"Add to list",wxPoint(5,5),wxSize(80,70));
    wxButton* RemoveList = new wxButton(MainPanel,wxID_REMOVE,"Remove From list",wxPoint(390,5),wxSize(90,70));
    AddList->Bind(wxEVT_BUTTON, &TheFrame::ToDoAdd,this);
    //RemoveList->Bind(wxEVT_BUTTON,&TheFrame::DelString,this);
}

EnterTaskName::EnterTaskName(const wxString& WindowTitle) : wxDialog(NULL, wxID_HELP, WindowTitle, wxDefaultPosition, wxSize(500, 180), wxDEFAULT_DIALOG_STYLE & ~(/*wxRESIZE_BORDER |*/ wxMAXIMIZE_BOX))
{
    wxPanel* subPanel = new wxPanel(this);
    subPanel->SetBackgroundColour(*wxWHITE);
            
    BtnApply = new wxButton(subPanel, wxID_EDIT, "Enter Task Name", wxDefaultPosition, wxDefaultSize);
    BtnApply->Bind(wxEVT_BUTTON, &EnterTaskName::SetString,this);

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->AddStretchSpacer();
    sizer->Add(taskName,0,wxALIGN_CENTER_VERTICAL);
    sizer->AddStretchSpacer();
    sizer->Add(BtnApply,0,wxALIGN_CENTER_VERTICAL);
    sizer->AddStretchSpacer();

    subPanel->SetSizer(sizer);
}

EnterTaskName* taskNameWindow = nullptr;
void TheFrame::ToDoAdd(wxCommandEvent& event)
{
    taskNameWindow = new EnterTaskName("EnterTaskName");
    taskNameWindow->Show(true);
    taskNameWindow->Center();
}

void EnterTaskName::SetString(wxCommandEvent& event)
{
    y += 20;//wxpoint(x,y += 20, 80 + 20 = 100 + 20 = 120)
    CheckedTask = new wxCheckBox(MainPanel,wxID_ADD, taskName->GetValue(),wxPoint(0,y),wxDefaultSize);
    taskNameWindow->Close(true);
}
