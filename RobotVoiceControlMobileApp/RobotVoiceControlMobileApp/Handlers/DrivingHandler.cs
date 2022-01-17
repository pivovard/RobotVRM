using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using static RobotVoiceControlMobileApp.Constants;

namespace RobotVoiceControlMobileApp.Handlers
{
    class DrivingHandler
    {
        private byte command { get; set; } = STOP;
        private byte speed { get; set; } = SPEED;

        BLEHandler bleHandler;

        private static DrivingHandler instance = null;

        public static DrivingHandler GetHandler()
        {
            if(instance == null)
            {
                instance = new DrivingHandler();
            }
            return instance;
        }

        private DrivingHandler()
        {
            this.bleHandler = BLEHandler.GetHandler();
        }

        public async Task<bool> Stop()
        {
            command = STOP;
            speed = SPEED;
            return await bleHandler.Send(STOP);
        }

        public async Task<bool> Forward(byte? s = null)
        {
            if (command == FORWARD)
            {
                return await Faster();
            }
            else
            {
                speed = s != null ? (byte)s : SPEED;
                command = FORWARD;
                return await bleHandler.Send(command, new byte[2] { speed, speed });
            }
        }

        public async Task<bool> Back(byte? s = null)
        {
            if (command == BACK)
            {
                return await Faster();
            }
            else
            {
                speed = s != null ? (byte)s : SPEED;
                command = BACK;
                return await bleHandler.Send(command, new byte[2] { speed, speed });
            }
        }

        public async Task<bool> Right()
        {
            return await bleHandler.Send(command, new byte[2] { (byte)(speed*2), speed });
        }

        public async Task<bool> Left()
        {
            return await bleHandler.Send(command, new byte[2] { (byte)(speed / 0x03), speed });
        }

        public async Task<bool> Faster()
        {
            if (speed + DSPEED < byte.MaxValue)
            {
                speed += DSPEED;
                return await bleHandler.Send(command, new byte[2] { speed, speed });
            }
            else return false;
        }

        public async Task<bool> Slower()
        {
            if (speed > DSPEED)
            {
                speed -= DSPEED;
                return await bleHandler.Send(command, new byte[2] { speed, speed });
            }
            else return false;
        }

        public async Task<bool> Follow()
        {
            command = FOLLOW;
            return await bleHandler.Send(FOLLOW);
        }

    }
}
