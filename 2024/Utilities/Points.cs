namespace Utilities;

using System;

using System;

using System;

public readonly struct Point2D : IEquatable<Point2D>, IComparable<Point2D>
{
    public int X { get; }
    public int Y { get; }

    public Point2D(int x, int y)
    {
        X = x;
        Y = y;
    }

    // Implement IEquatable<Point2D>
    public bool Equals(Point2D other)
    {
        return X == other.X && Y == other.Y;
    }

    public override bool Equals(object? obj)
    {
        return obj is Point2D other && Equals(other);
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(X, Y);
    }

    // Implement IComparable<Point2D>
    public int CompareTo(Point2D other)
    {
        // Compare X coordinates first
        int xComparison = X.CompareTo(other.X);
        if (xComparison != 0)
        {
            return xComparison;
        }

        // If X coordinates are equal, compare Y coordinates
        return Y.CompareTo(other.Y);
    }

    // For easier debugging or display
    public override string ToString()
    {
        return $"({X}, {Y})";
    }

    // Override == and != operators
    public static bool operator ==(Point2D a, Point2D b) => a.Equals(b);
    public static bool operator !=(Point2D a, Point2D b) => !a.Equals(b);

    // Override + operator
    public static Point2D operator +(Point2D a, Point2D b) => new Point2D(a.X + b.X, a.Y + b.Y);

    // Override - operator
    public static Point2D operator -(Point2D a, Point2D b) => new Point2D(a.X - b.X, a.Y - b.Y);
    
    public static Point2D operator *(Point2D a, int b) => new Point2D(a.X * b, a.Y * b);
}



public readonly struct Direction
{
    public int XDelta { get; }
    public int YDelta { get; }

    public Direction(int xDelta, int yDelta)
    {
        if (Math.Abs(xDelta) > 1 || Math.Abs(yDelta) > 1 || (xDelta != 0 && yDelta != 0))
            throw new ArgumentException("Direction deltas must be -1, 0, or 1, and cannot have both non-zero.");
        XDelta = xDelta;
        YDelta = yDelta;
    }

    public static Direction Up => new Direction(-1, 0);   
    public static Direction Down => new Direction(1, 0);  
    public static Direction Left => new Direction(0, -1); 
    public static Direction Right => new Direction(0, 1);

    public override string ToString() => $"({XDelta}, {YDelta})";

    public Direction RotateClockwise() => new Direction(YDelta, -XDelta);
    public Direction RotateCounterClockwise() => new Direction(-YDelta, XDelta);
}
