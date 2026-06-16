using System.Drawing;
using System.Numerics;
using Utilities;

//Day 8; Part 1!

string[] input = InputTools.ReadAllLines();

var antennas = new List<Antenna>();
for (int x = 0; x < input.Length; x++)
{
    for (int y = 0; y < input[x].Length; y++)
    {
        if(input[x][y] != '.')
            antennas.Add(new Antenna(new Point2D(x, y), input[x][y]));
    }
}

var antinodes = new HashSet<Point2D>();
foreach (var antenna in antennas)
{
    //antennas with same freq exept itself
    var fellowAntennas = antennas.Where(ant => ant.Type == antenna.Type && ant != antenna);
    foreach (var antenna2 in fellowAntennas)
    {
        //every antenna pair:
        //calculate its to antinodes:
        //calc vektor
        var vek  = antenna.Location - antenna2.Location;

        var firstAntinode = antenna.Location + vek;
        if(!IsOutOfBounds(firstAntinode))
            antinodes.Add(firstAntinode);
        
        var secondAntinode = antenna2.Location - vek;
        if(!IsOutOfBounds(secondAntinode))
            antinodes.Add(secondAntinode);
    }
}


Console.WriteLine(antinodes.Count);


bool IsOutOfBounds(Point2D point) => !Helper.IsBetween(point.X, 0, input.Length -1) || !Helper.IsBetween(point.Y, 0, input[0].Length - 1);
public class Antenna (Point2D location, Char type) 
{
    public char Type { get; } = type;
    public Point2D Location { get; } = location;
}