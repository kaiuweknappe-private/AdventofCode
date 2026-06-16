using Utilities;

//Day 9; Part 1!

string[] input = InputTools.ReadAllLines();
var inputList = new List<int>(input[0].Select(c => int.Parse(c.ToString()) )); 

//convert to block list
var blocks = new List<int>(); // -1 represents free space 
for (int i = 0; i < inputList.Count; i++)
{
    int blockType = -1;
    if (i % 2 == 0) //even -> file
    {
        blockType = i / 2; // id
    }
    
    for (int n = 0; n < inputList[i]; n++)
    {
        blocks.Add(blockType); 
    }
}

//now optimize the space usaged (shrink everything to the left..)
//interating through the blocks and when freespace moving tightest blocks to the left.. therefore keeping track of a right/end index
int endIndex = blocks.Count;
var optimizedBlocks = new List<int>();
for (int currentIndex = 0; currentIndex < endIndex; currentIndex++)
{
    
    if (blocks[currentIndex] == -1)// -> free space
    {
        //moving endIndex to the next rightmost file block:
        do
        {
            endIndex--;
        } while (blocks[endIndex] == -1);    
        
        //finished aswell if:
        if (endIndex <= currentIndex) break;
        
        //moving it to the current pos:
        optimizedBlocks.Add(blocks[endIndex]);
    }
    else
    {
        optimizedBlocks.Add(blocks[currentIndex]);
    }
}

//calc checksum:
long checksum = 0;
for (int i = 0; i < optimizedBlocks.Count; i++)
{
    checksum += optimizedBlocks[i] * i;
}
Console.WriteLine(checksum);
