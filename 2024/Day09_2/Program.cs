using Utilities;

//Day 9; Part 2!

string[] input = InputTools.ReadAllLines();

//convert to block list
var files = new List<Block>();
var fragments = new List<Fragment>();
int currentPos = 0;
for (int i = 0; i < input[0].Length; i++)
{
    var num = input[0][i] - '0';
    if (i % 2 == 0) //even -> file
    {
        files.Add(new Block(currentPos, num, i/2));
    }
    else
    {
        fragments.Add(new Fragment() {Pos = currentPos, Count = num});
    }
    currentPos += num;
}

//now optimize the space
for (int i = files.Count-1; i >= 0; i--)
{
    //find first large enough fragment:
    var newLocation = FindFirstLargeEnoughFragment(files[i].Count, files[i].Pos);
    
    //move the current file there:
    if(newLocation != -1)
        files[i].Pos = newLocation;
}

//calc checksum:
long checksum = 0;
foreach (var file in files)
{
    /*for (int n = 0; n < file.Count; n++)
    {
        checksum += file.Id * (file.Pos + n);
    }*/
    
    //with a bit of math from O(n²) -> O(n) :)
    var n = file.Count;
    var triangularSum = (n-1) * n / 2;
    checksum += (long)file.Id * (n * file.Pos + triangularSum);
}
Console.WriteLine(checksum);


int FindFirstLargeEnoughFragment(int count, int tillPos)
{
    foreach (var fragment in fragments)
    {
        if (fragment.Pos >= tillPos) return -1; // didnt find any

        if (fragment.Count < count) continue; // too small
        
        fragment.Count -= count;
        var pos = fragment.Pos;
        fragment.Pos += count;
        if (fragment.Count == 0)
            fragments.Remove(fragment);
        return pos;
    }
    return -1;
}

//block mdoel
class Block(int pos, int count, int id)
{
    public int Id { get; } = id;
    public int Pos { get; set; } = pos; //start index of block
    public int Count { get; } = count;
}

class Fragment
{
    public int Pos { get; set; }
    public int Count { get; set; }
}