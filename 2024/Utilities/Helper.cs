namespace Utilities;

public class Helper
{
    public static bool IsBetween(int value, int min, int max)
    {
        return value >= min && value <= max;
    }
    
    public static void Swap<T>(List<T> list, int index1, int index2)
    {
        //swap via deconstruction??? muss ich mir angucken
        (list[index1], list[index2]) = (list[index2], list[index1]);
    }
    
    public static string ToBase3(int number)
    {
        if (number == 0) return "0";

        return IntToString(number, ['0', '1', '2']);
    }
    
    public static string IntToString(int value, char[] baseChars)
    {
        string result = string.Empty;
        int targetBase = baseChars.Length;

        do
        {
            result = baseChars[value % targetBase] + result;
            value = value / targetBase;
        } 
        while (value > 0);

        return result;
    }
}