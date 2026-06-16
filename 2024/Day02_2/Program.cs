using Utilities;

//Day 2; Part 2!

string[] input = InputTools.ReadAllLines();

int safeCount = 0;
foreach (string line in input)
{
    //pars levels:
    var levels = line.Split(' ').Select(int.Parse).ToList();
    
    if(ReportIsSave(levels))
    {
        safeCount++;
        continue;
    }

    for (int i = 0; i < levels.Count(); i++)
    {
        var tempLevel = new List<int>(levels);
        tempLevel.RemoveAt(i);
        if (ReportIsSave(tempLevel))
        {
            safeCount++;
            break;
        }
    }
    
}
Console.WriteLine(safeCount);

bool ReportIsSave(List<int> levels)
{
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