using Utilities;

//Day 1; Part 1 !

string[] input = InputTools.ReadAllLines();

int sum = 0;
var leftList = new List<int>();
var rightList = new List<int>();

foreach (var line in input)
{
    var parts = line.Split("   ");
    leftList.Add(int.Parse(parts[0]));
    rightList.Add(int.Parse(parts[1]));
}

leftList.Sort((a, b) => a.CompareTo(b));
rightList.Sort((a, b) => a.CompareTo(b));

foreach (var (left, right) in leftList.Zip(rightList, (x, y) => (x, y)))
{
    sum += Math.Abs(left - right);
}

Console.WriteLine(sum);