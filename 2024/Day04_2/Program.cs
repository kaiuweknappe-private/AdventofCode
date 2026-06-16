using System.Diagnostics;
using Utilities;

//Day 4; Part 2!

string[] input = InputTools.ReadAllLines();
int count = 0;

for (int x = 0; x < input.Length; x++)
{
    //for every A search if 
    //and add count up
    for (int y = 0; y < input[x].Length; y++)
    {
        if (input[x][y] == 'A')
        {
            if (IsXMas(x, y)) 
                count++;
        }
    }
}
Console.WriteLine(count);

//function to check if its an mas / mas x at around the A
//x, y are coordinates to a X
bool IsXMas(int x, int y)
{
    //check if in bounds/ there is enough space
    if (!Helper.IsBetween(x - 1, 0, input.Length - 1) ||
        !Helper.IsBetween(y - 1, 0, input[x - 1].Length - 1) ||
        !Helper.IsBetween(x + 1, 0, input.Length - 1) ||
        !Helper.IsBetween(y + 1, 0, input[x + 1].Length - 1))
        return false;

    var first = input[x-1][y-1].ToString() + 'A' + input[x+1][y+1].ToString();
    var second = input[x-1][y+1].ToString() + 'A' + input[x+1][y-1].ToString();

    return IsMasString(first) && IsMasString(second);
}

bool IsMasString(string tag) => tag is "MAS" or "SAM";