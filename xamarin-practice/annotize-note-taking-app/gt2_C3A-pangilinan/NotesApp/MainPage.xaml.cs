using NotesApp.Data;
using NotesApp.Models;
using Syncfusion.XForms.PopupLayout;
using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Input;
using Xamarin.Essentials;
using Xamarin.Forms;

namespace NotesApp {
    public partial class MainPage : ContentPage {
        protected SfPopupLayout addNotePopup;
        // Save note --> true, Update note --> false
        public bool save = true;
        // Global note to update 
        public Note changeNote;
        protected string todayDate = DateTime.Now.ToString("dd. M. yyyy");

        // Generation of entry elements
        protected Entry NoteTitleEnt = new Entry { Placeholder = "Title can only be 10 chars", PlaceholderColor=Color.Gray, TextColor=Color.Black, MaxLength = 10 };
        protected Entry NoteContentEnt = new Entry { Placeholder = "What are your thoughts? (200 chars)", PlaceholderColor = Color.Gray , TextColor = Color.Black, MaxLength = 200 };
        public ICommand SaveNoteCommand { get; set; }

        public MainPage() {
            InitializeComponent();
            SaveNoteCommand = new Command(SaveNote);

            addNotePopup = PopupContent();

        }
    // Generation of add new note popup content
    public SfPopupLayout PopupContent() {
            SfPopupLayout popup = new SfPopupLayout();

            DataTemplate templateView = new DataTemplate(() => {
                StackLayout popupLayout = new StackLayout {
                    Children = {
                        new Label { Text = "Title", TextColor = Color.Black },
                        NoteTitleEnt,
                        new Label { Text = "Note", TextColor = Color.Black},
                        NoteContentEnt,
                    }
                };
                return popupLayout;
            });
          
            popup.PopupView.ContentTemplate = templateView;
            popup.PopupView.AnimationMode = AnimationMode.SlideOnBottom;
            popup.PopupView.HeaderTitle = "Add new note";
            popup.PopupView.AcceptButtonText = "Save";
            //Bind Command for saving note (when tapped save btn)
            popup.PopupView.AcceptCommand = SaveNoteCommand;

            return popup;
        }

        // Generating Notes into View
        protected override async void OnAppearing() {
            base.OnAppearing();
            today.Text = todayDate;

            List<Note> notes = await App.Database.GetNotesAsync();
            body.Children.Clear();

            // Note template
            foreach (Note note in notes) {
                //Del Button setup and bind
                ImageButton delBtn = new ImageButton { HeightRequest = 25, Source = "delete_icon.png", BackgroundColor = Color.White, Margin = 5 };
                delBtn.Clicked += OnDelBtnClicked;
                delBtn.CommandParameter = note;

                //Edit button setup and bind
                ImageButton editBtn = new ImageButton { HeightRequest = 25, Source = "edit_icon.png", BackgroundColor = Color.White, Margin = 5 };
                editBtn.Clicked += OnEditBtnClicked;
                editBtn.CommandParameter = note;

                //note label setup
                Label contentLabel = new Label { FontSize = 15, TextColor = Color.DarkGray, Text = note.NoteContent };
                Label titleLabel = new Label { FontSize = 20, TextColor = Color.Black, FontAttributes = FontAttributes.Bold, Text = note.NoteTitle };

                Grid grid = new Grid {
                    RowDefinitions = {
                        new RowDefinition(),
                        new RowDefinition(),
                        new RowDefinition(),
                        new RowDefinition(),
                        new RowDefinition(),
                    },
                    ColumnDefinitions = {
                        new ColumnDefinition(),
                        new ColumnDefinition(),
                        new ColumnDefinition(),
                        new ColumnDefinition(),
                    },
                };
                grid.Children.Add(titleLabel, 0, 0);
                grid.Children.Add(new Label { FontSize = 15, TextColor = Color.Black, HorizontalOptions = LayoutOptions.End, VerticalOptions = LayoutOptions.End, Text = note.DateCreate }, 3, 0);
                grid.Children.Add(contentLabel, 0, 1);
                grid.Children.Add(new Label { FontSize = 12, TextColor = Color.LightGray, Text = note.DateUpdate }, 0, 5);
                grid.Children.Add(new StackLayout {
                    HorizontalOptions = LayoutOptions.End,
                    Children = {
                        delBtn
                    }
                }, 2, 5);
                grid.Children.Add(new StackLayout {
                    HorizontalOptions = LayoutOptions.Start,
                    Children = {
                        editBtn
                    }
                }, 3, 5);
                Frame frame = new Frame {
                    Margin = 10,
                    CornerRadius = 5,
                    HasShadow = true,
                    BorderColor = Color.LightGray,
                    Content = grid
                };

                //Note label span
                Grid.SetColumnSpan(contentLabel, 4);
                Grid.SetRowSpan(contentLabel, 3);
                Grid.SetColumnSpan(titleLabel, 2);

                body.Children.Add(frame);
            };
        }

        // When add note btn clicked, showes add note popup
        private void addNotePopup_Clicked(object sender, EventArgs e) {
            save = true;
            addNotePopup.Show();
        }

        // When added new note, saves it
        async void SaveNote() {
            if (!string.IsNullOrEmpty(NoteTitleEnt.Text) && !string.IsNullOrEmpty(NoteContentEnt.Text) && save) {
                Note note = new Note {
                    NoteTitle = NoteTitleEnt.Text,
                    NoteContent = NoteContentEnt.Text,
                    DateCreate = todayDate
                };
                await App.Database.SaveNoteAsync(note);
            }else if (!string.IsNullOrEmpty(NoteTitleEnt.Text) && !string.IsNullOrEmpty(NoteContentEnt.Text) && !save) {
                changeNote.NoteTitle = NoteTitleEnt.Text;
                changeNote.NoteContent = NoteContentEnt.Text;
                changeNote.DateUpdate = todayDate;
                await App.Database.SaveNoteAsync(changeNote);
            }

            //Refresh entries
            NoteTitleEnt.Text = "";
            NoteContentEnt.Text = "";
            OnAppearing();
        }

        // Delete button clicked event
        async void OnDelBtnClicked(object sender, EventArgs e) {
            await App.Database.DeleteNoteAsync((Note)((ImageButton)sender).CommandParameter);
            OnAppearing();
        }

        // Edit button clicked event
        public void OnEditBtnClicked(object sender, EventArgs e) {
            save = false;
            changeNote = (Note)((ImageButton)sender).CommandParameter;
            addNotePopup.Show();
            OnAppearing();
        }
    }
}
