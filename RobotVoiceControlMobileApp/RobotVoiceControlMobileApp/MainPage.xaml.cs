using RobotVoiceControlMobileApp.Handlers;
using System;
using System.Diagnostics;
using Xamarin.Forms;

using static RobotVoiceControlMobileApp.Constants;

namespace RobotVoiceControlMobileApp
{
    public partial class MainPage : ContentPage
    {
        BLEHandler bleHandler;
        VRHandler vrHandler;
        DrivingHandler drivingHandler;

        public MainPage()
        {
            InitializeComponent();
            lText.Text = "";
            indicatorVR.IsRunning = false;

            bleHandler = BLEHandler.GetHandler();
            drivingHandler = DrivingHandler.GetHandler();
            vrHandler = new VRHandler( lText, indicatorVR);

            if (!bleHandler.ble.IsOn)
            {
                DisplayAlert("", "Turn Bluetooth ON!", "Ok");
            }
        }

        private async void btnConnect_Clicked(object sender, EventArgs e)
        {
            if (!bleHandler.ble.IsOn)
            {
                await DisplayAlert("", "Turn Bluetooth ON!", "Ok");
                return;
            }

            if (!bleHandler.IsConnected())
            {
                bool res = false;
                indicatorBLE.IsRunning = true;

                try
                {
                    await bleHandler.Scan();
                    res = await bleHandler.Connect();
                }
                catch(Exception ex)
                {
                    Debug.WriteLine(ex.Message);
                }
                finally
                {
                    indicatorBLE.IsRunning = false;
                }

                if (res)
                {
                    btnConnect.Source = "connected.png";
                    await DisplayAlert("", $"Connected to {bleHandler.adapter.ConnectedDevices[0].Name}", "Ok");
                }
                else await DisplayAlert("Error", "Failed to connect to the robot!", "Ok");
            }
            else
            {
                await bleHandler.Disconnect();
                btnConnect.Source = "disconnected.png";
                await DisplayAlert("", "Disconnected.", "Ok");
            }
        }

        async void ShowSettings(object sender, EventArgs e)
        {
            await Navigation.PushAsync(new SettingsPage());
        }

        //Voice recognition controls
        private async void rec_Clicked(object sender, EventArgs e)
        {
            if (!await vrHandler.IsMicEnabled()) await DisplayAlert("Error", "Please grant permission to the microphone!", "Ok");

            if (indicatorVR.IsRunning)
            {
                vrHandler.StopRecognition();
            }
            else
            {
                vrHandler.StartRecognition();
            }
        }

        //movement controls
        private async void btnLeft_Clicked(object sender, EventArgs e)
        {
            if (!await bleHandler.Send(FORWARD, new byte[2] { FAST, SLOW }))
            {
                await DisplayAlert("Error", "Failed to send the command", "Ok");
            }
        }

        private async void btnUp_Clicked(object sender, EventArgs e)
        {
            if (!await drivingHandler.Forward())
            {
                await DisplayAlert("Error", "Failed to send the command", "Ok");
            }
        }

        private async void btnUp2_Clicked(object sender, EventArgs e)
        {
            if (!await drivingHandler.Forward(DSPEED))
            {
                await DisplayAlert("Error", "Failed to send the command", "Ok");
            }
        }

        private async void btnRight_Clicked(object sender, EventArgs e)
        {
            if (!await bleHandler.Send(FORWARD, new byte[2] { SLOW, FAST }))
            {
                await DisplayAlert("Error", "Failed to send the command", "Ok");
            }
        }

        private async void btnDown_Clicked(object sender, EventArgs e)
        {
            if (!await drivingHandler.Back())
            {
                await DisplayAlert("Error", "Failed to send the command", "Ok");
            }
        }

        private async void btnDown2_Clicked(object sender, EventArgs e)
        {
            if (!await drivingHandler.Back(DSPEED))
            {
                await DisplayAlert("Error", "Failed to send the command", "Ok");
            }
        }

        private async void btnStop_Clicked(object sender, EventArgs e)
        {
            if (!await drivingHandler.Stop())
            {
                await DisplayAlert("Error", "Failed to send the command", "Ok");
            }
        }

        private async void btnFollow_Clicked(object sender, EventArgs e)
        {
            if (!await drivingHandler.Follow())
            {
                await DisplayAlert("Error", "Failed to send the command", "Ok");
            }
        }
    }
}
