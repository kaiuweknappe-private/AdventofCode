using System.Drawing;
using Utilities;

//Day 10; Part 1!

string[] input = InputTools.ReadAllLines();

var map = new int[input.Length, input[0].Length];
var trailStarts = new List<Point2D>();
for (int x = 0; x < input.Length; x++)
{
    for (int y = 0; y < input[0].Length; y++)
    {
        var height = input[x][y] - '0';
        map[x, y] = height;
        if(height == 0)
            trailStarts.Add(new Point2D(x, y));
    }
}

int sum = 0;
foreach (var trailStart in trailStarts)
{
    var trailHeads = new HashSet<Point2D>();
    GetTrailHeads(trailStart, trailHeads);
    sum += trailHeads.Count;
}
Console.WriteLine(sum);

void GetTrailHeads(Point2D currentPos, HashSet<Point2D> trailHeads)
{
    var currentHeight = GetHeightFromPoint(currentPos);

    if (currentHeight == 9) //stop condition
    {
        trailHeads.Add(currentPos);
        return;
    }

    if (GetHeightFromPoint(new Point2D(currentPos.X - 1, currentPos.Y)) - currentHeight == 1) //upwards
        GetTrailHeads(new Point2D(currentPos.X - 1, currentPos.Y), trailHeads);
    if (GetHeightFromPoint(new Point2D(currentPos.X + 1, currentPos.Y)) - currentHeight == 1) //downwards
        GetTrailHeads(new Point2D(currentPos.X + 1, currentPos.Y), trailHeads);
    if (GetHeightFromPoint(new Point2D(currentPos.X, currentPos.Y - 1)) - currentHeight == 1) //left
        GetTrailHeads(new Point2D(currentPos.X, currentPos.Y - 1), trailHeads);
    if (GetHeightFromPoint(new Point2D(currentPos.X, currentPos.Y + 1)) - currentHeight == 1) //right
        GetTrailHeads(new Point2D(currentPos.X, currentPos.Y + 1), trailHeads);
}

int GetHeightFromPoint(Point2D point) => !IsOutOfBounds(point) ? map[point.X, point.Y] : -1;

bool IsOutOfBounds(Point2D point) => !Helper.IsBetween(point.X, 0, input.Length -1) || !Helper.IsBetween(point.Y, 0, input[0].Length - 1);
