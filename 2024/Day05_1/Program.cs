using Microsoft.VisualBasic;
using Utilities;

//Day 5; Part 1!

string[] input = InputTools.ReadAllLines();
int emptyIndex = Array.IndexOf(input, "");
string[] firstPart = input.Take(emptyIndex).ToArray();
string[] secondPart = input.Skip(emptyIndex + 1).ToArray();

//read ruels
var rules = new List<(int first, int second)>();
foreach (var line in firstPart)
{
    var split = line.Split('|');
    rules.Add((int.Parse(split[0]), int.Parse(split[1])));
}

//read updates
var updates = new List<List<int>>();
foreach (var line in secondPart)
{
    var split = line.Split(',');
    var tempList = new List<int>();
    foreach (var stringNum in split)
    {
        tempList.Add(int.Parse(stringNum));
    }
    updates.Add(tempList);
}

//check updates if correct
int result = 0;
foreach (var update in updates)
{
    if (UpdateIsSafe(update))
    {
        result += update[update.Count / 2];
    }
}
Console.WriteLine(result);

bool UpdateIsSafe(List<int> list)
{
    foreach (var rule in rules)
    {
        if (list.Contains(rule.first) && list.Contains(rule.second))
        {
            if (list.IndexOf(rule.first) > list.IndexOf(rule.second))
                return false;
        }
    }

    return true;
}