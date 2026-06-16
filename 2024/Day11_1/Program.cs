using Utilities;

//Day 11; Part 1!

string[] input = InputTools.ReadAllLines();

var newStones = new List<long>();
foreach (var item in input[0].Split(' '))
    newStones.Add(long.Parse(item));

List<long> oldStones;
for (int i = 0; i < 25; i++)
{
    oldStones = new List<long>(newStones);
    newStones.Clear();
    
    //for every bling: transfer oldStones to new Stones by appliing ruels
    foreach (var stone in oldStones)
    {
        if (stone == 0) // first rule
        {
            newStones.Add(1);
        }
        else if (((int)Math.Log10(stone) +1) % 2 == 0) //second rule
        {
            var middle = ((int)Math.Floor(Math.Log10(stone)) + 1) / 2;
            var divisor = (int)Math.Pow(10, middle);
            newStones.Add(stone / divisor);
            newStones.Add(stone % divisor);
            //tried something like this instead of string stuff.. not sure if its currently working like this.. but should be somehow possible like that
        }
        else //third rule
        {
            newStones.Add(stone * 2024);
        }
    }
}
Console.WriteLine(newStones.Count);