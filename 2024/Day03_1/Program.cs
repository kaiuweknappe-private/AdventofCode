using System.Text.RegularExpressions;
using Utilities;

//Day 3; Part 1!

string[] input = InputTools.ReadAllLines();
var pattern = @"mul\((\d{1,3}),(\d{1,3})\)";
int result = 0;

foreach (var line in input)
{
    var match = Regex.Match(line, pattern);
    while (match.Success)
    {
        var firstFactor  = int.Parse(match.Groups[1].Value);
        var secondFactor = int.Parse(match.Groups[2].Value);
        result += firstFactor * secondFactor;
        
        match = match.NextMatch();
    }
    
}

Console.WriteLine(result);