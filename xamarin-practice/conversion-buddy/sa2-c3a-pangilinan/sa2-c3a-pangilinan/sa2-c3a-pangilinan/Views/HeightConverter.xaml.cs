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
    public partial class HeightConverter : ContentPage
    {
        public ICommand LocalCommand => new Command(ButtonReset);
        public ICommand CalculateCommand => new Command(Calculate);

        private const double CM = 30.48; //1 FT = 30.48 CM
        public HeightConverter()
        {
            InitializeComponent();
            BindingContext = this;
        }
        private void ButtonReset()
        {
            enterFT.Text = "";
            enterCM.Text = "";
        }

        private void Calculate()
        {
            if (enterCM.Text == "" && enterFT.Text != "") //FT to CM
            {
                enterCM.Text = Convert.ToString(double.Parse(enterFT.Text) * CM);
            }
            else if (enterCM.Text != "" && enterFT.Text == "") //CM to FT
            {
                enterFT.Text = Convert.ToString(double.Parse(enterCM.Text) / CM);
            }
        }

        private void enterCM_Focused(object sender, FocusEventArgs e)
        {
            enterFT.Text = "";
        }

        private void enterFT_Focused(object sender, FocusEventArgs e)
        {
            enterCM.Text = "";
        }

        private void enterCM_Completed(object sender, EventArgs e)
        {
            Calculate();
        }

        private void enterFT_Completed(object sender, EventArgs e)
        {
            Calculate();
        }
    }
}