using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

using Xamarin.Forms;
using Xamarin.Forms.Xaml;

namespace sa2_c3a_pangilinan.Views
{
    [XamlCompilation(XamlCompilationOptions.Compile)]
    public partial class WeightConverter : ContentPage
    {
        public ICommand LocalCommand => new Command(ButtonReset);
        public ICommand CalculateCommand => new Command(Calculate);

        private const double LBS = 2.20462262185; //1 KG = 2.20462262185 LBS
        public WeightConverter()
        {
            InitializeComponent();
            BindingContext = this;
        }

        private void ButtonReset()
        {
            enterKG.Text = "";
            enterLBS.Text = "";
        }

        private void Calculate()
        {
            if (enterKG.Text == "" && enterLBS.Text != "") //LBS to KG
            {
                enterKG.Text = Convert.ToString(double.Parse(enterLBS.Text) / LBS);
            }
            else if (enterKG.Text != "" && enterLBS.Text == "") //KG to LBS
            {
                enterLBS.Text = Convert.ToString(double.Parse(enterKG.Text) * LBS);
            }
        }

        private void enterKG_Focused(object sender, FocusEventArgs e)
        {
            enterLBS.Text = "";
        }

        private void enterLBS_Focused(object sender, FocusEventArgs e)
        {
            enterKG.Text = "";
        }

        private void enterKG_Completed(object sender, EventArgs e)
        {
            Calculate();
        }

        private void enterLBS_Completed(object sender, EventArgs e)
        {
            Calculate();
        }
    }
}