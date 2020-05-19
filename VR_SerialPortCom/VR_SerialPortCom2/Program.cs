using System;
using System.Collections.Generic;
using System.ComponentModel.Design;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VR_SerialPortCom2
{
    class Program
    {
        static System.IO.Ports.SerialPort port;

        static readonly string[] commands = { "FORWARD", "BACK", "STOP", "RIGHT", "LEFT", "FOLLOW", "DANCE" };
        static byte[] buffer = new byte[200];

        static readonly byte BEG = 0xAA;
        static readonly byte END = 0x0A;

        //0xAA [LEN] [COMMAND] [DATA] [0x0A]
        //byte[] msg = new byte[] {0xAA, 0x02, 0x00, 0x0A }; //status

        static void Main(string[] args)
        {
            if(args.Length < 2)
            {
                Help();
                return;
            }

            port = new System.IO.Ports.SerialPort(args[1], args.Length == 3 ? int.Parse(args[2]) : 9600);

            port.Open();

            if (port.IsOpen) Console.WriteLine("Connected");
            else Console.WriteLine("Not connected");

            switch (args[0])
            {
                case "train": Train();  break;
                case "test": Test();  break;
                default: Help(); break;
            }

            port.Close();
            Console.ReadKey();
        }

        static void Train()
        {
            //0x20 train
            byte[] msg = { 0xAA, 0x03, 0x20, 0x00, 0x0A };
            //0x21 train with signature
            //byte[] msg = new byte[] { 0xAA, 0x05, 0x21, 0x00, 0x6E, 0x6E, 0x0A };

            Console.WriteLine("Press any key when you are ready...");
            Console.ReadKey();

            for(byte i = 0; i < 7; ++i)
            {
                Console.WriteLine($"Set {commands[i]} command:");

                msg[3] = i;
                port.Write(msg, 0, msg.Length);

                do
                {
                    int len = Read();
                    if (buffer[2] != 0x20) PrintPrompt(len);
                }
                while (buffer[2] != 0x20);
                
            }

            SetAutoLoad();

            Console.WriteLine("Training complete.");
        }

        static void SetAutoLoad()
        {
            //0x15 set auto load on
            //0x7F 7 commands
            byte[] msg = { 0xAA, 0x0A, 0x15, 0x7F, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0A };
            port.Write(msg, 0, msg.Length);
        }

        static void Test()
        {
            //0x30 load to recognizer
            byte[] msg = { 0xAA, 0x09, 0x30, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0A };
            port.Write(msg, 0, msg.Length);

            while (true)
            {
                int len = Read();
                PrintHex(len);
                if (buffer[2] == 0xD) Console.WriteLine(commands[buffer[5]]);
            }
        }

        static int Read()
        {
            buffer[0] = (byte)port.ReadByte();
            int len = port.ReadByte();
            buffer[1] = (byte)len;

            for (int i = 0; i < len; ++i)
            {
                buffer[i + 2] = (byte)port.ReadByte(); ;
            }

            return len + 2;
        }

        static void PrintHex(int len)
        {
            for (int i = 0; i < len; ++i)
            {
                Console.Write("{0:X} ", buffer[i]);
            }
            Console.WriteLine();
        }

        static void PrintChar(int len)
        {
            for (int i = 0; i < len; ++i)
            {
                Console.Write("{0}", (char)buffer[i]);
            }
            Console.WriteLine();
        }

        static void PrintPrompt(int len)
        {
            for(int i = 3; i < len-1; ++i)
            {
                Console.Write("{0}", (char)buffer[i]);
            }
            Console.WriteLine();
        }

        static void Help()
        {
            Console.WriteLine("VR_SerialPortCom2 [command] [port] [(optional) baud rate]\n" +
                "Commands:\n" +
                "- train: trains 7 records to the VRM module\n" +
                "- test: test records 1-7");
        }
    }
}
