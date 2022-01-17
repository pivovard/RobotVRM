using System;
using System.Collections.Generic;
using System.Text;

namespace RobotVoiceControlMobileApp.Handlers
{
    public static class KeywordMap
    {
        public static readonly string[] STOP = { "stop", "stůj", "zastav" };
        public static readonly string[] FORWARD = { "go", "forward", "ride", "jeď", "dopředu", "vpřed", "rovně" };
        public static readonly string[] BACKWARD = { "back", "reverse", "couvej", "zpět", "zpátky" };
        public static readonly string[] RIGHT = { "right", "doprava", "vpravo" };
        public static readonly string[] LEFT = { "left", "doleva", "vlevo" };
        public static readonly string[] FASTER = { "fast", "faster", "go go", "rychle", "rychleji", "zrychli" };
        public static readonly string[] SLOWER = { "slow", "slower", "pomalu", "pomaleji", "zpomal" };
        public static readonly string[] FOLLOW = { "follow", "následuj" };

        public static bool Match(this string text, string[] pattern)
        {
            foreach(var p in pattern)
            {
                if (text.Contains(p)) return true;
            }
            return false;
        }
    }
}
