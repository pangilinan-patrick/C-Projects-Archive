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
    public partial class MoneyConverter : ContentPage
    {
        public ICommand LocalCommand => new Command(ButtonReset);
        public ICommand CalculateCommand => new Command(Calculate);

        //The currencies will include US dollar, Japanese Yen, KSA riyal, UAE dirham and UK pound.
        private const double USD = 52.89;
        private const double YEN = 0.4;
        private const double SAR = 14.13;
        private const double AED = 14.42;
        private const double GBP = 66.52;

        public MoneyConverter()
        {
            InitializeComponent();
            BindingContext = this;
        }

        private void CurrencyOptions(object sender, EventArgs args)
        {
            //Dollars, JYEn, KSARiyal, Dirham, Pound
            RadioButton radioButton = sender as RadioButton;
            enterCurrency.Text = ""; //reset values after changing currency
            enterPHP.Text = "";     //reset values after changing currency

            if (Dollars.IsChecked)
            {
                exchangeRate.Text = $"Enter {radioButton.Content}:";    //change the exchange rate text to the appropriate currency
                label.Text = $"1 {radioButton.Value} = PHP {USD}";
            }

            else if (JYen.IsChecked)
            {
                exchangeRate.Text = $"Enter {radioButton.Content}:";
                label.Text = $"1 {radioButton.Value} = PHP {YEN}";
            }

            else if (KSARiyal.IsChecked)
            {
                exchangeRate.Text = $"Enter {radioButton.Content}:";
                label.Text = $"1 {radioButton.Value} = PHP{SAR}";
            }

            else if (Dirham.IsChecked)
            {
                exchangeRate.Text = $"Enter {radioButton.Content}:";
                label.Text = $"1 {radioButton.Value} = PHP{AED}";
            }

            else if (Pound.IsChecked)
            {
                exchangeRate.Text = $"Enter {radioButton.Content}:";
                label.Text = $"1 {radioButton.Value} = PHP{GBP}";
            }
        }

        private void ButtonReset()
        {
            enterCurrency.Text = "";
            enterPHP.Text = "";
        }

        private void Calculate()
        {
            //currency start
            if (Dollars.IsChecked)
            {
                if (enterPHP.Text == "" && enterCurrency.Text != "") //USD to PHP
                {
                    enterPHP.Text = Convert.ToString(double.Parse(enterCurrency.Text) * USD);
                }
                else if (enterPHP.Text != "" && enterCurrency.Text == "") //PHP to USD
                {
                    enterCurrency.Text = Convert.ToString(double.Parse(enterPHP.Text) / USD);
                }
            }

            else if (JYen.IsChecked)
            {
                if (enterPHP.Text == "" && enterCurrency.Text != "")
                {
                    enterPHP.Text = Convert.ToString(double.Parse(enterCurrency.Text) * YEN);
                }
                else if (enterPHP.Text != "" && enterCurrency.Text == "")
                {
                    enterCurrency.Text = Convert.ToString(double.Parse(enterPHP.Text) / YEN);
                }
            }

            else if (KSARiyal.IsChecked)
            {
                if (enterPHP.Text == "" && enterCurrency.Text != "")
                {
                    enterPHP.Text = Convert.ToString(double.Parse(enterCurrency.Text) * SAR);
                }
                else if (enterPHP.Text != "" && enterCurrency.Text == "")
                {
                    enterCurrency.Text = Convert.ToString(double.Parse(enterPHP.Text) / SAR);
                }
            }

            else if (Dirham.IsChecked)
            {
                if (enterPHP.Text == "" && enterCurrency.Text != "")
                {
                    enterPHP.Text = Convert.ToString(double.Parse(enterCurrency.Text) * AED);
                }
                else if (enterPHP.Text != "" && enterCurrency.Text == "")
                {
                    enterCurrency.Text = Convert.ToString(double.Parse(enterPHP.Text) / AED);
                }
            }

            else if (Pound.IsChecked)
            {
                if (enterPHP.Text == "" && enterCurrency.Text != "")
                {
                    enterPHP.Text = Convert.ToString(double.Parse(enterCurrency.Text) * GBP);
                }
                else if (enterPHP.Text != "" && enterCurrency.Text == "")
                {
                    enterCurrency.Text = Convert.ToString(double.Parse(enterPHP.Text) / GBP);
                }
            }
        }

        private void enterPHP_Focused(object sender, FocusEventArgs e)
        {
            enterCurrency.Text = "";
        }

        private void enterCurrency_Focused(object sender, FocusEventArgs e)
        {
            enterPHP.Text = "";
        }

        private void enterPHP_Completed(object sender, EventArgs e)
        {
            Calculate();
        }

        private void enterCurrency_Completed(object sender, EventArgs e)
        {
            Calculate();
        }
    }
}