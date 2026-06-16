using Utilities;

//Day 10; Part 2!

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
    sum += GetTrailHeads(trailStart);

Console.WriteLine(sum);
//feels like part 1 & 2 should be the other way around, lol

int GetTrailHeads(Point2D currentPos)
{
    var currentHeight = GetHeightFromPoint(currentPos);
    
    if (currentHeight == 9) //stop condition
        return 1;
    
    var currentRating = 0;
    if (GetHeightFromPoint(new Point2D(currentPos.X - 1, currentPos.Y)) - currentHeight == 1) //upwards
        currentRating += GetTrailHeads(new Point2D(currentPos.X - 1, currentPos.Y));
    if (GetHeightFromPoint(new Point2D(currentPos.X + 1, currentPos.Y)) - currentHeight == 1) //downwards
        currentRating += GetTrailHeads(new Point2D(currentPos.X + 1, currentPos.Y));
    if (GetHeightFromPoint(new Point2D(currentPos.X, currentPos.Y - 1)) - currentHeight == 1) //left
        currentRating += GetTrailHeads(new Point2D(currentPos.X, currentPos.Y - 1));
    if (GetHeightFromPoint(new Point2D(currentPos.X, currentPos.Y + 1)) - currentHeight == 1) //right
        currentRating += GetTrailHeads(new Point2D(currentPos.X, currentPos.Y + 1));
    
    return currentRating;
}

int GetHeightFromPoint(Point2D point) => !IsOutOfBounds(point) ? map[point.X, point.Y] : -1;

bool IsOutOfBounds(Point2D point) => !Helper.IsBetween(point.X, 0, input.Length -1) || !Helper.IsBetween(point.Y, 0, input[0].Length - 1);