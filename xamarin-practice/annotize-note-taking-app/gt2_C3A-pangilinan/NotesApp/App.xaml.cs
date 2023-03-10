using System;
using Xamarin.Forms;
using Xamarin.Forms.Xaml;
using NotesApp.Data;
using System.IO;

namespace NotesApp {
    public partial class App : Application {
        static NoteDatabase database;

        public static NoteDatabase Database {
            get {
                if (database == null) {
                    database = new NoteDatabase(Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "Note.db3"));
                }
                return database;
            }
        }

        public App() {
            InitializeComponent();

            MainPage = new NavigationPage(new LoginPage());
        }

        protected override void OnStart() {
        }

        protected override void OnSleep() {
        }

        protected override void OnResume() {
        }
    }
}
