using System.Text.RegularExpressions;
using Utilities;

//Day 3; Part 2!

string[] input = InputTools.ReadAllLines();

var patternMul = @"mul\((\d{1,3}),(\d{1,3})\)";
var patterndo = @"do\(\)";
var patterndont = @"don't\(\)";

var list = new List<Match>();
bool isEnabled = true;
int result = 0;

foreach (var line in input)
{
    var match = Regex.Match(line, patternMul);
    while (match.Success)
    {
        list.Add(match);
        match = match.NextMatch();
    }
    
    match = Regex.Match(line, patterndo);
    while (match.Success)
    {
        list.Add(match);
        match = match.NextMatch();
    }
    
    match = Regex.Match(line, patterndont);
    while (match.Success)
    {
        list.Add(match);
        match = match.NextMatch();
    }

    result += CalculateLine();
    list.Clear();
}

Console.WriteLine(result);

int CalculateLine()
{
    list.Sort((a, b) => a.Index.CompareTo(b.Index));

    int lineRes = 0;
    foreach (var match in list)
    {
        if (match.Value == "do()")
        {
            isEnabled = true;
        }
        else if (match.Value == "don't()")
        {
            isEnabled = false;
        }
        else
        {
            if (!isEnabled) continue;

            var firstFactor = match.Groups[1].Value;
            var secondFactor = match.Groups[2].Value;
            lineRes += int.Parse(firstFactor) * int.Parse(secondFactor);
        }
    }
    return lineRes;
}