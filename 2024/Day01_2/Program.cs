using Utilities;

//Day 1; Part 2 !

string[] input = InputTools.ReadAllLines();

var leftList = new List<int>();
var rightList = new List<int>();

foreach (var line in input)
{
    var parts = line.Split("   ");
    leftList.Add(int.Parse(parts[0]));
    rightList.Add(int.Parse(parts[1]));
}

//parsing the right list into a dict first or at the same time would prob be more efficient
int result = 0;
foreach (var item in leftList)
{
    result += rightList.Count(x => x == item) * item;
}
Console.WriteLine(result);