using Utilities;

//Day 4; Part 1!

string[] input = InputTools.ReadAllLines();

var refString = "MAS";
int count = 0;

for (int x = 0; x < input.Length; x++)
{
    //for every x search all directions for xmas's
    //and add count up
    for (int y = 0; y < input[x].Length; y++)
    {
        if (input[x][y] == 'X')
        {
            if (IsXMasString(x, y, -1, 0)) count++; //up
            if (IsXMasString(x, y, -1, 1)) count++;
            if (IsXMasString(x, y, 0, 1)) count++;//right
            if (IsXMasString(x, y, 1, 1)) count++;
            if (IsXMasString(x, y, 1, 0)) count++;//down
            if (IsXMasString(x, y, 1, -1)) count++;
            if (IsXMasString(x, y, 0, -1)) count++;//left
            if (IsXMasString(x, y, -1, -1)) count++;
        }
    }
}
Console.WriteLine(count);

//function to check for xmas string in specified direction
//x, y are coordinates to a X
//direction delta can eighter be -1, 0, or 1
bool IsXMasString(int x, int y, int xDelta, int yDelta)
{
    for (int i = 1; i <= refString.Length; i++)
    {
        var currentX = x + i * xDelta;
        var currentY = y + i * yDelta;
        if (!Helper.IsBetween(currentX, 0, input.Length-1) ||
            !Helper.IsBetween(currentY, 0, input[currentX].Length -1) ||
            input[currentX][currentY] != refString[i-1])
            return false;
    }
    return true;
}