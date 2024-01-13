#include <wx/wx.h>
#include <fstream>
#include <wx/notebook.h>
#include <wx/spinctrl.h>
#include<wx/mediactrl.h>
#include <wx/grid.h>


class MainPagecontent : public wxPanel
{
public:
    wxMediaCtrl* Hit_button_Sound;//the sound effect of the button
    wxMediaCtrl* lucky_button_Sound;

    MainPagecontent(wxWindow* parent)
        : wxPanel(parent, wxID_ANY)
    {
        ::wxInitAllImageHandlers();
        // Load the background image
        wxString imagePath = "C:\\ProjData\\FirstGUI\\assets\\dee.png";
        background.LoadFile(imagePath, wxBITMAP_TYPE_ANY);

        // Set up the main page title
        wxStaticText* titleLabel = new wxStaticText(this, wxID_ANY, "Welcome to our factory", wxPoint(20, 20));
        titleLabel->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

        // Set up the exit button
        wxButton* exitButton = new wxButton(this, wxID_ANY, "Exit");
        exitButton->Bind(wxEVT_BUTTON, &MainPagecontent::OnExitButtonClick, this);

        //set feel lucky button
        wxButton* luckyButton = new wxButton(this, wxID_ANY, "Feel Lucky!");
        luckyButton->Bind(wxEVT_BUTTON, &MainPagecontent::OnLuckyButtonClick, this);

        // Set up layout
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(titleLabel, 0, wxALIGN_CENTER | wxTOP | wxLEFT, 20);
        sizer->AddStretchSpacer();  // Add space to push the button to the bottom

        sizer->Add(exitButton, 0, wxALIGN_RIGHT | wxBOTTOM | wxRIGHT, 20);
        sizer->Add(luckyButton, 0, wxALIGN_RIGHT | wxBOTTOM | wxRIGHT, 10);
        SetSizer(sizer);

        // Bind the paint event
        Bind(wxEVT_PAINT, &MainPagecontent::OnPaint, this);

        Hit_button_Sound = new wxMediaCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);//properties of the mediaplayer
        Hit_button_Sound->SetPlaybackRate(1.0);//the media player
        Hit_button_Sound->Load("C:\\ProjData\\FirstGUI\\assets\\Explosion Sound Effects(MP3_160K).mp3");

        lucky_button_Sound = new wxMediaCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);//properties of the mediaplayer
        lucky_button_Sound->SetPlaybackRate(1.0);//the media player
        lucky_button_Sound->Load("C:\\ProjData\\FirstGUI\\assets\\It was Perfect – Homelander The Boys Video meme Template(MP3_160K).mp3");
    }

private:
    void OnPaint(wxPaintEvent& event)
    {
        wxPaintDC dc(this);
        if (background.IsOk()) {
            dc.DrawBitmap(wxBitmap(background), 0, 0, false);
        }
    }

    void OnExitButtonClick(wxCommandEvent& event)
    {
        //explosion
        Hit_button_Sound->Play();
        wxMilliSleep(3000);
        // Close the main frame when the exit button is clicked
        wxExit();
    }
    void OnLuckyButtonClick(wxCommandEvent& event)
    {
        //perfect sound
        lucky_button_Sound->Play();
        
    }

    wxImage background;
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MainPagecontent, wxPanel)
EVT_PAINT(MainPagecontent::OnPaint)
wxEND_EVENT_TABLE()


class SearchHistoryPanel : public wxPanel// class for the panel of the main page (first page in our magic book)
{
public:
    wxMediaCtrl* Hit_button_Sound;//the sound effect of the button
    wxButton* Search_history_delete_button;// the button that will delete the history
    int ctr = 0;//counter that will be used to add rows
    wxGrid* Search_history_grid;//the search history table
    wxCheckBox* Rewrite_the_history;
    wxStaticText* warning_message;
    wxStaticText* title;

    wxButton* Addbtn;

