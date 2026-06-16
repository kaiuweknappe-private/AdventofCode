using Utilities;

//Day 11; Part 2!

string[] input = InputTools.ReadAllLines();

var stones = new List<long>();
foreach (var item in input[0].Split(' '))
    stones.Add(long.Parse(item));

/*for (int b = 0; b < 25; b++)
{
    var currentStones = stones.Count;
    //for every bling: transfer oldStones to new Stones by appliing ruels
    for (int i = 0; i < currentStones; i++)
    {
        if (stones[i] == 0) // first rule
        {
            stones[i] = 1;
        }
        else if (((int)Math.Log10(stones[i]) +1) % 2 == 0) //second rule
        {
            var middle = ((int)Math.Floor(Math.Log10(stones[i])) + 1) / 2;
            var divisor = (int)Math.Pow(10, middle);
            stones[i] /= divisor;
            stones.Add(stones[i] % divisor);
        }
        else //third rule
        {
            stones[i] *= 2024;
        }
    }
    //Console.WriteLine(b);
    Console.WriteLine(stones.Count);
}*/

//trying it now recursifly with deep first rather that width first, u feel me?
/*int sum = 0;
foreach (var stone in stones)
{
    GetBranchesAmount(stone, 0);
}
Console.WriteLine(sum);

void GetBranchesAmount(long stone, int depth)
{
    if (depth >= 45)//reached one stone after n blinks
    {
        sum++;
        return;
    }
    
    //apply rules and branch
    if (stone == 0) // first rule
    {
        GetBranchesAmount(1, depth + 1);
    }
    else if (((int)Math.Log10(stone) +1) % 2 == 0) //second rule
    {
        var middle = ((int)Math.Floor(Math.Log10(stone)) + 1) / 2;
        var divisor = (int)Math.Pow(10, middle);
        GetBranchesAmount(stone / divisor, depth + 1);
        GetBranchesAmount(stone % divisor, depth + 1);
    }
    else //third rule
    {
        GetBranchesAmount(stone * 2024, depth + 1); 
    }
}*/


//new try, try binding same stones together every state..should avoid a few can assess how many
var uniqueStones = new List<Stone>(stones.Select(v => new Stone(v, 1)));
for (int b = 0; b < 25; b++)
{
    var currentLength = uniqueStones.Count;
    //for every bling:
    for (var i = 0; i < currentLength; i++)
    {
        if (uniqueStones[i].Value == 0) // first rule
        {
            uniqueStones[i].Value = 1;
        }
        else if (((int)Math.Log10(uniqueStones[i].Value) +1) % 2 == 0) //second rule
        {
            var middle = ((int)Math.Log10(uniqueStones[i].Value) + 1) / 2;
            var divisor = (int)Math.Pow(10, middle);
            var leftStone = new Stone(uniqueStones[i].Value / divisor, 1);
            var rightStone = new Stone(uniqueStones[i].Value % divisor, 1);
            if(uniqueStones.Contains(leftStone))
                uniqueStones.Find(s => s.Value == leftStone.Value).Value++;
            else
                uniqueStones.Add(leftStone);
            if(uniqueStones.Contains(rightStone))
                uniqueStones.Find(s => s.Value == rightStone.Value).Value++;
            else
                uniqueStones.Add(rightStone);
        }
        else //third rule
        {
            uniqueStones[i].Value *= 2024;
        }
    }
    Console.WriteLine(b);
}

int result = uniqueStones.Sum((stone) => stone.Count);
Console.WriteLine(result);

class Stone(long value, int count)
{
    public long Value { get; set; } = value;
    public int Count { get; set; } = count;
}