using Utilities;

//Day 2; Part 1!

string[] input = InputTools.ReadAllLines();

int safeCount = 0;
foreach (string line in input)
{
    //pars levels:
    var levels = line.Split(' ').Select(int.Parse).ToList();
    
    if (ReportIsSave(levels))
        safeCount++;
    
}
Console.WriteLine(safeCount);

bool ReportIsSave(List<int> levels)
{
    
    //if its only one let it pass
    if (levels.Count == 1) return true;

    //check first pair manually:
    var firstDiff = GetDelta(levels.First(), levels.Skip(1).First());
    if(!IsSafe(firstDiff)) return false;
    bool isAscending = firstDiff > 0;

    //check the rest
    bool isSafe = true;
    for (int i = 1; i < levels.Count - 1; i++)
    {
        var diff = GetDelta(levels[i], levels[i + 1]);
        if(!IsSafe(diff)) return false;

        bool intermidiateEvaluation = diff > 0 ? isAscending : !isAscending;
        if (!intermidiateEvaluation)
            isSafe = false;
    }

    return isSafe;
    
}

int GetDelta(int a, int b) => b - a;
bool IsSafe(int diff) => Math.Abs(diff) is >= 1 and <= 3;