    SearchHistoryPanel(wxNotebook* parent) : wxPanel(parent)//creating panel"the second parameter is a label of type wxString which will be a text in the panel"
    {


        Addbtn = new wxButton(this, wxID_ANY, "add a cell", wxPoint(90, 300), wxDefaultSize);
        Addbtn->Bind(wxEVT_BUTTON, &SearchHistoryPanel::add_grid_row, this);
        //the font of the title
        title = new wxStaticText(this, wxID_ANY, "welcome to the Search history", wxPoint(300, -1), wxDefaultSize);//label with default size 
        wxFont title_font(18, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        title->SetFont(title_font);

        //warning message
        warning_message = new wxStaticText(this, wxID_ANY, "Warning: A Program with no history is a Program with no future.\n Do you realy want to delete the history?", wxPoint(100, 580), wxDefaultSize);
        warning_message->SetForegroundColour(wxColor(255, 0, 0));
        warning_message->Hide();

        Search_history_grid = new wxGrid(this, wxID_ANY, wxPoint(250, 100), wxSize(600, 450));
        Search_history_grid->CreateGrid(ctr, 1);//create grid with ctr(zero) rows and 1 column
        Search_history_grid->SetColLabelValue(0, "search history");//set the header of the column to "search history". Note: index 0 is the header column

        // delete button
        Search_history_delete_button = new wxButton(this, wxID_ANY, "Delete", wxPoint(500, 600));
        Search_history_delete_button->Bind(wxEVT_BUTTON, &SearchHistoryPanel::Hit_button_event, this);
        Search_history_delete_button->Enable(false);

        //the rewrite the history checkbox
        Rewrite_the_history = new wxCheckBox(this, wxID_ANY, "do you really want to delete the history?", wxPoint(600, 600), wxDefaultSize);
        Rewrite_the_history->SetForegroundColour(wxColor(255, 0, 0));
        Rewrite_the_history->Bind(wxEVT_CHECKBOX, &SearchHistoryPanel::Warning_checkBox, this);
        //sound effect

        Hit_button_Sound = new wxMediaCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);//properties of the mediaplayer
        Hit_button_Sound->SetPlaybackRate(1.0);//the media player
        Hit_button_Sound->Load("C:\\ProjData\\FirstGUI\\assets\\Punch Sound Effect(MP3_160K).mp3");//loading the sound using the directory 
        //using the event  you created and linking it with the button
    }
private:
    bool IsGridEmpty(wxGrid* grid)
    {
        return grid->GetNumberRows() == 1 && grid->GetNumberCols() == 1;
    }

    void Hit_button_event(wxCommandEvent& event)//you must pass an event parameter
    {

        Hit_button_Sound->Play();//play the sound

        if (Search_history_grid->GetNumberRows() > 0)//check if the grid is empty or not
        {
            // Clear the grid
            Search_history_grid->ClearGrid();
            Search_history_grid->DeleteRows(0, Search_history_grid->GetNumberRows());

            Search_history_grid->AppendRows(1);
            Rewrite_the_history->SetValue(false);
            warning_message->Hide();
            Search_history_delete_button->Enable(false);

            ctr = 0;
        }
    }

    void Warning_checkBox(wxCommandEvent& event)//you must pass an event parameter
    {
        warning_message->Show();
        Search_history_delete_button->Enable(true);
    }
    void add_grid_row(wxCommandEvent& event)//you must pass an event parameter
    {
        Hit_button_Sound->Play();//play the sound

        Search_history_grid->AppendRows(1);
        Search_history_grid->SetCellValue(ctr, 0, "add kaza");

        Search_history_grid->SetReadOnly(ctr, 0);

        Search_history_grid->SetColSize(0, 500);
        ctr++;
    }
};


class Relations : public wxPanel// class for the panel of the main page (first page in our magic book)
{
public:
    wxMediaCtrl* Hit_button_Sound;//the sound effect of the button
    wxButton* create_rels_btn;
    wxChoice* supList;
    wxChoice* spaList;
    bool supList_flag = false;
    bool spaList_flag = false;
    wxStaticText* title;
    wxStaticText* undefined_message;
    wxMediaCtrl* Rel_Exist_sound;

    bool search_flag_text_control = true;//counter that will use to prevent the deletion from the textbox

