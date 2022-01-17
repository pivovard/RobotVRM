﻿using Microsoft.CognitiveServices.Speech;
using RobotVoiceControlMobileApp.Services;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading.Tasks;
using Xamarin.Forms;

using static RobotVoiceControlMobileApp.Constants;

namespace RobotVoiceControlMobileApp.Handlers
{
    class VRHandler
    {
        SpeechRecognizer recognizer;
        IMicrophoneService micService;

        BLEHandler bleHandler;
        DrivingHandler drivingHandler;

        Label lText;
        ActivityIndicator indicator;

        public VRHandler(Label label, ActivityIndicator indicator)
        {
            micService = DependencyService.Resolve<IMicrophoneService>();

            this.bleHandler = BLEHandler.GetHandler();
            this.drivingHandler = DrivingHandler.GetHandler();

            this.lText = label;
            this.indicator = indicator;

            // initialize speech recognizer 
            if (recognizer == null)
            {
                var config = SpeechConfig.FromSubscription(Constants.CognitiveServicesApiKey, Constants.CognitiveServicesRegion);
                //string[] languages = { "cs-CZ", "en-US", "en-GB" };
                AutoDetectSourceLanguageConfig lang_config = AutoDetectSourceLanguageConfig.FromLanguages(Constants.GetLanguages);
                recognizer = new SpeechRecognizer(config, lang_config);
                recognizer.Recognized += (obj, args) =>
                {
                    Process(args.Result.Text);
                };
            }
        }

        public async Task<bool> IsMicEnabled()
        {
            bool isMicEnabled = await micService.GetPermissionAsync();
            if (isMicEnabled) return true;
            else return false;
        }

        public async void StartRecognition()
        {
            try
            {
                await recognizer.StartContinuousRecognitionAsync();
            }
            catch (Exception e)
            {
                Debug.WriteLine(e.Message);
                return;
            }

            Device.BeginInvokeOnMainThread(() =>
            {
                indicator.IsRunning = true;
            });
        }

        public async void StopRecognition()
        {
            try
            {
                await recognizer.StopContinuousRecognitionAsync();
            }
            catch (Exception e)
            {
                Debug.WriteLine(e.Message);
                return;
            }

            Device.BeginInvokeOnMainThread(() =>
            {
                indicator.IsRunning = false;
            });
        }

        private void Process(string text)
        {
            Device.BeginInvokeOnMainThread(() =>
            {
                lText.Text = text;
            });

            this.StopRecognition();

            ProcessText(text);
        }

        private void ProcessText(string text)
        {
            text = text.ToLower();

            if (text.Match(KeywordMap.STOP))
            {
                drivingHandler.Stop();
                return;
            }

            if (text.Match(KeywordMap.FASTER))
            {
                drivingHandler.Faster();
                return;
            }

            if (text.Match(KeywordMap.SLOWER))
            {
                drivingHandler.Slower();
                return;
            }

            if (text.Match(KeywordMap.RIGHT))
            {
                drivingHandler.Right();
                return;
            }

            if (text.Match(KeywordMap.LEFT))
            {
                drivingHandler.Left();
                return;
            }

            if (text.Match(KeywordMap.BACKWARD))
            {
                drivingHandler.Back();
            }

            if (text.Match(KeywordMap.FORWARD))
            {
                drivingHandler.Forward();
                return;
            }

            if (text.Match(KeywordMap.FOLLOW))
            {
                drivingHandler.Follow();
                return;
            }
        }

        private void ProcessTextDeprecated(string text)
        {
            text = text.ToLower();

            if (UsePhrase && !text.Contains(GetPhrase.ToLower())) return;
            
            if (text.Contains("stop"))
            {
                bleHandler.Send(STOP);
                return;
            }

            if (text.Contains("forward") || (text.Contains("go") && !text.Contains("back")) )
            {
                if (text.Contains("slow"))
                {
                    bleHandler.Send(FORWARD, new byte[2] { FAST, FAST });
                }
                else
                {
                    bleHandler.Send(FORWARD, new byte[2] { FFAST, FFAST });
                }
                return;
            }

            if (text.Contains("back") || text.Contains("reverse"))
            {
                bleHandler.Send(BACK, new byte[2] { FAST, FAST });
                return;
            }

            if (text.Contains("right"))
            {
                bleHandler.Send(FORWARD, new byte[2] { SLOW, FAST });
                return;
            }

            if (text.Contains("left"))
            {
                bleHandler.Send(FORWARD, new byte[2] { FAST, SLOW });
                return;
            }

            if (text.Contains("follow"))
            {
                bleHandler.Send(FOLLOW);
                return;
            }
        }

    }
}