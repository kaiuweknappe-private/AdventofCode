using Utilities;

//Day 6; Part 2!

string[] input = InputTools.ReadAllLines();

var obstacales = new HashSet<Point2D>();
var startPos = new Point2D(0,0);

for (int x = 0; x < input.Length; x++)
{
    for (int y = 0; y < input[x].Length; y++)
    {
        if(input[x][y] == '#')
            obstacales.Add(new Point2D(x, y));
        else if(input[x][y] == '^')
            startPos = new Point2D(x, y);
    }
}

//find the main path
var currentPos = startPos;
var direction = Direction.Up;
var mainPath = new HashSet<Point2D>(); //(hashset only keeps unique once)
do
{
    //adding to visited:
    mainPath.Add(currentPos);
    
    //finding next pos and avoiding obstacales
    var nextPos = new Point2D(currentPos.X + direction.XDelta, currentPos.Y + direction.YDelta);
    while (obstacales.Contains(nextPos))
    {
        direction = direction.RotateClockwise();
        nextPos = new Point2D(currentPos.X + direction.XDelta, currentPos.Y + direction.YDelta);
    }
    currentPos = nextPos;
    
} while (!IsOutOfBounds(currentPos));

var currentPathTracker = new Dictionary<Point2D, HashSet<Direction>>();
int count = 0;
foreach (var possibleObstacalPlacement in mainPath.Skip(1)) //skip starting pos
{
    currentPathTracker.Clear();
    //check if new obstacles set leads to loop path:
    if(IsALoop(possibleObstacalPlacement))
        count++;
}
Console.WriteLine(count);

bool IsALoop(Point2D additionalObstacle)
{
    currentPos = startPos;
    direction = Direction.Up;
    do
    {
        if (currentPathTracker.ContainsKey(currentPos))
        {
            if(currentPathTracker[currentPos].Contains(direction))
                return true; // same point with same direction was already visited -> loop
            currentPathTracker[currentPos].Add(direction);
        }
        else
        {
            currentPathTracker.Add(currentPos, [direction]);
        }
        
        //finding next pos and avoiding obstacales
        var nextPos = new Point2D(currentPos.X + direction.XDelta, currentPos.Y + direction.YDelta);
        while (obstacales.Contains(nextPos) || nextPos.Equals(additionalObstacle))
        {
            direction = direction.RotateClockwise();
            nextPos = new Point2D(currentPos.X + direction.XDelta, currentPos.Y + direction.YDelta);
        }
        currentPos = nextPos;
    
    } while (!IsOutOfBounds(currentPos));
    
    return false;
}

bool IsOutOfBounds(Point2D point) => !Helper.IsBetween(point.X, 0, input.Length -1) || !Helper.IsBetween(point.Y, 0, input[0].Length - 1);