    Relations(wxNotebook* parent) : wxPanel(parent)//creating panel"the second parameter is a label of type wxString which will be a text in the panel"
    {
        title = new wxStaticText(this, wxID_ANY, "Welcome to our relation generator", wxPoint(300, -1), wxDefaultSize);//label with default size 

        //the font of the error message(its linked with the search button event)
        wxFont title_font(18, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        title->SetFont(title_font);
        //if not found message
        undefined_message = new wxStaticText(this, wxID_ANY, "Sorry, but there is already a relationship", wxPoint(250, 350), wxDefaultSize);
        undefined_message->SetForegroundColour(wxColour(255, 0, 0));
        undefined_message->SetBackgroundColour(wxColour(150, 150, 150));
        undefined_message->SetFont(title_font);
        undefined_message->Hide();

        //supplier drop down menu
        wxArrayString supArray;
        supArray.Add("dump value1");
        supArray.Add("dump value2");
        supList = new wxChoice(this, wxID_ANY, wxPoint(250, 200), wxDefaultSize, supArray);
        wxStaticText* supListLabel = new wxStaticText(this, wxID_ANY, "suppliers", wxPoint(150, 200), wxDefaultSize);
        supList->Bind(wxEVT_CHOICE, &Relations::supplier_list_event, this);
        //spare parts drop down menu
        wxArrayString spaArray;
        spaArray.Add("dump value1");
        spaArray.Add("dump value2");
        spaList = new wxChoice(this, wxID_ANY, wxPoint(800, 200), wxDefaultSize, spaArray);
        wxStaticText* spaListLabel = new wxStaticText(this, wxID_ANY, "spare parts", wxPoint(700, 200), wxDefaultSize);
        spaList->Bind(wxEVT_CHOICE, &Relations::spare_part_list_event, this);
        // submit button
        create_rels_btn = new wxButton(this, wxID_ANY, "create a relation", wxPoint(500, 450));
        create_rels_btn->Enable(false);
        create_rels_btn->Bind(wxEVT_BUTTON, &Relations::Hit_button_event, this);

        //sound effect

        Hit_button_Sound = new wxMediaCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);//properties of the mediaplayer
        Hit_button_Sound->SetPlaybackRate(1.0);//the media player
        Hit_button_Sound->Load("C:\\ProjData\\FirstGUI\\assets\\Punch Sound Effect(MP3_160K).mp3");//loading the sound using the directory 
        //using the event  you created and linking it with the button

        //relation exist sound
        Rel_Exist_sound = new wxMediaCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);//properties of the mediaplayer
        Rel_Exist_sound->SetPlaybackRate(1.0);//the media player
        Rel_Exist_sound->Load("C:\\ProjData\\FirstGUI\\assets\\Minecraft Steve OOF Sound Effect(MP3_160K).mp3");//loading the sound using the directory 
    }
private:
    void Hit_button_event(wxCommandEvent& event)//you must pass an event parameter
    {
        Hit_button_Sound->Play();//play the sound

        wxMilliSleep(1500);
        undefined_message->Show();
        Rel_Exist_sound->Play();
        //our logic will be here
    }
    void supplier_list_event(wxCommandEvent& event)//i
    {

        supList_flag = true;
        check_button();
    }
    void spare_part_list_event(wxCommandEvent& event)//you must pass an event parameter
    {

        spaList_flag = true;
        check_button();
    }

    void check_button()//you must pass an event parameter
    {

        if (supList_flag && spaList_flag)
        {
            create_rels_btn->Enable(true);
            title->SetForegroundColour(wxColour(255, 0, 0));
            title->Refresh();//make sure that the updates will be applied
        }
    }
};


class MyFrame : public wxFrame {
private:
    void OnPageChange(wxBookCtrlEvent& event)
    {
        // Handle page change event
        // You can add logic here to perform actions when switching between pages
        event.Skip();
    }

