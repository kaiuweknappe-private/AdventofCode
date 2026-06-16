using Utilities;

//Day 7; Part 2!

string[] input = InputTools.ReadAllLines();

//reading input part
var equasions = new List<Equasion>();
foreach (var line in input)
{
    Equasion tempEquasions = new Equasion();
    var firstSplit = line.Split(": ");
    tempEquasions.Ref = long.Parse(firstSplit[0]);
    foreach (var val in firstSplit[1].Split(' '))
    {
        tempEquasions.Values.Add(int.Parse(val));
    }
    equasions.Add(tempEquasions);
}

//solving the puzzle
long result = 0;
foreach (var equasion in equasions)
{
    for (int n = 0; n < Math.Pow(3, equasion.Values.Count - 1); n++)
    {
        var base3Code = Helper.ToBase3(n).PadLeft(equasion.Values.Count - 1, '0');
        var num = (long)equasion.Values.First();
        
        for (int i = 0; i< base3Code.Length; i++)
        {
            if (base3Code[i] == '0')
            {
                num += equasion.Values[i + 1];
            }
            else if (base3Code[i] == '1')
            {
                num *= equasion.Values[i + 1];
            }
            else if (base3Code[i] == '2')
            {
                num = long.Parse(num.ToString() + equasion.Values[i + 1].ToString());
            }
        }
        
        if (num == equasion.Ref)
        {
            result += equasion.Ref;
            break;
        }
    }
}
Console.WriteLine(result);
return;

// util
public class Equasion
{
    public long Ref { get; set; }
    public List<int> Values { get;} = new();
}