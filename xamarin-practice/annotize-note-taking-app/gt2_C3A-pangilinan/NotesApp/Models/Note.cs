using SQLite;
using System;
using System.Collections.Generic;
using System.Text;

namespace NotesApp.Models {
    public class Note {
        [PrimaryKey, AutoIncrement]
        public int ID { get; set; }
        [NotNull]
        public string NoteTitle { get; set; }
        [NotNull]
        public string NoteContent { get; set; }
        [NotNull]
        public string DateCreate { get; set; }
        public string DateUpdate { get; set; }
    }
}