    wxNotebook* notebook;
    wxString dataFileName; // File to store data
    wxDECLARE_EVENT_TABLE();

public:
    MyFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
    {
        ::wxInitAllImageHandlers();

        wxNotebook* notebook = new wxNotebook(this, wxID_ANY);

        // Main Page
        wxPanel* mainPage = new MainPagecontent(notebook);
        notebook->AddPage(mainPage, "Main Page");

        wxPanel* supSearch = new SearchHistoryPanel(notebook);//first page of the panel that holds text as a parameter"its inside the panel
        notebook->AddPage(supSearch, "History");//adding the first page to the notebook which is panel 1 with a title of main page



        // Factory Page
        wxPanel* factoryPage = new wxPanel(notebook);
        notebook->AddPage(factoryPage, "Factory");

        // Create and configure controls for the Factory page
        wxBoxSizer* factorySizer = new wxBoxSizer(wxVERTICAL);

        wxCheckListBox* suppliersList = new wxCheckListBox(factoryPage, wxID_ANY, wxDefaultPosition, wxDefaultSize,
            0, NULL, wxLB_MULTIPLE);

        wxCheckListBox* suppliersList2 = new wxCheckListBox(factoryPage, wxID_ANY, wxDefaultPosition, wxDefaultSize,
            0, NULL, wxLB_MULTIPLE);

        suppliersList->Append("Insert");

        suppliersList2->Append("Display");

        factorySizer->Add(new wxStaticText(factoryPage, wxID_ANY, "Suppliers:"), 0, wxALL, 5);
        factorySizer->Add(suppliersList, 0, wxALL | wxEXPAND, 5);

        factorySizer->Add(new wxStaticText(factoryPage, wxID_ANY, "Suppliers:"), 0, wxALL, 5);
        factorySizer->Add(suppliersList2, 0, wxALL | wxEXPAND, 5);

        factoryPage->SetSizer(factorySizer);

        // Bind events
        suppliersList->Bind(wxEVT_CHECKLISTBOX, &MyFrame::OnInsert, this);
        suppliersList2->Bind(wxEVT_CHECKLISTBOX, &MyFrame::OnDisplay, this);

        // Set the data file name
        dataFileName = "data.txt";


        // Relations Page
        wxPanel* relationsPage = new Relations(notebook);
        notebook->AddPage(relationsPage, "Relations");

        // Set up the layout
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(notebook, 1, wxEXPAND);
        SetSizer(sizer);

        // Set the minimum size for the frame
        SetMinSize(wxSize(800, 600));

        // Bind the event for page change for main page content
        Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &MyFrame::OnPageChange, this, wxID_ANY);
    }
    void OnExit(wxCommandEvent& event) {
        // Close the application
        Close(true);
    }

    void OnAbout(wxCommandEvent& event) {
        // Show an about dialog
        wxMessageBox("This is a wxWidgets application example.", "About", wxOK | wxICON_INFORMATION, this);
    }
    void OnInsert(wxCommandEvent& event) {
        if (event.GetInt() == 0) { // Check if "Insert" is checked
            // Show a form for inserting data
            wxString name, phone, email;

            wxTextEntryDialog dialog(this, "Enter Supplier Information:", "Insert Supplier");

            if (dialog.ShowModal() == wxID_OK) {
                name = dialog.GetValue();
                wxTextEntryDialog phoneDialog(this, "Enter Phone Number:", "Insert Supplier");
                if (phoneDialog.ShowModal() == wxID_OK) {
                    phone = phoneDialog.GetValue();
                    wxTextEntryDialog emailDialog(this, "Enter Email:", "Insert Supplier");
                    if (emailDialog.ShowModal() == wxID_OK) {
                        email = emailDialog.GetValue();

                        // Append data to the file
                        std::ofstream dataFile(dataFileName.ToStdString(), std::ios::app);
                        if (dataFile.is_open()) {
                            dataFile << "Supplier: " << name << ", Phone: " << phone << ", Email: " << email << std::endl;
                            dataFile.close();
                            wxMessageBox("Data inserted successfully!");
                        }
                        else {
                            wxMessageBox("Failed to open the data file for writing!");
                        }
                    }
                }
            }
        }
    }

    void OnDisplay(wxCommandEvent& event) {
        if (event.GetInt() == 0) { // Check if "Display" is checked
            // Display data from the file
            std::ifstream dataFile(dataFileName.ToStdString());
            wxString content;

            if (dataFile.is_open()) {
                std::string line;
                while (std::getline(dataFile, line)) {
                    content += wxString(line) + "\n";
                }
                dataFile.close();
            }
            else {
                content = "Failed to open the data file for reading!";
            }

            wxMessageDialog dialog(this, content, "Display Data", wxOK | wxICON_INFORMATION);
            dialog.ShowModal();
        }
    }
    void OnExitt(wxCommandEvent& event) {
        // Close the application
        Close(true);
    }

    void OnAboutt(wxCommandEvent& event) {
        // Show an about dialog
        wxMessageBox("This is a wxWidgets application example.", "About", wxOK | wxICON_INFORMATION, this);
    }
};

// Event table macros
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(wxID_EXIT, MyFrame::OnExit)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
wxEND_EVENT_TABLE()

class MyApp : public wxApp {
public:
    virtual bool OnInit() override {
        MyFrame* frame = new MyFrame("Factory");
        frame->Show(true);
        frame->SetClientSize(1100, 650);
        frame->Center();
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
