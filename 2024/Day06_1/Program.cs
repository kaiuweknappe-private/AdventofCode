using Utilities;

//Day 6; Part 1!

string[] input = InputTools.ReadAllLines();

var obstacales = new HashSet<Point2D>();
var currentPos = new Point2D(0,0);

for (int x = 0; x < input.Length; x++)
{
    for (int y = 0; y < input[x].Length; y++)
    {
        if(input[x][y] == '#')
            obstacales.Add(new Point2D(x, y));
        else if(input[x][y] == '^')
            currentPos = new Point2D(x, y);
    }
}

var direction = Direction.Up;
var visited = new HashSet<Point2D>(); //(hashset only keeps unique once)
do
{
    //adding to visited:
    visited.Add(currentPos);
    
    //finding next pos and avoiding obstacales
    var nextPos = new Point2D(currentPos.X + direction.XDelta, currentPos.Y + direction.YDelta);
    while (obstacales.Contains(nextPos))
    {
        direction = direction.RotateClockwise();
        nextPos = new Point2D(currentPos.X + direction.XDelta, currentPos.Y + direction.YDelta);
    }
    currentPos = nextPos;
    
} while (!IsOutOfBounds(currentPos));

Console.WriteLine(visited.Count);

bool IsOutOfBounds(Point2D point) => !Helper.IsBetween(point.X, 0, input.Length -1) || !Helper.IsBetween(point.Y, 0, input[0].Length - 1); 
